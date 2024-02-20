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
    std::vector<Matrix>				m_vecFinalBoneMat; // 텍스쳐에 전달할 최종 행렬정보
    int							    m_iFrameCount; // 30
    double						    m_dCurTime;
    int							    m_iCurClip; // 클립 인덱스	

    int							    m_iFrameIdx; // 클립의 현재 프레임
    int							    m_iNextFrameIdx; // 클립의 다음 프레임
    float						    m_fRatio;	// 프레임 사이 비율

    StructuredBuffer*               m_pBoneFinalMatBuffer;  // 특정 프레임의 최종 행렬
    bool						    m_bFinalMatUpdate; // 최종행렬 연산 수행여부
};

