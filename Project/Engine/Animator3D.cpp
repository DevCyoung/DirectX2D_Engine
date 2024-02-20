#include "pch.h"
#include "Animator3D.h"
#include "StructuredBuffer.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Anim3DBuuferCopyCS.h"
#include "ResourceManager.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "EnumShaderBindStage.h"
#include "GameObject.h"
#include "StructuredBuffer.h"
#include "TimeManager.h"
Animator3D::Animator3D()
	: Component(eComponentType::Animator3D)
	, m_pVecBones(nullptr)
	, m_pVecClip(nullptr)
	, m_vecClipUpdateTime()
	, m_vecFinalBoneMat()
	, m_iFrameCount(30)
	, m_dCurTime(0)
	, m_iCurClip(0)
	, m_iFrameIdx(0)
	, m_iNextFrameIdx(0)
	, m_fRatio(0)
	, m_pBoneFinalMatBuffer(nullptr)
	, m_bFinalMatUpdate(false)
{
	//m_pBoneFinalMatBuffer = new StructuredBuffer(eSBType::BoneFinalBuffer, eSRVTpye::BoneFrameData, sizeof(Matrix),
		//100, nullptr, gGraphicDevice->UnSafe_GetDevice());
}

Animator3D::~Animator3D()
{
	delete m_pBoneFinalMatBuffer;
}

Animator3D::Animator3D(const Animator3D& other)
	: Component(eComponentType::Animator3D)
{
	(void)other;
}

void Animator3D::UpdateData()
{
	if (true)
	{
		// Animation3D Update Compute Shader
		Anim3DBuuferCopyCS* pUpdateShader =
			(Anim3DBuuferCopyCS*)gResourceManager->Find<ComputeShader>(L"Animation3DCS");
	
		// Bone Data
		Mesh* pMesh = GetComponent<MeshRenderer>()->GetMesh();

		//reSize
		check_mesh(pMesh);
	
		pUpdateShader->SetFrameDataBuffer(pMesh->GetBoneFrameDataBuffer());
		pUpdateShader->SetOffsetMatBuffer(pMesh->GetBoneOffsetBuffer());
		pUpdateShader->SetOutputBuffer(m_pBoneFinalMatBuffer);
	
		UINT iBoneCount = (UINT)m_pVecBones->size();
		pUpdateShader->SetBoneCount(iBoneCount);
		pUpdateShader->SetFrameIndex(m_iFrameIdx);
		pUpdateShader->SetNextFrameIdx(m_iNextFrameIdx);
		pUpdateShader->SetFrameRatio(m_fRatio);
	
		// ������Ʈ ���̴� ����	
		//pUpdateShader->Execute();
		//gGraphicDevice->Distpatch(pUpdateShader);

		pUpdateShader->UpdateData();	
		gGraphicDevice->BindCS(pUpdateShader);
		gGraphicDevice->Distpatch(pUpdateShader);
		pUpdateShader->Clear();

		//gGraphicDevice->BindSB()
		m_bFinalMatUpdate = true;				
	}

	// t30 �������Ϳ� ������� ������(��������) ���ε�			
	// 	
	gGraphicDevice->BindSB(30, m_pBoneFinalMatBuffer, eShaderBindType::VS);
	//m_pBoneFinalMatBuffer->UpdateData(30, PIPELINE_STAGE::PS_VERTEX);
}

void Animator3D::SetAnimClip(std::vector<tMTAnimClip>* _vecAnimClip)
{
	m_pVecClip = _vecAnimClip;
	m_vecClipUpdateTime.resize(m_pVecClip->size());

	// �׽�Ʈ �ڵ�
	//static float fTime = 0.f;
	//fTime += 1.f;
	//m_vecClipUpdateTime[0] = fTime;

}

void Animator3D::ClearData()
{
	ID3D11ShaderResourceView* pSRV = nullptr;
	UINT recentNum = 30;

	gGraphicDevice->UnSafe_Context()->VSSetShaderResources(recentNum, 1, &pSRV);
	gGraphicDevice->UnSafe_Context()->HSSetShaderResources(recentNum, 1, &pSRV);
	gGraphicDevice->UnSafe_Context()->DSSetShaderResources(recentNum, 1, &pSRV);
	gGraphicDevice->UnSafe_Context()->GSSetShaderResources(recentNum, 1, &pSRV);
	gGraphicDevice->UnSafe_Context()->PSSetShaderResources(recentNum, 1, &pSRV);
	gGraphicDevice->UnSafe_Context()->CSSetShaderResources(recentNum, 1, &pSRV);

	UINT iMtrlCount = GetComponent<MeshRenderer>()->GetMaterialCount();
	Material* pMtrl = nullptr;
	for (UINT i = 0; i < iMtrlCount; ++i)
	{
		pMtrl = GetComponent<MeshRenderer>()->GetMaterial(i);
		if (nullptr == pMtrl)
		{
			continue;
		}			
		
		pMtrl->SetAnim3D(false); // Animation Mesh �˸���
		pMtrl->SetBoneCount(0);
	}

}

void Animator3D::check_mesh(Mesh* _pMesh)
{
	(void)_pMesh;
	UINT iBoneCount = _pMesh->GetBoneCount();
	if (m_pBoneFinalMatBuffer == nullptr || m_pBoneFinalMatBuffer->GetElementCount() != iBoneCount)
	{
		delete m_pBoneFinalMatBuffer;
		m_pBoneFinalMatBuffer = new StructuredBuffer(eSBType::BoneFinalBuffer, 
			eSRVTpye::BoneFrameData, 
			sizeof(Matrix),
			iBoneCount,
			nullptr, 
			gGraphicDevice->UnSafe_GetDevice());
	}
	//if (m_pBoneFinalMatBuffer->GetElementCount() != iBoneCount)
	//{
	//	m_pBoneFinalMatBuffer->Create(sizeof(Matrix), iBoneCount, SB_TYPE::READ_WRITE, false, nullptr);
	//}
}

void Animator3D::update()
{
	//RenderComponent::update();
}

void Animator3D::lateUpdate()
{
	m_dCurTime = 0.f;
	// ���� ������� Clip �� �ð��� �����Ѵ�.
	m_vecClipUpdateTime[m_iCurClip] += gDeltaTime;

	if (m_vecClipUpdateTime[m_iCurClip] >= m_pVecClip->at(m_iCurClip).dTimeLength)
	{
		m_vecClipUpdateTime[m_iCurClip] = 0.f;
	}

	m_dCurTime = m_pVecClip->at(m_iCurClip).dStartTime + m_vecClipUpdateTime[m_iCurClip];

	// ���� ������ �ε��� ���ϱ�
	double dFrameIdx = m_dCurTime * (double)m_iFrameCount;
	m_iFrameIdx = (int)(dFrameIdx);

	// ���� ������ �ε���
	if (m_iFrameIdx >= m_pVecClip->at(0).iFrameLength - 1)
		m_iNextFrameIdx = m_iFrameIdx;	// ���̸� ���� �ε����� ����
	else
		m_iNextFrameIdx = m_iFrameIdx + 1;

	// �����Ӱ��� �ð��� ���� ������ �����ش�.
	m_fRatio = (float)(dFrameIdx - (double)m_iFrameIdx);

	// ��ǻƮ ���̴� ���꿩��
	m_bFinalMatUpdate = false;
}

//void Animator3D::render(const Camera* const camera)
//{
//	(void)camera;
//}
