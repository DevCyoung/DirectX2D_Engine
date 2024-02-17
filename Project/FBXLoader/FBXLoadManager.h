#pragma once
#include "define.h"
#include <Engine\StructBuffer.h>
#include <FBXLoader\fbxsdk.h>

using namespace fbxsdk;

//#include "fbxsdk.h"

struct tFbxMaterial
{
	tMtrlData			tMtrl;
	std::wstring		strMtrlName;
	std::wstring		strDiff;
	std::wstring		strNormal;
	std::wstring		strSpec;
	std::wstring		strEmis;
};

struct tKeyFrame
{
	FbxAMatrix  matTransform;
	double		dTime;
};

struct tBone
{
	std::wstring			strBoneName;
	int						iDepth;			// °èÃþ±¸Á¶ ±íÀÌ
	int						iParentIndx;	// ºÎ¸ð Bone ÀÇ ÀÎµ¦½º
	FbxAMatrix				matOffset;		// Offset Çà·Ä( -> »Ñ¸® -> Local)
	FbxAMatrix				matBone;
	std::vector<tKeyFrame>	vecKeyFrame;
};

struct tAnimClip
{
	std::wstring		strName;
	FbxTime				tStartTime;
	FbxTime				tEndTime;
	FbxLongLong			llTimeLength;
	FbxTime::EMode		eMode;
};

struct tWeightsAndIndices
{
	int		iBoneIdx;
	double	dWeight;
};

struct tContainer
{
	std::wstring									strName;
	std::vector<Vector3>							vecPos;
	std::vector<Vector3>							vecTangent;
	std::vector<Vector3>							vecBinormal;
	std::vector<Vector3>							vecNormal;
	std::vector<Vector2>							vecUV;
	std::vector<Vector4>							vecIndices;
	std::vector<Vector4>							vecWeights;

	std::vector<std::vector<UINT>>					vecIdx;
	std::vector<tFbxMaterial>						vecMtrl;

	// Animation °ü·Ã Á¤º¸
	bool											bAnimation;
	std::vector<std::vector<tWeightsAndIndices>>	vecWI;

	void Resize(UINT _iSize)
	{
		vecPos.resize(_iSize);
		vecTangent.resize(_iSize);
		vecBinormal.resize(_iSize);
		vecNormal.resize(_iSize);
		vecUV.resize(_iSize);
		vecIndices.resize(_iSize);
		vecWeights.resize(_iSize);
		vecWI.resize(_iSize);
	}
};



class FBXLoadManager
{
	PUBLIC_SINGLETON_DECLARE(FBXLoadManager);

public:
	
	void Load(const std::wstring& filePath);

	void triangulate(FbxNode* _pNode);
	void loadMeshDataFromNode(FbxNode* fbxNode);
	void lodeMesh(FbxMesh* _pFbxMesh);
	void lodeMaterial(FbxSurfaceMaterial* _pMtrlSur);
	void loadTextrue();
	void loadSkeleton(FbxNode* rootNode);
	void loadSkeletonRe(FbxNode* _pNode, int _iDepth, int _iIdx, int _iParentIdx);

	void GetBinormal(FbxMesh* _pMesh, tContainer* _pContainer, int _iIdx, int _iVtxOrder);
	void GetTangent(FbxMesh* _pMesh, tContainer* _pContainer, int _iIdx, int _iVtxOrder);
	void GetNormal(FbxMesh* _pMesh, tContainer* _pContainer, int _iIdx, int _iVtxOrder);
	void GetUV(FbxMesh* _pMesh, tContainer* _pContainer, int _iIdx, int _iVtxOrder);
	Vector4 GetMtrlData(FbxSurfaceMaterial* _pSurface, 
		const char* _pMtrlName,
		const char* _pMtrlFactorName);

	std::wstring GetMtrlTextureName(FbxSurfaceMaterial* _pSurface, const char* _pMtrlProperty);
	
	const tContainer& GetContainer(const int idx) const { return mVecContainer[idx]; }


	// Animation
	std::vector<tBone*>					m_vecBone;
	FbxArray<FbxString*>				m_arrAnimName;
	std::vector<tAnimClip*>				m_vecAnimClip;

	fbxsdk::FbxManager* mFbxManager;
	fbxsdk::FbxIOSettings* mIos;
	//fbxsdk::FbxImporter* mImpoter;

	std::vector<tContainer>				mVecContainer;
};