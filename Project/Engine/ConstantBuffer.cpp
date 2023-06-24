#include "pch.h"
#include "ConstantBuffer.h"

namespace engine
{
	ConstantBuffer::ConstantBuffer(const eCBType type, const UINT size, ID3D11Device* const device)
		: mType(type)
		, mDesc{}
		, mSize(size)
		, mBuffer(nullptr)
	{
		Assert(device, WCHAR_IS_NULLPTR);
		Assert((mSize % 16) == 0, "data not al 16 byte!");		

		mDesc.ByteWidth = size;
		mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		mDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

		device->CreateBuffer(&mDesc, nullptr, mBuffer.GetAddressOf());
		Assert(mBuffer.Get(), WCHAR_IS_NULLPTR);		
	}

	ConstantBuffer::~ConstantBuffer()
	{
	}
}
