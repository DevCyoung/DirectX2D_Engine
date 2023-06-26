#include "pch.h"
#include "BSCollection.h"

BSCollection::BSCollection(ID3D11Device* const device)
	: mBStates{0, }
{
	Assert(device, WCHAR_IS_NULLPTR);

	D3D11_BLEND_DESC blendDesc = {};

	//default
	mBStates[(UINT)eBSType::Default] = nullptr;

	// Alpha Blend
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&blendDesc
		, mBStates[(UINT)eBSType::AlphaBlend].GetAddressOf());
	Assert(mBStates[static_cast<UINT>(eBSType::AlphaBlend)].Get(), WCHAR_IS_NULLPTR);

	// one one
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&blendDesc
		, mBStates[(UINT)eBSType::OneOne].GetAddressOf());
	Assert(mBStates[static_cast<UINT>(eBSType::AlphaBlend)].Get(), WCHAR_IS_NULLPTR);

}

BSCollection::~BSCollection()
{
}
