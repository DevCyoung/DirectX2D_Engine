#include "pch.h"
#include "FBXLoader.h"
#include "PathManager.h"
#include <FBXLoader/FBXLoadManager.h>
#include "StructVertex.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "Mesh.h"

#ifdef _DEBUG
#pragma comment(lib, "FBXLoader/Debug/FBXLoader_d")
#else
#pragma comment(lib, "FBXLoader/Release/FBXLoader")
#endif

void FBXLoader::LoadFBX(const std::wstring& relativePath)
{
	std::wstring filePath = PathManager::GetInstance()->GetResourcePath();
	filePath += relativePath;

	FBXLoadManager::GetInstance()->Load(filePath);

}

void FBXLoader::CreateMeshFromFBX()
{


	// Animation3D
	//if (!container->bAnimation)
	//	return pMesh;

	//vector<tBone*>& vecBone = _loader.GetBones();
	//UINT iFrameCount = 0;
	//for (UINT i = 0; i < vecBone.size(); ++i)
	//{
	//	tMTBone bone = {};
	//	bone.iDepth = vecBone[i]->iDepth;
	//	bone.iParentIndx = vecBone[i]->iParentIndx;
	//	bone.matBone = GetMatrixFromFbxMatrix(vecBone[i]->matBone);
	//	bone.matOffset = GetMatrixFromFbxMatrix(vecBone[i]->matOffset);
	//	bone.strBoneName = vecBone[i]->strBoneName;

	//	for (UINT j = 0; j < vecBone[i]->vecKeyFrame.size(); ++j)
	//	{
	//		tMTKeyFrame tKeyframe = {};
	//		tKeyframe.dTime = vecBone[i]->vecKeyFrame[j].dTime;
	//		tKeyframe.iFrame = j;
	//		tKeyframe.vTranslate.x = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetT().mData[0];
	//		tKeyframe.vTranslate.y = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetT().mData[1];
	//		tKeyframe.vTranslate.z = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetT().mData[2];

	//		tKeyframe.vScale.x = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetS().mData[0];
	//		tKeyframe.vScale.y = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetS().mData[1];
	//		tKeyframe.vScale.z = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetS().mData[2];

	//		tKeyframe.qRot.x = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetQ().mData[0];
	//		tKeyframe.qRot.y = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetQ().mData[1];
	//		tKeyframe.qRot.z = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetQ().mData[2];
	//		tKeyframe.qRot.w = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetQ().mData[3];

	//		bone.vecKeyFrame.push_back(tKeyframe);
	//	}

	//	iFrameCount = max(iFrameCount, (UINT)bone.vecKeyFrame.size());

	//	pMesh->m_vecBones.push_back(bone);
	//}

	//vector<tAnimClip*>& vecAnimClip = _loader.GetAnimClip();

	//for (UINT i = 0; i < vecAnimClip.size(); ++i)
	//{
	//	tMTAnimClip tClip = {};

	//	tClip.strAnimName = vecAnimClip[i]->strName;
	//	tClip.dStartTime = vecAnimClip[i]->tStartTime.GetSecondDouble();
	//	tClip.dEndTime = vecAnimClip[i]->tEndTime.GetSecondDouble();
	//	tClip.dTimeLength = tClip.dEndTime - tClip.dStartTime;

	//	tClip.iStartFrame = (int)vecAnimClip[i]->tStartTime.GetFrameCount(vecAnimClip[i]->eMode);
	//	tClip.iEndFrame = (int)vecAnimClip[i]->tEndTime.GetFrameCount(vecAnimClip[i]->eMode);
	//	tClip.iFrameLength = tClip.iEndFrame - tClip.iStartFrame;
	//	tClip.eMode = vecAnimClip[i]->eMode;

	//	pMesh->m_vecAnimClip.push_back(tClip);
	//}

	//// Animation 이 있는 Mesh 경우 structuredbuffer 만들어두기
	//if (pMesh->IsAnimMesh())
	//{
	//	// BoneOffet 행렬
	//	vector<Matrix> vecOffset;
	//	vector<tFrameTrans> vecFrameTrans;
	//	vecFrameTrans.resize((UINT)pMesh->m_vecBones.size() * iFrameCount);

	//	for (size_t i = 0; i < pMesh->m_vecBones.size(); ++i)
	//	{
	//		vecOffset.push_back(pMesh->m_vecBones[i].matOffset);

	//		for (size_t j = 0; j < pMesh->m_vecBones[i].vecKeyFrame.size(); ++j)
	//		{
	//			vecFrameTrans[(UINT)pMesh->m_vecBones.size() * j + i]
	//				= tFrameTrans{ Vec4(pMesh->m_vecBones[i].vecKeyFrame[j].vTranslate, 0.f)
	//				, Vec4(pMesh->m_vecBones[i].vecKeyFrame[j].vScale, 0.f)
	//				, pMesh->m_vecBones[i].vecKeyFrame[j].qRot };
	//		}
	//	}

	//	pMesh->m_pBoneOffset = new CStructuredBuffer;
	//	pMesh->m_pBoneOffset->Create(sizeof(Matrix), (UINT)vecOffset.size(), SB_TYPE::READ_ONLY, false, vecOffset.data());

	//	pMesh->m_pBoneFrameData = new CStructuredBuffer;
	//	pMesh->m_pBoneFrameData->Create(sizeof(tFrameTrans), (UINT)vecOffset.size() * iFrameCount
	//		, SB_TYPE::READ_ONLY, false, vecFrameTrans.data());
	//}

	//return nullptr;
}
