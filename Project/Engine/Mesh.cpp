#include "pch.h"
#include "Mesh.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

Mesh::Mesh(
	const void* const vertexs,
	const size_t vertexCount,
	const size_t vertexSize,
	const void* const indexs,
	const size_t indexCount,
	const size_t indexSize)
	: mVertexBuffer(nullptr)
	, mVertexCount(vertexCount)
	, mVertexSize(vertexSize)
	, mVertexDesc{}
	, mIndexBuffer(nullptr)
	, mIndexCount(indexCount)
	, mIndexSize(indexSize)
	, mIdexDesc{}
{	
	mVertexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	mVertexDesc.CPUAccessFlags = 0;
	mVertexDesc.Usage = D3D11_USAGE_DEFAULT;
	mVertexDesc.ByteWidth = static_cast<UINT>(mVertexCount * mVertexSize);

	D3D11_SUBRESOURCE_DATA outVertexSub = {};
	outVertexSub.pSysMem = vertexs;

	if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateBuffer(&mVertexDesc, &outVertexSub, mVertexBuffer.GetAddressOf())))
	{
		Assert(false, ASSERT_MSG("failed to create vertex buffer"));
	}
	
	mIdexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	mIdexDesc.CPUAccessFlags = 0;
	mIdexDesc.Usage = D3D11_USAGE_DEFAULT;
	mIdexDesc.ByteWidth = static_cast<UINT>(mIndexCount * mIndexSize);

	D3D11_SUBRESOURCE_DATA tIndexSub = {};
	tIndexSub.pSysMem = indexs;

	if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateBuffer(&mIdexDesc, &tIndexSub, mIndexBuffer.GetAddressOf())))
	{
		Assert(false, ASSERT_MSG("failed to create index buffer"));
	}
}

Mesh::~Mesh()
{
}

HRESULT Mesh::Load(const std::wstring& filePath)
{
	Assert(false, ASSERT_MSG(""));

	(void)filePath;
	return E_NOTIMPL;
}
