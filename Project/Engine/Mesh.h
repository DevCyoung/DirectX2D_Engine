#pragma once
#include <wrl.h>
#include <d3d11.h>
#include "Resource.h"
using namespace Microsoft::WRL;

struct tIndexInfo
{
	ComPtr<ID3D11Buffer>    pIB;
	D3D11_BUFFER_DESC       tIBDesc;
	UINT				    iIdxCount;
	const void* pIdxSysMem;
};


class Mesh : public Resource
{
	friend class GraphicDeviceDX11;
	friend class ResourceManager;

private:
	Mesh() = default;
public:
	Mesh(
		const void* const vertexs,
		const size_t vertexCount,
		const size_t vertexSize,
		const void* const indexs,
		const size_t indexCount,
		const size_t indexSize);

	Mesh(
		const void* const vertexs,
		const size_t vertexCount,
		const size_t vertexSize,
		const std::vector<tIndexInfo>& infos);

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

public:
	virtual ~Mesh();	
	UINT GetVertexCount() const { return static_cast<UINT>(mVertexCount); }
	//UINT GetIndexCount()  const { return static_cast<UINT>(mIndexCount); }
	virtual HRESULT Load(const std::wstring& filePath) override;
	UINT GetIndexCount() 
	{
		return static_cast<UINT>(mIndexBuffers.size());
	}

private:
	void addIndexBuffer(const void* const indexs,const 
		size_t indexCount, 
		const size_t indexSize);
	void addVertex(const void* const vertexs);	 

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
	size_t mVertexCount;
	size_t mVertexSize;
	D3D11_BUFFER_DESC mVertexDesc;
	std::vector<tIndexInfo> mIndexBuffers;	
};
