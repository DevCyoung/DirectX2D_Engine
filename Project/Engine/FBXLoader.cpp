#include "pch.h"
#include "FBXLoader.h"
#include "PathManager.h"
#include <FBXLoader/FBXLoadManager.h>
#include "StructVertex.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "Mesh.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "EnumRenderType.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"
#include <Shlwapi.h>
#include "StructuredBuffer.h"
#include "Animator3D.h"
//#include ""

#ifdef _DEBUG
#pragma comment(lib, "FBXLoader/Debug/FBXLoader_d")
#else
#pragma comment(lib, "FBXLoader/Release/FBXLoader")
#endif

#pragma comment(lib, "shlwapi")

//Shlwapi.lib

void FBXLoader::LoadFBX(const std::wstring& relativePath)
{
	std::wstring filePath = PathManager::GetInstance()->GetResourcePath();
	filePath += relativePath;

	FBXLoadManager::GetInstance()->Load(filePath);
	//FbxInstantiate(relativePath);

	//CreateMeshFromFBX();
	//FBXLoader::FbxInstantiate(relativePath);
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

Matrix GetMatrixFromFbxMatrix(FbxAMatrix& _mat)
{
	Matrix mat;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat.m[i][j] = (float)_mat.Get(i, j);
		}
	}
	return mat;
}

GameObject* FBXLoader::FbxInstantiate(const std::wstring& relativePath)
{
	std::wstring filePath = PathManager::GetInstance()->GetResourcePath();
	filePath += relativePath;
	FBXLoadManager::GetInstance()->Load(filePath);

	GameObject* obj = new GameObject();

	obj->AddComponent<MeshRenderer>();

	FBXLoadManager* const fbxLoadManager = FBXLoadManager::GetInstance();

	const tContainer& container = fbxLoadManager->GetContainer(0);
	const UINT VERTEX_COUNT = (UINT)container.vecPos.size();

	std::vector<tVertex> vertexBuffer;
	std::vector<size_t> sizes;
	std::vector<UINT> indexBuffers;

	Assert(!container.vecPos.empty(), ASSERT_MSG_INVALID);
	Assert(!container.vecIdx.empty(), ASSERT_MSG_INVALID);

	vertexBuffer.resize(VERTEX_COUNT);
	for (UINT i = 0; i < VERTEX_COUNT; ++i)
	{
		vertexBuffer[i].Position = container.vecPos[i];
		vertexBuffer[i].UV = container.vecUV[i];
		vertexBuffer[i].Color = Vector4(1.f, 0.f, 1.f, 1.f);
		vertexBuffer[i].Normal = container.vecNormal[i];
		vertexBuffer[i].Tangent = container.vecTangent[i];
		vertexBuffer[i].Binormal = container.vecBinormal[i];
		vertexBuffer[i].vWeights = container.vecWeights[i];
		vertexBuffer[i].vIndices = container.vecIndices[i];
	}

	indexBuffers.reserve(VERTEX_COUNT);
	for (const std::vector<UINT>& indexeBuffer : container.vecIdx)
	{
		for (UINT index : indexeBuffer)
		{
			indexBuffers.push_back(index);
		}
	}

	sizes.reserve(container.vecIdx.size());
	for (const std::vector<UINT>& indexeBuffer : container.vecIdx)
	{
		sizes.push_back(indexeBuffer.size());
	}

	Mesh* mesh = new Mesh(vertexBuffer.data(),
		VERTEX_COUNT,
		sizeof(tVertex),
		indexBuffers.data(),
		sizes.data(),
		container.vecIdx.size(),
		sizeof(UINT));

	
	std::wstring meshPath = relativePath;
	meshPath += L"Mesh";
	gResourceManager->Insert(meshPath, mesh);
	obj->GetComponent<MeshRenderer>()->SetMesh(mesh);

	Shader* shader =
		gResourceManager->FindAndLoad<Shader>(L"Std3D");

	for (UINT i = 0; i < container.vecMtrl.size(); ++i)
	{
		//FIXME
		if (mesh->GetIndexBufferCount() <= i)
		{
			continue;
		}

		Material* material = new Material();
		material->SetShader(shader);

		const std::wstring& resourcePath = gPathManager->GetResourcePath();

		std::vector<std::wstring> paths;

		paths.push_back(container.vecMtrl[i].strDiff);
		paths.push_back(container.vecMtrl[i].strNormal);
		paths.push_back(container.vecMtrl[i].strSpec);
		paths.push_back(container.vecMtrl[i].strEmis);

		for (int j = 0; j < paths.size(); ++j)
		{
			if (paths[j].empty())
			{
				continue;
			}

			std::wstring texRelativePath = paths[j].substr(resourcePath.size());
			if (texRelativePath.empty())
			{
				continue;
			}

			LPCWSTR lpcwstr = paths[j].c_str();
			if (!PathFileExistsW(lpcwstr))
			{
				continue;
			}
			else
			{
				Texture* tex = gResourceManager->FindAndLoadOrNull<Texture>(texRelativePath);
				material->SetTexture(TEX_PARAM(TEX_0 + j), tex);
			}			
		}

		std::wstring materialPath = relativePath;
		materialPath += L"Material_";
		materialPath += std::to_wstring(i);

		gResourceManager->Insert(materialPath, material);
		obj->GetComponent<MeshRenderer>()->SetMaterial(material, i);
	}

	// Animation3D
	if (!container.bAnimation)
	{
		return obj;
	}		

	obj->AddComponent<Animator3D>();



	std::vector<tBone*>& vecBone = fbxLoadManager->GetBones();
	UINT iFrameCount = 0;
	for (UINT i = 0; i < vecBone.size(); ++i)
	{
		tMTBone bone = {};
		bone.iDepth = vecBone[i]->depth;
		bone.iParentIndx = vecBone[i]->parentIdx;
		bone.matBone = GetMatrixFromFbxMatrix(vecBone[i]->matBone);
		bone.matOffset = GetMatrixFromFbxMatrix(vecBone[i]->matOffset);
		bone.strBoneName = vecBone[i]->boneName;
			
		for (UINT j = 0; j < vecBone[i]->vecKeyFrame.size(); ++j)
		{
			tMTKeyFrame tKeyframe = {};
			tKeyframe.dTime = vecBone[i]->vecKeyFrame[j].dTime;
			tKeyframe.iFrame = j;
			tKeyframe.vTranslate.x = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetT().mData[0];
			tKeyframe.vTranslate.y = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetT().mData[1];
			tKeyframe.vTranslate.z = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetT().mData[2];

			tKeyframe.vScale.x = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetS().mData[0];
			tKeyframe.vScale.y = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetS().mData[1];
			tKeyframe.vScale.z = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetS().mData[2];

			tKeyframe.qRot.x = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetQ().mData[0];
			tKeyframe.qRot.y = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetQ().mData[1];
			tKeyframe.qRot.z = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetQ().mData[2];
			tKeyframe.qRot.w = (float)vecBone[i]->vecKeyFrame[j].matTransform.GetQ().mData[3];

			bone.vecKeyFrame.push_back(tKeyframe);
		}

		iFrameCount = max(iFrameCount, (UINT)bone.vecKeyFrame.size());

		mesh->m_vecBones.push_back(bone);
	}

	std::vector<tAnimClip*>& vecAnimClip = fbxLoadManager->GetAnimationClips();

	for (UINT i = 0; i < vecAnimClip.size(); ++i)
	{
		tMTAnimClip tClip = {};

		tClip.strAnimName = vecAnimClip[i]->strName;
		tClip.dStartTime = vecAnimClip[i]->tStartTime.GetSecondDouble();
		tClip.dEndTime = vecAnimClip[i]->tEndTime.GetSecondDouble();
		tClip.dTimeLength = tClip.dEndTime - tClip.dStartTime;

		tClip.iStartFrame = (int)vecAnimClip[i]->tStartTime.GetFrameCount(vecAnimClip[i]->eMode);
		tClip.iEndFrame = (int)vecAnimClip[i]->tEndTime.GetFrameCount(vecAnimClip[i]->eMode);
		tClip.iFrameLength = tClip.iEndFrame - tClip.iStartFrame;
		tClip.eMode = vecAnimClip[i]->eMode;

		mesh->m_vecAnimClip.push_back(tClip);
	}

	// Animation 이 있는 Mesh 경우 structuredbuffer 만들어두기
	if (mesh->IsAnimMesh())
	{
		// BoneOffet 행렬
		std::vector<Matrix> vecOffset;
		std::vector<tFrameTrans> vecFrameTrans;
		vecFrameTrans.resize((UINT)mesh->m_vecBones.size() * iFrameCount);

		for (size_t i = 0; i < mesh->m_vecBones.size(); ++i)
		{
			vecOffset.push_back(mesh->m_vecBones[i].matOffset);

			for (size_t j = 0; j < mesh->m_vecBones[i].vecKeyFrame.size(); ++j)
			{
				vecFrameTrans[(UINT)mesh->m_vecBones.size() * j + i]
					= tFrameTrans{ Vector4(mesh->m_vecBones[i].vecKeyFrame[j].vTranslate.x,
										   mesh->m_vecBones[i].vecKeyFrame[j].vTranslate.y,
										   mesh->m_vecBones[i].vecKeyFrame[j].vTranslate.z, 0.f),
								   Vector4(mesh->m_vecBones[i].vecKeyFrame[j].vScale.x,
										   mesh->m_vecBones[i].vecKeyFrame[j].vScale.y,
										   mesh->m_vecBones[i].vecKeyFrame[j].vScale.z, 0.f)
					, mesh->m_vecBones[i].vecKeyFrame[j].qRot };
			}
		}

		mesh->m_pBoneOffset = new StructuredBuffer(eSBType::BoneOffset, 
			eSRVTpye::BoneOffset,
			sizeof(Matrix), 
			(UINT)vecOffset.size(),
			vecOffset.data(), 
			gGraphicDevice->UnSafe_GetDevice());
		
		mesh->m_pBoneFrameData = new StructuredBuffer(eSBType::BoneFrameData,
			eSRVTpye::BoneFrameData,
			sizeof(tFrameTrans),
			(UINT)vecOffset.size() * iFrameCount,
			vecFrameTrans.data(),
			gGraphicDevice->UnSafe_GetDevice());
	}

	obj->GetComponent<Animator3D>()->SetBones(mesh->GetBones());
	obj->GetComponent<Animator3D>()->SetAnimClip(mesh->GetAnimClip());

	return obj;
}
