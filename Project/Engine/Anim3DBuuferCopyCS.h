#pragma once
#include "ComputeShader.h"
class StructuredBuffer;

class Anim3DBuuferCopyCS : public ComputeShader
{
private:
	StructuredBuffer* m_pFrameDataBuffer;			// t13
	StructuredBuffer* m_pOffsetMatBuffer;			// t14 
	StructuredBuffer* m_pOutputBuffer;				// u0

public:
	// g_int_0 : BonCount, g_int_1 : Frame Index
	void SetBoneCount(int _iBoneCount) { m_Const.arrInt[0] = _iBoneCount; }
	void SetFrameIndex(int _iFrameIdx) { m_Const.arrInt[1] = _iFrameIdx; }
	void SetNextFrameIdx(int _iFrameIdx) { m_Const.arrInt[2] = _iFrameIdx; }
	void SetFrameRatio(float _fFrameRatio) { m_Const.arrFloat[0] = _fFrameRatio; }

	void SetFrameDataBuffer(StructuredBuffer* _buffer) { m_pFrameDataBuffer = _buffer; }
	void SetOffsetMatBuffer(StructuredBuffer* _buffer) { m_pOffsetMatBuffer = _buffer; }
	void SetOutputBuffer(StructuredBuffer* _buffer) { m_pOutputBuffer = _buffer; }

public:
	virtual void UpdateData();
	virtual void Clear();

	Anim3DBuuferCopyCS() = default;
	Anim3DBuuferCopyCS(const std::wstring& CSRelativePath, const std::wstring& CSFunName);
	virtual ~Anim3DBuuferCopyCS();
	Anim3DBuuferCopyCS(const Anim3DBuuferCopyCS&) = delete;
	Anim3DBuuferCopyCS& operator=(const Anim3DBuuferCopyCS&) = delete;
};

