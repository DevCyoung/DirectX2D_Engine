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
	, mIndexBuffers()	
{	
	(void)indexSize;

	addVertex(vertexs);
	
	addIndexBuffer(indexs, indexCount, indexSize);


}

Mesh::Mesh(const void* const vertexs, 
	const size_t vertexCount, 
	const size_t vertexSize, 
	const std::vector<tIndexInfo>& infos)
	: mVertexBuffer(nullptr)
	, mVertexCount(vertexCount)
	, mVertexSize(vertexSize)
	, mVertexDesc{}
	, mIndexBuffers()
{
	addVertex(vertexs);

	for (const tIndexInfo& info : infos)
	{
		addIndexBuffer(info.pIdxSysMem, info.iIdxCount, sizeof(UINT));
	}
}

Mesh::~Mesh()
{


	mIndexBuffers.clear();
}

HRESULT Mesh::Load(const std::wstring& filePath)
{
	Assert(false, ASSERT_MSG(""));

	(void)filePath;
	return E_NOTIMPL;
}

void Mesh::addIndexBuffer(const void* const indexs, 
	const size_t indexCount, 
	const size_t indexSize)
{
	(void)indexSize;

	D3D11_BUFFER_DESC indexDexc = {};
	indexDexc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	indexDexc.CPUAccessFlags = 0;
	indexDexc.Usage = D3D11_USAGE_DEFAULT;
	indexDexc.ByteWidth = static_cast<UINT>(indexCount * 4);

	D3D11_SUBRESOURCE_DATA tIndexSub = {};
	tIndexSub.pSysMem = indexs;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateBuffer(&indexDexc, &tIndexSub, indexBuffer.GetAddressOf())))
	{
		Assert(false, ASSERT_MSG("failed to create index buffer"));
	}

	tIndexInfo info = {};
	info.iIdxCount = static_cast<UINT>(indexCount);
	info.pIB = indexBuffer;
	info.tIBDesc = indexDexc;
	info.pIdxSysMem = indexs;

	//delete info.pIdxSysMem;

	mIndexBuffers.push_back(info);
}

void Mesh::addVertex(const void* const vertexs)
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
}

