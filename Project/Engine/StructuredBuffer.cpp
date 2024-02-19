#include "pch.h"
#include "StructuredBuffer.h"

StructuredBuffer::StructuredBuffer(const eSBType SBType,
	const eSRVTpye SRVType,
	const UINT dataSize,
	const UINT stride,
	const void* const dataOrNull, ID3D11Device* const device)
	: mBuffer(nullptr)
	, mSRV(nullptr)
	, mDesc{}
	, mType(SBType)
	, mSRVType(SRVType)
	, mSize(dataSize)
	, mStride(stride)
{
	mBuffer = nullptr;
	mSRV = nullptr;
	mDesc = {};

	mSize = dataSize;
	mStride = stride;

	// 16바이트 단위 메모리 정렬
	Assert((mSize % 16) == 0, ASSERT_MSG_INVALID);

	//FIXME
	mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE  | D3D11_BIND_UNORDERED_ACCESS;
	//FIXME

	mDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	//mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	mDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	mDesc.ByteWidth = mSize * stride;
	mDesc.StructureByteStride = mSize; // 데이터 간격	

	if (nullptr == dataOrNull)
	{
		HRESULT hr = device->CreateBuffer(&mDesc, nullptr, mBuffer.GetAddressOf());
		Assert(SUCCEEDED(hr), ASSERT_MSG_INVALID);
		(void)hr;
	}
	else
	{
		D3D11_SUBRESOURCE_DATA tSubData = {};
		tSubData.pSysMem = dataOrNull;

		HRESULT hr = device->CreateBuffer(&mDesc, &tSubData, mBuffer.GetAddressOf());
		Assert(SUCCEEDED(hr), ASSERT_MSG_INVALID);
		(void)hr;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.BufferEx.NumElements = mStride;
	srvDesc.ViewDimension = D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX;

	HRESULT hr  = device->CreateShaderResourceView(mBuffer.Get(), &srvDesc, mSRV.GetAddressOf());
	Assert(SUCCEEDED(hr), ASSERT_MSG_INVALID);
	(void)hr;

	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC m_UABDesc = {};
		m_UABDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		m_UABDesc.Buffer.NumElements = mStride;

		if (FAILED(device->CreateUnorderedAccessView(mBuffer.Get(), &m_UABDesc, m_UAV.GetAddressOf())))
		{
			assert(nullptr);
		}
	}
}

StructuredBuffer::~StructuredBuffer()
{
}