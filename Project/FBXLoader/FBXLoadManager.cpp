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

		//삼각화
		triangulate(fbxScene->GetRootNode());

		// 메쉬 데이터 얻기
		loadMeshDataFromNode(fbxScene->GetRootNode());

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
void FBXLoadManager::lodeMesh(FbxMesh* FbxMesh)
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

	//LoadAnimationData(_pFbxMesh, &Container);	
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

void FBXLoadManager::loadMeshDataFromNode(FbxNode* fbxNode)
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
			lodeMesh(pMesh);
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
		loadMeshDataFromNode(fbxNode->GetChild(i));
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
