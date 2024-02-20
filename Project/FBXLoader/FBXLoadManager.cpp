#include "pch.h"
#include "framework.h"
#include "FBXLoadManager.h"

FBXLoadManager::FBXLoadManager()
	: mFbxManager(nullptr)
	, mIos(nullptr)
{
	mFbxManager = FbxManager::Create();
	Assert(mFbxManager, ASSERT_MSG_NULL);

	mIos = FbxIOSettings::Create(mFbxManager, IOSROOT);
	Assert(mIos, ASSERT_MSG_NULL);
}

FBXLoadManager::~FBXLoadManager()
{
	mIos->Destroy();

	mFbxManager->Destroy();

	for (tBone* bone : m_vecBone)
	{
		delete bone;
	}
}

void FBXLoadManager::Load(const std::wstring& wFilePath)
{
	//장면가져오기
	{
		const std::string& FILE_PATH = std::string(wFilePath.cbegin(), wFilePath.cend()).c_str();

		FbxImporter* const imposter = FbxImporter::Create(mFbxManager, "");
		Assert(imposter, ASSERT_MSG_NULL);

		// Initialize the importer.
		bool lImportStatus = imposter->Initialize(FILE_PATH.c_str(), -1, mFbxManager->GetIOSettings());
		Assert(lImportStatus, ASSERT_MSG_INVALID);

		//장면 가져오기		
		FbxScene* const fbxScene = FbxScene::Create(mFbxManager, "");
		Assert(fbxScene, ASSERT_MSG_NULL);
		imposter->Import(fbxScene);

		fbxScene->GetGlobalSettings().SetAxisSystem(FbxAxisSystem::Max);

		mVecContainer.clear();

		//bon
		loadSkeleton(fbxScene->GetRootNode());

		//animation names
		fbxScene->FillAnimStackNameArray(m_arrAnimName);

		loadAnimationClip(fbxScene);

		//삼각화
		triangulate(fbxScene->GetRootNode());

		// 메쉬 데이터 얻기
		loadMeshDataFromNode(fbxScene, fbxScene->GetRootNode());

		loadTextrue();

		imposter->Destroy();
	}


}

void FBXLoadManager::triangulate(FbxNode* _pNode)
{
	FbxNodeAttribute* pAttr = _pNode->GetNodeAttribute();

	if (pAttr &&
		(pAttr->GetAttributeType() == FbxNodeAttribute::eMesh
			|| pAttr->GetAttributeType() == FbxNodeAttribute::eNurbs
			|| pAttr->GetAttributeType() == FbxNodeAttribute::eNurbsSurface))
	{
		FbxGeometryConverter converter(mFbxManager);
		converter.Triangulate(pAttr, true);
	}

	int iChildCount = _pNode->GetChildCount();

	for (int i = 0; i < iChildCount; ++i)
	{
		triangulate(_pNode->GetChild(i));
	}
}
void FBXLoadManager::lodeMesh(FbxScene* const fbxScene, FbxMesh* FbxMesh)
{		
	Assert(FbxMesh, ASSERT_MSG_NULL);

	mVecContainer.push_back(tContainer{});
	tContainer& container = mVecContainer[mVecContainer.size() - 1];

	const std::string& MESH_NAME = FbxMesh->GetName();
	container.strName = std::wstring(MESH_NAME.begin(), MESH_NAME.end());

	const int VERTEX_COUNT = FbxMesh->GetControlPointsCount();
	container.Resize(VERTEX_COUNT);

	const FbxVector4* const P_VERTEX_POS_ARRAY = FbxMesh->GetControlPoints();

	for (int i = 0; i < VERTEX_COUNT; ++i)
	{
		container.vecPos[i].x = static_cast<float>(P_VERTEX_POS_ARRAY[i].mData[0]);
		container.vecPos[i].y = static_cast<float>(P_VERTEX_POS_ARRAY[i].mData[2]);
		container.vecPos[i].z = static_cast<float>(P_VERTEX_POS_ARRAY[i].mData[1]);
	}
	
	const int POLY_COUNT = FbxMesh->GetPolygonCount();

	// 재질의 개수 ( ==> SubSet 개수 ==> Index Buffer Count)
	const int MTRL_COUNT = FbxMesh->GetNode()->GetMaterialCount();
	container.vecIdx.resize(MTRL_COUNT);

	// 정점 정보가 속한 subset 을 알기위해서...
	FbxGeometryElementMaterial* mtrl = FbxMesh->GetElementMaterial();

	// 폴리곤을 구성하는 정점 개수
	const int POLY_SIZE = FbxMesh->GetPolygonSize(0);
	if (3 != POLY_SIZE)
	{
		// Polygon 구성 정점이 3개가 아닌 경우
		Assert(false, ASSERT_MSG_INVALID);
	}		

	UINT poly[3] = {0,};
	UINT IndexIdx = 0; // 폴리곤 순서로 접근하는 순번
	for (int i = 0; i < POLY_COUNT; ++i)
	{
		for (int j = 0; j < POLY_SIZE; ++j)
		{
			// i 번째 폴리곤에, j 번째 정점
			const int VERTEX_IDX = FbxMesh->GetPolygonVertex(i, j);
			poly[j] = VERTEX_IDX;

			GetTangent(FbxMesh, &container, VERTEX_IDX, IndexIdx);
			GetBinormal(FbxMesh, &container, VERTEX_IDX, IndexIdx);
			GetNormal(FbxMesh, &container, VERTEX_IDX, IndexIdx);
			GetUV(FbxMesh, &container, VERTEX_IDX, FbxMesh->GetTextureUVIndex(i, j));

			++IndexIdx;
		}
		int iSubsetIdx = mtrl->GetIndexArray().GetAt(i);
		container.vecIdx[iSubsetIdx].push_back(poly[0]);
		container.vecIdx[iSubsetIdx].push_back(poly[2]);
		container.vecIdx[iSubsetIdx].push_back(poly[1]);
	}

	loadAnimationData(fbxScene, FbxMesh, &container);
}

Vector4 FBXLoadManager::GetMtrlData(FbxSurfaceMaterial* _pSurface,
	const char* _pMtrlName,
	const char* _pMtrlFactorName)
{
	FbxDouble3  vMtrl;
	FbxDouble	dFactor = 0.;

	FbxProperty tMtrlProperty = _pSurface->FindProperty(_pMtrlName);
	FbxProperty tMtrlFactorProperty = _pSurface->FindProperty(_pMtrlFactorName);

	if (tMtrlProperty.IsValid() && tMtrlFactorProperty.IsValid())
	{
		vMtrl = tMtrlProperty.Get<FbxDouble3>();
		dFactor = tMtrlFactorProperty.Get<FbxDouble>();
	}

	Vector4 vRetVal = Vector4((float)vMtrl.mData[0] * (float)dFactor, (float)vMtrl.mData[1] * (float)dFactor, (float)vMtrl.mData[2] * (float)dFactor, (float)dFactor);
	return vRetVal;
}

std::wstring FBXLoadManager::GetMtrlTextureName(FbxSurfaceMaterial* _pSurface, const char* _pMtrlProperty)
{
	std::string strName;

	FbxProperty TextureProperty = _pSurface->FindProperty(_pMtrlProperty);
	if (TextureProperty.IsValid())
	{
		UINT iCnt = TextureProperty.GetSrcObjectCount();

		if (1 <= iCnt)
		{
			FbxFileTexture* pFbxTex = TextureProperty.GetSrcObject<FbxFileTexture>(0);
			if (NULL != pFbxTex)
				strName = pFbxTex->GetFileName();
		}
	}

	return std::wstring(strName.begin(), strName.end());
}

DWORD SecondThread(PVOID pvParam)
{
	BYTE*			pByte = reinterpret_cast<BYTE*>(pvParam);
	FbxSkin*		pSkin = (FbxSkin*)*(unsigned long long*)(pByte);
	FbxScene* const fbxScene = (FbxScene*)*(unsigned long long*)(pByte + 8);
	FbxMesh*		_pMesh = (FbxMesh*)*(unsigned long long*)(pByte + 16);
	tContainer*		_pContainer = (tContainer*)*(unsigned long long*)(pByte + 24);
	FBXLoadManager* manager = (FBXLoadManager*)*(unsigned long long*)(pByte + 32);
	int idx = *(int*)(pByte + 40);


	//FbxSkin* pSkin, FbxScene* const fbxScene, FbxMesh* _pMesh, tContainer* _pContainer, int idx
	FbxCluster* pCluster = pSkin->GetCluster(idx);

	if (!pCluster->GetLink())
		return 0;

	// 현재 본 인덱스를 얻어온다.
	std::string boneName = pCluster->GetLink()->GetName();
	int iBoneIdx = manager->FindBoneIndex(boneName);
	if (-1 == iBoneIdx)
		assert(NULL);

	FbxAMatrix matNodeTransform = manager->GetTransform(_pMesh->GetNode());

	// Weights And Indices 정보를 읽는다.
	manager->LoadWeightsAndIndices(pCluster, iBoneIdx, _pContainer);

	// Bone 의 OffSet 행렬 구한다.
	manager->LoadOffsetMatrix(pCluster, matNodeTransform, iBoneIdx, _pContainer);

	// Bone KeyFrame 별 행렬을 구한다.
	manager->LoadKeyframeTransform(fbxScene, _pMesh->GetNode(),
		pCluster, matNodeTransform, iBoneIdx, _pContainer);
	return 0;
}

void FBXLoadManager::lodeMaterial(FbxSurfaceMaterial* _pMtrlSur)
{
	tFbxMaterial tMtrlInfo{};

	std::string str = _pMtrlSur->GetName();
	tMtrlInfo.strMtrlName = std::wstring(str.begin(), str.end());

	// Diff
	tMtrlInfo.tMtrl.vDiff = GetMtrlData(_pMtrlSur
		, FbxSurfaceMaterial::sDiffuse
		, FbxSurfaceMaterial::sDiffuseFactor);

	// Amb
	tMtrlInfo.tMtrl.vAmb = GetMtrlData(_pMtrlSur
		, FbxSurfaceMaterial::sAmbient
		, FbxSurfaceMaterial::sAmbientFactor);

	// Spec
	tMtrlInfo.tMtrl.vSpec = GetMtrlData(_pMtrlSur
		, FbxSurfaceMaterial::sSpecular
		, FbxSurfaceMaterial::sSpecularFactor);

	// Emisv
	tMtrlInfo.tMtrl.vEmv = GetMtrlData(_pMtrlSur
		, FbxSurfaceMaterial::sEmissive
		, FbxSurfaceMaterial::sEmissiveFactor);

	// Texture Name
	tMtrlInfo.strDiff = GetMtrlTextureName(_pMtrlSur, FbxSurfaceMaterial::sDiffuse);
	tMtrlInfo.strNormal = GetMtrlTextureName(_pMtrlSur, FbxSurfaceMaterial::sNormalMap);
	tMtrlInfo.strSpec = GetMtrlTextureName(_pMtrlSur, FbxSurfaceMaterial::sSpecular);
	tMtrlInfo.strEmis = GetMtrlTextureName(_pMtrlSur, FbxSurfaceMaterial::sEmissive);


	mVecContainer.back().vecMtrl.push_back(tMtrlInfo);
}

void FBXLoadManager::loadTextrue()
{
	for (UINT i = 0; i < mVecContainer.size(); ++i)
	{

		for (UINT j = 0; j < mVecContainer[i].vecMtrl.size(); ++j)
		{
			std::vector<std::wstring> vecPath;
			vecPath.push_back(mVecContainer[i].vecMtrl[j].strDiff.c_str());
			vecPath.push_back(mVecContainer[i].vecMtrl[j].strNormal.c_str());
			vecPath.push_back(mVecContainer[i].vecMtrl[j].strSpec.c_str());
			vecPath.push_back(mVecContainer[i].vecMtrl[j].strEmis.c_str());

			for (std::wstring path : vecPath)
			{

			}
		}
	}
}

void FBXLoadManager::loadSkeleton(FbxNode* rootNode)
{
	const int CHILD_COUNT = rootNode->GetChildCount();
	for (int i = 0; i < CHILD_COUNT; ++i)
	{
		FbxNode* currNode = rootNode->GetChild(i);
		loadSkeletonRe(currNode, 0, 0, -1);
	}
}

void FBXLoadManager::loadSkeletonRe(FbxNode* _pNode, int depth, int Idx, int parentIdx)
{
	FbxNodeAttribute* const attr = _pNode->GetNodeAttribute();

	if (attr && attr->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		tBone* const bone = new tBone;

		std::string boneName = _pNode->GetName();

		bone->boneName = std::wstring(boneName.begin(), boneName.end());
		bone->depth = depth++;
		bone->parentIdx = parentIdx;

		m_vecBone.push_back(bone);
	}

	const int CHILD_COUNT = _pNode->GetChildCount();
	for (int i = 0; i < CHILD_COUNT; ++i)
	{
		loadSkeletonRe(_pNode->GetChild(i), depth, (int)m_vecBone.size(), Idx);
	}
}

void FBXLoadManager::loadAnimationClip(FbxScene* const fbxScene)
{
	int iAnimCount = m_arrAnimName.GetCount();

 	for (int i = 0; i < iAnimCount; ++i)
	{
		FbxAnimStack* pAnimStack = fbxScene->FindMember<FbxAnimStack>(m_arrAnimName[i]->Buffer());


		//FbxAnimEvaluator* pevaluator = m_pScene->GetAnimationEvaluator();
		//m_pScene->SetCurrentAnimationStack();


		if (!pAnimStack)
			continue;

		tAnimClip* pAnimClip = new tAnimClip;

		std::string strClipName = pAnimStack->GetName();
		pAnimClip->strName = std::wstring(strClipName.begin(), strClipName.end());

		FbxTakeInfo* pTakeInfo = fbxScene->GetTakeInfo(pAnimStack->GetName());
		pAnimClip->tStartTime = pTakeInfo->mLocalTimeSpan.GetStart();
		pAnimClip->tEndTime = pTakeInfo->mLocalTimeSpan.GetStop();

		pAnimClip->eMode = fbxScene->GetGlobalSettings().GetTimeMode();
		pAnimClip->llTimeLength = pAnimClip->tEndTime.GetFrameCount(pAnimClip->eMode) - 
			pAnimClip->tStartTime.GetFrameCount(pAnimClip->eMode);



		m_vecAnimClip.push_back(pAnimClip);
	}
}

void FBXLoadManager::loadAnimationData(FbxScene* const fbxScene, FbxMesh* _pMesh, tContainer* _pContainer)
{
	// Animation Data 로드할 필요가 없음
	int iSkinCount = _pMesh->GetDeformerCount(FbxDeformer::eSkin);
	if (iSkinCount <= 0 || m_vecAnimClip.empty())
		return;

	_pContainer->bAnimation = true;

	// Skin 개수만큼 반복을하며 읽는다.	
	for (int i = 0; i < iSkinCount; ++i)
	{
		FbxSkin* pSkin = (FbxSkin*)_pMesh->GetDeformer(i, FbxDeformer::eSkin);

		if (pSkin)
		{
			FbxSkin::EType eType = pSkin->GetSkinningType();
			if (FbxSkin::eRigid == eType || FbxSkin::eLinear)
			{
				// Cluster 를 얻어온다
				// Cluster == Joint == 관절
				int iClusterCount = pSkin->GetClusterCount();
				//CreateThread(nullptr)

				//HANDLE handles[10000] = { 0, };
				//BYTE pbs[10000][44];

				for (int j = 0; j < iClusterCount; ++j)
				{
					//BYTE* pb = pbs[j];
					//
					//*(unsigned long long*)(pb)      = (unsigned long long)pSkin;
					//*(unsigned long long*)(pb + 8)  = (unsigned long long)fbxScene;
					//*(unsigned long long*)(pb + 16) = (unsigned long long)_pMesh;
					//*(unsigned long long*)(pb + 24) = (unsigned long long)_pContainer;
					//*(unsigned long long*)(pb + 32) = (unsigned long long)this;
					//*(int*)(pb + 40)				= j;
					//
					////SecondThread(pb);
					//DWORD ThreadID;
					//handles[j] = CreateThread(nullptr, 0, SecondThread, (PVOID)pb, 0, &ThreadID);

					//ThreadFunc(pb);
					//delete pb;
					FbxCluster* pCluster = pSkin->GetCluster(j);

					if (!pCluster->GetLink())
						continue;

					// 현재 본 인덱스를 얻어온다.
					std::string boneName = pCluster->GetLink()->GetName();
					int iBoneIdx = FindBoneIndex(boneName);
					if (-1 == iBoneIdx)
						assert(NULL);

					FbxAMatrix matNodeTransform = GetTransform(_pMesh->GetNode());

					// Weights And Indices 정보를 읽는다.
					LoadWeightsAndIndices(pCluster, iBoneIdx, _pContainer);

					// Bone 의 OffSet 행렬 구한다.
					LoadOffsetMatrix(pCluster, matNodeTransform, iBoneIdx, _pContainer);

					// Bone KeyFrame 별 행렬을 구한다.
					LoadKeyframeTransform(fbxScene, _pMesh->GetNode(), 
						pCluster, matNodeTransform, iBoneIdx, _pContainer);
				}

				for (int i = 0; i < iClusterCount; ++i)
				{
					//WaitForSingleObject(handles[i], INFINITE);
				}
			}
		}
	}
	CheckWeightAndIndices(_pMesh, _pContainer);
}

int FBXLoadManager::FindBoneIndex(std::string _strBoneName)
{
	std::wstring strBoneName = std::wstring(_strBoneName.begin(), _strBoneName.end());

	for (UINT i = 0; i < m_vecBone.size(); ++i)
	{
		if (m_vecBone[i]->boneName == strBoneName)
		{
			return i;
		}			
	}

	return -1;	
}

void FBXLoadManager::LoadWeightsAndIndices(const FbxCluster* _pCluster, int _iBoneIdx, tContainer* _pContainer)
{
	int iIndicesCount = _pCluster->GetControlPointIndicesCount();

	for (int i = 0; i < iIndicesCount; ++i)
	{
		tWeightsAndIndices tWI = {};

		// 각 정점에게 본 인덱스 정보와, 가중치 값을 알린다.
		tWI.iBoneIdx = _iBoneIdx;
		tWI.dWeight = _pCluster->GetControlPointWeights()[i];

		int iVtxIdx = _pCluster->GetControlPointIndices()[i];

		_pContainer->vecWI[iVtxIdx].push_back(tWI);
	}
}

void FBXLoadManager::LoadOffsetMatrix(FbxCluster* _pCluster, 
	const FbxAMatrix& _matNodeTransform, 
	int _iBoneIdx, 
	tContainer* _pContainer)
{
	FbxAMatrix matClusterTrans;
	FbxAMatrix matClusterLinkTrans;

	_pCluster->GetTransformMatrix(matClusterTrans);
	_pCluster->GetTransformLinkMatrix(matClusterLinkTrans);

	// Reflect Matrix
	FbxVector4 V0 = { 1, 0, 0, 0 };
	FbxVector4 V1 = { 0, 0, 1, 0 };
	FbxVector4 V2 = { 0, 1, 0, 0 };
	FbxVector4 V3 = { 0, 0, 0, 1 };

	FbxAMatrix matReflect;
	matReflect[0] = V0;
	matReflect[1] = V1;
	matReflect[2] = V2;
	matReflect[3] = V3;

	FbxAMatrix matOffset;
	matOffset = matClusterLinkTrans.Inverse() * matClusterTrans * _matNodeTransform;
	matOffset = matReflect * matOffset * matReflect;

	m_vecBone[_iBoneIdx]->matOffset = matOffset;
}

void FBXLoadManager::LoadKeyframeTransform(FbxScene* const fbxScene,
	FbxNode* _pNode,
	FbxCluster* _pCluster, 
	const FbxAMatrix& _matNodeTransform, 
	int _iBoneIdx, 
	tContainer* _pContainer)
{
	if (m_vecAnimClip.empty())
		return;

	FbxVector4	v1 = { 1, 0, 0, 0 };
	FbxVector4	v2 = { 0, 0, 1, 0 };
	FbxVector4	v3 = { 0, 1, 0, 0 };
	FbxVector4	v4 = { 0, 0, 0, 1 };
	FbxAMatrix	matReflect;
	matReflect.mData[0] = v1;
	matReflect.mData[1] = v2;
	matReflect.mData[2] = v3;
	matReflect.mData[3] = v4;

	m_vecBone[_iBoneIdx]->matBone = _matNodeTransform;

	FbxTime::EMode eTimeMode = fbxScene->GetGlobalSettings().GetTimeMode();


	// 모든 AnimClip 의 행렬정보를 연산해서 하나의 프레임행렬 데이터 만들기
	for (size_t i = 0; i < m_vecAnimClip.size(); ++i)
	{
		// 애님 클립 이름으로 FbxAnimStack 정보를 찾는다.
		std::string strClipName = std::string(m_vecAnimClip[i]->strName.begin(), m_vecAnimClip[i]->strName.end());
		FbxAnimStack* pAnimStack = fbxScene->FindMember<FbxAnimStack>(strClipName.c_str());

		// 현재 AnimStack 을 변경한다.
		fbxScene->SetCurrentAnimationStack(pAnimStack);

		// 현재 Animstiack 의 행렬정보를 연산해서 Bone 에 프레임별 행렬정보를 채운다.
		FbxLongLong llStartFrame = m_vecAnimClip[i]->tStartTime.GetFrameCount(eTimeMode);
		FbxLongLong llEndFrame = m_vecAnimClip[i]->tEndTime.GetFrameCount(eTimeMode);

		for (FbxLongLong i = llStartFrame; i < llEndFrame; ++i)
		{
			tKeyFrame tFrame = {};
			FbxTime   tTime = 0;

			tTime.SetFrame(i, eTimeMode);

			FbxAMatrix matFromNode = _pNode->EvaluateGlobalTransform(tTime) * _matNodeTransform;
			FbxAMatrix matCurTrans = matFromNode.Inverse() * _pCluster->GetLink()->EvaluateGlobalTransform(tTime);
			matCurTrans = matReflect * matCurTrans * matReflect;

			tFrame.dTime = tTime.GetSecondDouble();
			tFrame.matTransform = matCurTrans;

			m_vecBone[_iBoneIdx]->vecKeyFrame.push_back(tFrame);
		}
	}
}

void FBXLoadManager::CheckWeightAndIndices(FbxMesh* _pMesh, tContainer* _pContainer)
{
	std::vector<std::vector<tWeightsAndIndices>>::iterator iter = _pContainer->vecWI.begin();

	int iVtxIdx = 0;
	for (iter; iter != _pContainer->vecWI.end(); ++iter, ++iVtxIdx)
	{
		if ((*iter).size() > 1)
		{
			// 가중치 값 순으로 내림차순 정렬
			std::sort((*iter).begin(), (*iter).end()
				, [](const tWeightsAndIndices& left, const tWeightsAndIndices& right)
				{
					return left.dWeight > right.dWeight;
				}
			);

			double dWeight = 0.f;
			for (UINT i = 0; i < (*iter).size(); ++i)
			{
				dWeight += (*iter)[i].dWeight;
			}

			// 가중치의 합이 1이 넘어가면 처음부분에 더해준다.
			double revision = 0.f;
			if (dWeight > 1.0)
			{
				revision = 1.0 - dWeight;
				(*iter)[0].dWeight += revision;
			}

			if ((*iter).size() >= 4)
			{
				(*iter).erase((*iter).begin() + 4, (*iter).end());
			}
		}

		// 정점 정보로 변환, 
		float fWeights[4] = {};
		float fIndices[4] = {};

		for (UINT i = 0; i < (*iter).size(); ++i)
		{
			fWeights[i] = (float)(*iter)[i].dWeight;
			fIndices[i] = (float)(*iter)[i].iBoneIdx;
		}

		memcpy(&_pContainer->vecWeights[iVtxIdx], fWeights, sizeof(Vector4));
		memcpy(&_pContainer->vecIndices[iVtxIdx], fIndices, sizeof(Vector4));
	}
}

FbxAMatrix FBXLoadManager::GetTransform(FbxNode* _pNode)
{
	const FbxVector4 vT = _pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	const FbxVector4 vR = _pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	const FbxVector4 vS = _pNode->GetGeometricScaling(FbxNode::eSourcePivot);

	return FbxAMatrix(vT, vR, vS);
}

void FBXLoadManager::loadMeshDataFromNode(FbxScene* const fbxScene, FbxNode* fbxNode)
{
	// 노드의 메쉬정보 읽기
	FbxNodeAttribute* pAttr = fbxNode->GetNodeAttribute();

	if (pAttr && FbxNodeAttribute::eMesh == pAttr->GetAttributeType())
	{
		FbxAMatrix matGlobal = fbxNode->EvaluateGlobalTransform();
		matGlobal.GetR();

		FbxMesh* pMesh = fbxNode->GetMesh();
		if (NULL != pMesh)
		{
			lodeMesh(fbxScene, pMesh);
		}			
	}

	// 해당 노드의 재질정보 읽기
	const int MTRL_COUNT = fbxNode->GetMaterialCount();
	for (int i = 0; i < MTRL_COUNT; ++i)
	{
		FbxSurfaceMaterial* pMtrlSur = fbxNode->GetMaterial(i);
		lodeMaterial(pMtrlSur);
	}

	// 자식 노드 정보 읽기
	const int CHILD_COUNT = fbxNode->GetChildCount();
	for (int i = 0; i < CHILD_COUNT; ++i)
	{
		loadMeshDataFromNode(fbxScene, fbxNode->GetChild(i));
	}
}


void FBXLoadManager::GetTangent(FbxMesh* _pMesh
	, tContainer* _pContainer
	, int _iIdx		 /*해당 정점의 인덱스*/
	, int _iVtxOrder /*폴리곤 단위로 접근하는 순서*/)
{
	const int TANGENT_COUNT = _pMesh->GetElementTangentCount();

	if (1 > TANGENT_COUNT)
	{
		return;
	}

	if (1 < TANGENT_COUNT)
		assert(NULL); // 정점 1개가 포함하는 탄젠트 정보가 2개 이상이다.

	// 탄젠트 data 의 시작 주소
	FbxGeometryElementTangent* pTangent = _pMesh->GetElementTangent();
	UINT iTangentIdx = 0;

	if (pTangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (pTangent->GetReferenceMode() == FbxGeometryElement::eDirect)
			iTangentIdx = _iVtxOrder;
		else
			iTangentIdx = pTangent->GetIndexArray().GetAt(_iVtxOrder);
	}
	else if (pTangent->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (pTangent->GetReferenceMode() == FbxGeometryElement::eDirect)
			iTangentIdx = _iIdx;
		else
			iTangentIdx = pTangent->GetIndexArray().GetAt(_iIdx);
	}

	FbxVector4 vTangent = pTangent->GetDirectArray().GetAt(iTangentIdx);

	_pContainer->vecTangent[_iIdx].x = (float)vTangent.mData[0];
	_pContainer->vecTangent[_iIdx].y = (float)vTangent.mData[2];
	_pContainer->vecTangent[_iIdx].z = (float)vTangent.mData[1];
}

void FBXLoadManager::GetBinormal(FbxMesh* _pMesh, tContainer* _pContainer, int _iIdx, int _iVtxOrder)
{
	int iBinormalCnt = _pMesh->GetElementBinormalCount();
	if (1 > iBinormalCnt)
	{
		return;
	}

	if (1 != iBinormalCnt)
		assert(NULL); // 정점 1개가 포함하는 종법선 정보가 2개 이상이다.

	// 종법선 data 의 시작 주소
	FbxGeometryElementBinormal* pBinormal = _pMesh->GetElementBinormal();
	UINT iBinormalIdx = 0;

	if (pBinormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (pBinormal->GetReferenceMode() == FbxGeometryElement::eDirect)
			iBinormalIdx = _iVtxOrder;
		else
			iBinormalIdx = pBinormal->GetIndexArray().GetAt(_iVtxOrder);
	}
	else if (pBinormal->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (pBinormal->GetReferenceMode() == FbxGeometryElement::eDirect)
			iBinormalIdx = _iIdx;
		else
			iBinormalIdx = pBinormal->GetIndexArray().GetAt(_iIdx);
	}

	FbxVector4 vBinormal = pBinormal->GetDirectArray().GetAt(iBinormalIdx);

	_pContainer->vecBinormal[_iIdx].x = (float)vBinormal.mData[0];
	_pContainer->vecBinormal[_iIdx].y = (float)vBinormal.mData[2];
	_pContainer->vecBinormal[_iIdx].z = (float)vBinormal.mData[1];
}

void FBXLoadManager::GetNormal(FbxMesh* _pMesh, tContainer* _pContainer, int _iIdx, int _iVtxOrder)
{
	int iNormalCnt = _pMesh->GetElementNormalCount();
	if (1 != iNormalCnt)
		assert(NULL); // 정점 1개가 포함하는 종법선 정보가 2개 이상이다.

	// 종법선 data 의 시작 주소
	FbxGeometryElementNormal* pNormal = _pMesh->GetElementNormal();
	UINT iNormalIdx = 0;

	if (pNormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (pNormal->GetReferenceMode() == FbxGeometryElement::eDirect)
			iNormalIdx = _iVtxOrder;
		else
			iNormalIdx = pNormal->GetIndexArray().GetAt(_iVtxOrder);
	}
	else if (pNormal->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (pNormal->GetReferenceMode() == FbxGeometryElement::eDirect)
			iNormalIdx = _iIdx;
		else
			iNormalIdx = pNormal->GetIndexArray().GetAt(_iIdx);
	}

	FbxVector4 vNormal = pNormal->GetDirectArray().GetAt(iNormalIdx);

	_pContainer->vecNormal[_iIdx].x = (float)vNormal.mData[0];
	_pContainer->vecNormal[_iIdx].y = (float)vNormal.mData[2];
	_pContainer->vecNormal[_iIdx].z = (float)vNormal.mData[1];
}

void FBXLoadManager::GetUV(FbxMesh* _pMesh, tContainer* _pContainer, int _iIdx, int _iUVIndex)
{
	FbxGeometryElementUV* pUV = _pMesh->GetElementUV();

	UINT iUVIdx = 0;
	if (pUV->GetReferenceMode() == FbxGeometryElement::eDirect)
		iUVIdx = _iIdx;
	else
		iUVIdx = pUV->GetIndexArray().GetAt(_iIdx);

	iUVIdx = _iUVIndex;
	FbxVector2 vUV = pUV->GetDirectArray().GetAt(iUVIdx);
	_pContainer->vecUV[_iIdx].x = (float)vUV.mData[0];
	_pContainer->vecUV[_iIdx].y = 1.f - (float)vUV.mData[1]; // fbx uv 좌표계는 좌하단이 0,0
}
