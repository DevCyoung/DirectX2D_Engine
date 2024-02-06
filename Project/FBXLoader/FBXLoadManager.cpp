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
}void FBXLoadManager::lodeMesh(FbxMesh* _pFbxMesh)
{
	mVecContainer.push_back(tContainer{});
	tContainer& Container = mVecContainer[mVecContainer.size() - 1];

	std::string strName = _pFbxMesh->GetName();
	Container.strName = std::wstring(strName.begin(), strName.end());

	int iVtxCnt = _pFbxMesh->GetControlPointsCount();
	Container.Resize(iVtxCnt);

	FbxVector4* pFbxPos = _pFbxMesh->GetControlPoints();

	for (int i = 0; i < iVtxCnt; ++i)
	{
		Container.vecPos[i].x = (float)pFbxPos[i].mData[0];
		Container.vecPos[i].y = (float)pFbxPos[i].mData[2];
		Container.vecPos[i].z = (float)pFbxPos[i].mData[1];
	}

	// 폴리곤 개수
	int iPolyCnt = _pFbxMesh->GetPolygonCount();

	// 재질의 개수 ( ==> SubSet 개수 ==> Index Buffer Count)
	int iMtrlCnt = _pFbxMesh->GetNode()->GetMaterialCount();
	Container.vecIdx.resize(iMtrlCnt);

	// 정점 정보가 속한 subset 을 알기위해서...
	FbxGeometryElementMaterial* pMtrl = _pFbxMesh->GetElementMaterial();

	// 폴리곤을 구성하는 정점 개수
	int iPolySize = _pFbxMesh->GetPolygonSize(0);
	if (3 != iPolySize)
		assert(NULL); // Polygon 구성 정점이 3개가 아닌 경우

	UINT arrIdx[3] = {};
	UINT iVtxOrder = 0; // 폴리곤 순서로 접근하는 순번

	for (int i = 0; i < iPolyCnt; ++i)
	{
		for (int j = 0; j < iPolySize; ++j)
		{
			// i 번째 폴리곤에, j 번째 정점
			int iIdx = _pFbxMesh->GetPolygonVertex(i, j);
			arrIdx[j] = iIdx;

			GetTangent(_pFbxMesh, &Container, iIdx, iVtxOrder);
			GetBinormal(_pFbxMesh, &Container, iIdx, iVtxOrder);
			GetNormal(_pFbxMesh, &Container, iIdx, iVtxOrder);
			GetUV(_pFbxMesh, &Container, iIdx, _pFbxMesh->GetTextureUVIndex(i, j));

			++iVtxOrder;
		}
		UINT iSubsetIdx = pMtrl->GetIndexArray().GetAt(i);
		Container.vecIdx[iSubsetIdx].push_back(arrIdx[0]);
		Container.vecIdx[iSubsetIdx].push_back(arrIdx[2]);
		Container.vecIdx[iSubsetIdx].push_back(arrIdx[1]);
	}

	//LoadAnimationData(_pFbxMesh, &Container);
}

void FBXLoadManager::lodeMaterial(FbxSurfaceMaterial* _pMtrlSur)
{
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
			lodeMesh(pMesh);
	}

	// 해당 노드의 재질정보 읽기
	UINT iMtrlCnt = fbxNode->GetMaterialCount();
	if (iMtrlCnt > 0)
	{
		for (UINT i = 0; i < iMtrlCnt; ++i)
		{
			FbxSurfaceMaterial* pMtrlSur = fbxNode->GetMaterial(i);
			lodeMaterial(pMtrlSur);
		}
	}

	// 자식 노드 정보 읽기
	int iChildCnt = fbxNode->GetChildCount();
	for (int i = 0; i < iChildCnt; ++i)
	{
		loadMeshDataFromNode(fbxNode->GetChild(i));
	}
}

void FBXLoadManager::Load(const std::wstring& filePath)
{
	//장면가져오기
	{
		FbxImporter* imposter = FbxImporter::Create(mFbxManager, "");
		Assert(imposter, ASSERT_MSG_NULL);

		std::string cStr = std::string(filePath.cbegin(), filePath.cend()).c_str();
		const char* cFilePath = cStr.c_str();

		// Initialize the importer.
		bool lImportStatus = imposter->Initialize(cFilePath, -1, mFbxManager->GetIOSettings());
		Assert(lImportStatus, ASSERT_MSG_INVALID);

		//장면 가져오기		
		FbxScene* fbxScene = FbxScene::Create(mFbxManager, "");		
		Assert(fbxScene, ASSERT_MSG_NULL);
		imposter->Import(fbxScene);

		fbxScene->GetGlobalSettings().SetAxisSystem(FbxAxisSystem::Max);

		mVecContainer.clear();


		//삼각화
		triangulate(fbxScene->GetRootNode());

		// 메쉬 데이터 얻기
		loadMeshDataFromNode(fbxScene->GetRootNode());

		imposter->Destroy();
	}


}



void FBXLoadManager::GetTangent(FbxMesh* _pMesh
	, tContainer* _pContainer
	, int _iIdx		 /*해당 정점의 인덱스*/
	, int _iVtxOrder /*폴리곤 단위로 접근하는 순서*/)
{
	int iTangentCnt = _pMesh->GetElementTangentCount();
	if (1 != iTangentCnt)
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
