#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "EnumSRV.h"

enum class eSBType
{
	Light2D,
	Particle2D,
	BoneOffset,
	BoneFrameData,
	BoneFinalBuffer,
	End,
};

class StructuredBuffer
{
	friend class GraphicDeviceDX11;
public:
	StructuredBuffer(const eSBType CBType,
		const eSRVTpye SRVType,
		const UINT dataSize,
		const UINT stride,
		const void* const dataOrNull, ID3D11Device* const device);

	virtual ~StructuredBuffer();
	StructuredBuffer(const StructuredBuffer&) = delete;
	StructuredBuffer& operator=(const StructuredBuffer&) = delete;

	UINT GetElementSize() { return mSize; }
	UINT GetElementCount() { return mStride; }
	UINT GetBufferSize() { return mSize * mStride; }

private:	
	Microsoft::WRL::ComPtr<ID3D11Buffer>				mBuffer;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mSRV;
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>   m_UAV;

	D3D11_BUFFER_DESC mDesc;
	eSBType mType;
	eSRVTpye mSRVType;
	UINT mSize;
	UINT mStride;
};
