#pragma once
#include "Component.h"
#include "FBXLoader.h"

REGISTER_COMPONENT_TYPE(Animator3D);

class StructuredBuffer;
class Mesh;
class Animator3D : public Component
{
public:
	Animator3D();
	virtual ~Animator3D();
	Animator3D(const Animator3D& other);
	Animator3D& operator=(const Animator3D&) = delete;

    void UpdateData();

public:
    void SetBones(std::vector<tMTBone>* _vecBones) 
    { 
        m_pVecBones = _vecBones; m_vecFinalBoneMat.resize(m_pVecBones->size()); 
    }
    StructuredBuffer* GetFinalBoneMat() { return m_pBoneFinalMatBuffer; }
    UINT GetBoneCount() { return (UINT)m_pVecBones->size(); }

    void SetClipTime(int _iClipIdx, float _fTime) { m_vecClipUpdateTime[_iClipIdx] = _fTime; }
    void SetAnimClip(std::vector<tMTAnimClip>* _vecAnimClip);
    void ClearData();
    void check_mesh(Mesh* _pMesh);

//private:
    

    virtual void update() override;
    virtual void lateUpdate() override;
    //virtual void render(const Camera* const camera);



public:
    std::vector<tMTBone>*           m_pVecBones;
    std::vector<tMTAnimClip>*       m_pVecClip;

    std::vector<float>				m_vecClipUpdateTime;
    std::vector<Matrix>				m_vecFinalBoneMat; // �ؽ��Ŀ� ������ ���� �������
    int							    m_iFrameCount; // 30
    double						    m_dCurTime;
    int							    m_iCurClip; // Ŭ�� �ε���	

    int							    m_iFrameIdx; // Ŭ���� ���� ������
    int							    m_iNextFrameIdx; // Ŭ���� ���� ������
    float						    m_fRatio;	// ������ ���� ����

    StructuredBuffer*               m_pBoneFinalMatBuffer;  // Ư�� �������� ���� ���
    bool						    m_bFinalMatUpdate; // ������� ���� ���࿩��
};

