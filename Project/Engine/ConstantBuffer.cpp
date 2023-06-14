#include "pch.h"
#include "ConstantBuffer.h"
#include "Engine.h"

namespace engine
{
	ConstantBuffer::ConstantBuffer(const eCBType type, const UINT size)
		: mType(type)
		, mDesc{}
		, mBuffer(nullptr)
	{
		assert((size % 16) == 0);

		mDesc.ByteWidth = size;
		mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		mDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

		gDevie->CreateBuffer(&mDesc, nullptr, mBuffer.GetAddressOf());
		assert(mBuffer.Get());
	}

	ConstantBuffer::~ConstantBuffer()
	{
	}
}