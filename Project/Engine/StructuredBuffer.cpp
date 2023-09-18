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

	// 16����Ʈ ���� �޸� ����
	Assert((mSize % 16) == 0, WCHAR_IS_INVALID_TYPE);

	mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
	mDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	mDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	mDesc.ByteWidth = mSize * stride;
	mDesc.StructureByteStride = mSize; // ������ ����	

	if (nullptr == dataOrNull)
	{
		HRESULT hr = device->CreateBuffer(&mDesc, nullptr, mBuffer.GetAddressOf());
		Assert(SUCCEEDED(hr), WCHAR_IS_INVALID_TYPE);
		(void)hr;
	}
	else
	{
		D3D11_SUBRESOURCE_DATA tSubData = {};
		tSubData.pSysMem = dataOrNull;

		HRESULT hr = device->CreateBuffer(&mDesc, &tSubData, mBuffer.GetAddressOf());
		Assert(SUCCEEDED(hr), WCHAR_IS_INVALID_TYPE);
		(void)hr;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.BufferEx.NumElements = mStride;
	srvDesc.ViewDimension = D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX;

	HRESULT hr  = device->CreateShaderResourceView(mBuffer.Get(), &srvDesc, mSRV.GetAddressOf());
	Assert(SUCCEEDED(hr), WCHAR_IS_INVALID_TYPE);
	(void)hr;
}

StructuredBuffer::~StructuredBuffer()
{
}