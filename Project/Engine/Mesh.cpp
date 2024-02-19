#include "pch.h"
#include "Mesh.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "EnumResource.h"
#include "StructuredBuffer.h"

Mesh::Mesh(
	const void* const vertexs,
	const size_t vertexCount,
	const size_t vertexSize,
	const UINT* const indexs,
	const size_t indexCount,
	const size_t indexSize)
	: Resource(eResourceType::Mesh)
	, mVertexBuffer(nullptr)
	, mVertexCount(vertexCount)
	, mVertexSize(vertexSize)
	, mVertexDesc{}
	, mIndexBuffers()	
	, m_pBoneFrameData(nullptr)
	, m_pBoneOffset(nullptr)
{	
	(void)indexSize;

	addVertex(vertexs);
	
	addIndexBuffer(indexs, indexCount, indexSize);


}

Mesh::Mesh(const void* const vertexs,
	const size_t vertexCount,
	const size_t vertexSize,
	const UINT* const indexes,
	const size_t* const indexCounts,
	const size_t indexesCount,
	const size_t indexSize)
	: Resource(eResourceType::Mesh)
	, mVertexBuffer(nullptr)
	, mVertexCount(vertexCount)
	, mVertexSize(vertexSize)
	, mVertexDesc{}
	, mIndexBuffers()
	, m_pBoneFrameData(nullptr)
	, m_pBoneOffset(nullptr)
{
	addVertex(vertexs);

	const UINT* temp = indexes;

	for (size_t i = 0; i < indexesCount; ++i)
	{
		if (indexCounts[i] <= 0)
		{
			continue;
		}

		addIndexBuffer(temp, indexCounts[i], indexSize);
		temp += indexCounts[i];
	}
}

Mesh::~Mesh()
{
	mIndexBuffers.clear();

	delete m_pBoneFrameData;
	m_pBoneFrameData = nullptr;

	delete m_pBoneOffset;
	m_pBoneOffset = nullptr;
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
	D3D11_BUFFER_DESC indexDexc = {};
	indexDexc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	indexDexc.CPUAccessFlags = 0;
	indexDexc.Usage = D3D11_USAGE_DEFAULT;
	indexDexc.ByteWidth = static_cast<UINT>(indexCount * indexSize);

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
	//info.pIdxSysMem = indexs;

	//free(info.pIdxSysMem);
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

