#include "pch.h"
#include "GraphicDeviceDX11.h"
#include "Textrue.h"
#include "Shader.h"
#include "Mesh.h"
#include "CBCollection.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#pragma region Comment Date : 2023-05-26 
/*
* Trouble : Fxing
* Date : 2023-05-26
* Author : yoseo
* ���� SwapChain������ Warning �߻�
* DXGI WARNING: IDXGIFactory::CreateSwapChain: Blt-model swap effects (DXGI_SWAP_EFFECT_DISCARD and DXGI_SWAP_EFFECT_SEQUENTIAL) are legacy swap effects that are predominantly superceded by their flip-model counterparts (DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL and DXGI_SWAP_EFFECT_FLIP_DISCARD). Please consider updating your application to leverage flip-model swap effects to benefit from modern presentation enhancements. More information is available at http://aka.ms/dxgiflipmodel. [ MISCELLANEOUS WARNING #294: ]*
* DXGI_SWAP_CHAIN_DESC ����ü�� swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
* �κ��� DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD ���� ��ü�ϸ� Warning�� ��������� �������� 60���� ����
* �ǰų� Ȥ�� �������� ������ �߻��Ѵ�.
* �ذ��Ϸ��� �õ����Դϴ�.
* Date : 2023-05-29
* ����������...
*/
#pragma endregion

#pragma region Constructor
GraphicDeviceDX11::GraphicDeviceDX11(const HWND hWnd, const UINT screenWidth, const UINT screenHeight)
	: mConstantBuffers(nullptr)
{
	Assert(hWnd, WCHAR_IS_NULLPTR);

#ifdef _DEBUG
	constexpr UINT DEVICE_FLAG = D3D11_CREATE_DEVICE_DEBUG;
#else
	//���� ��ɷ� �ؾ��ϴ��� �����...
	//const UINT deviceFlag = D3D11_CREATE_DEVICE_SINGLETHREADED;
	constexpr UINT DEVICE_FLAG = D3D11_CREATE_DEVICE_DEBUG;
#endif

#pragma region Create Device And Context
	D3D_FEATURE_LEVEL featureLevel = static_cast<D3D_FEATURE_LEVEL>(0);

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, DEVICE_FLAG, nullptr, 0, D3D11_SDK_VERSION,
		mDevice.GetAddressOf(), &featureLevel,
		mContext.GetAddressOf())))
	{
		Assert(false, L"failed to create device");
		return;
	}

	Assert(mDevice, WCHAR_IS_NULLPTR);
	Assert(mContext, WCHAR_IS_NULLPTR);

#pragma endregion

#pragma region Change Window ScreenSize		
	RECT windowSize =
	{
		0, 0,
		static_cast<LONG>(screenWidth), static_cast<LONG>(screenHeight)
	};

	const BOOL B_MENU = GetMenu(hWnd) != nullptr;

	AdjustWindowRect(&windowSize, WS_OVERLAPPEDWINDOW, B_MENU);
	SetWindowPos(hWnd,
		nullptr, 0, 0,
		windowSize.right - windowSize.left,
		windowSize.bottom - windowSize.top, 0);

	ShowWindow(hWnd, true);
	UpdateWindow(hWnd);
#pragma endregion


#pragma region Create SwaphChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferCount = 2;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = TRUE;

	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 240;   //�ִ�������
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;   //�ּ�������
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM; //�ȼ� ����                                    

	Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory> pDXGIFactory = nullptr;

	if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(pDXGIDevice.GetAddressOf()))))
	{
		Assert(false, L"failed to create IDXGIDevice");
		return;
	}

	if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(pDXGIAdapter.GetAddressOf()))))
	{
		Assert(false, L"failed to create IDXGIAdapter");
		return;
	}

	if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pDXGIFactory.GetAddressOf()))))
	{
		Assert(false, L"failed to create IDXGIFactory");
		return;
	}

	if (FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(), &swapChainDesc, mSwapChain.GetAddressOf())))
	{
		Assert(false, L"failed to create IDXGISwapChain");
		return;
	}

	//RenderTarget
	if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(mRenderTargetTexture.GetAddressOf()))))
	{
		Assert(false, L"failed to get buffer");
		return;
	}

	if (FAILED(mDevice->CreateRenderTargetView(mRenderTargetTexture.Get(), nullptr, mRenderTargetView.GetAddressOf())))
	{
		Assert(false, L"failed to create render target view");
		return;
	}
#pragma endregion

#pragma region Create DepthStencil
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};

	depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.Width = screenWidth;
	depthStencilDesc.Height = screenHeight;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.MiscFlags = 0;

	if (FAILED(mDevice->CreateTexture2D(&depthStencilDesc, nullptr, mDepthStencilTexture.GetAddressOf())))
	{
		Assert(false, L"failed to create depth stencil texture");
		return;
	}

	if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilTexture.Get(), nullptr, mDepthStencilView.GetAddressOf())))
	{
		Assert(false, L"failed to create depth stencil view");
		return;
	}
#pragma endregion

#pragma region Create ConstantBuffers		
	mConstantBuffers = new CBCollection(mDevice.Get());
#pragma endregion

#pragma region Create Sampler
	D3D11_SAMPLER_DESC tSamDesc = {};

	tSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	mDevice->CreateSamplerState(&tSamDesc, m_Sampler[0].GetAddressOf());


	tSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	mDevice->CreateSamplerState(&tSamDesc, m_Sampler[1].GetAddressOf());

	mContext->VSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	mContext->HSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	mContext->DSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	mContext->GSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
	mContext->PSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());


	mContext->VSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	mContext->HSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	mContext->DSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	mContext->GSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
	mContext->PSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
#pragma endregion

}
#pragma endregion

GraphicDeviceDX11::~GraphicDeviceDX11()
{
	SAFE_DELETE_POINTER(mConstantBuffers);
}

void GraphicDeviceDX11::BindIA(const Shader* const shader)
{
	Assert(shader, WCHAR_IS_NULLPTR);
	Assert(shader->mInputLayout.Get(), WCHAR_IS_NULLPTR);

	mContext->IASetInputLayout(shader->mInputLayout.Get());
	mContext->IASetPrimitiveTopology(shader->mTopology);
}

void GraphicDeviceDX11::BindMesh(const Mesh* const mesh)
{
	Assert(mesh, WCHAR_IS_NULLPTR);


	const UINT vertexSize = mesh->GetVertexSize();
	const UINT offset = 0;
	mContext->IASetVertexBuffers(0, 1, mesh->mBuffer.GetAddressOf(), &vertexSize, &offset);
}

void GraphicDeviceDX11::BindTexture(const eShaderBindType stage, const UINT startSlot, const Texture* const texture)
{
	switch (stage)
	{
	case eShaderBindType::VS:
		mContext->VSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
		break;
	case eShaderBindType::HS:
		mContext->HSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
		break;
	case eShaderBindType::DS:
		mContext->DSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
		break;
	case eShaderBindType::GS:
		mContext->GSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
		break;
	case eShaderBindType::PS:
		mContext->PSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
		break;
	case eShaderBindType::CS:
		mContext->CSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
		break;
	default:
		Assert(false, WCHAR_SWITCH_DEFAULT);
		break;
	}
}

void GraphicDeviceDX11::BindCB(const eCBType type, const eShaderBindType stage)
{
	const ConstantBuffer& CB = mConstantBuffers->GetConstantBuffer(type);
	const UINT startSlot = static_cast<UINT>(CB.mType);

	switch (stage)
	{
	case eShaderBindType::VS:
		mContext->VSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
		break;
	case eShaderBindType::HS:
		mContext->HSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
		break;
	case eShaderBindType::DS:
		mContext->DSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
		break;
	case eShaderBindType::GS:
		mContext->GSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
		break;
	case eShaderBindType::PS:
		mContext->PSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
		break;
	case eShaderBindType::CS:
		mContext->CSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
		break;
	default:
		Assert(false, WCHAR_SWITCH_DEFAULT);
		break;
	}
}

void GraphicDeviceDX11::PassCB(const eCBType type, const UINT byteSize, const void* const data)
{
	Assert(data, WCHAR_IS_NULLPTR);
	UNREFERENCED_PARAMETER(byteSize);

	ConstantBuffer& CB = mConstantBuffers->GetConstantBuffer(type);
	Assert(CB.mSize == byteSize, L"data size not ali 16");

	D3D11_MAPPED_SUBRESOURCE subResource = {};

	mContext->Map(CB.mBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy_s(subResource.pData, CB.mDesc.ByteWidth, data, CB.mDesc.ByteWidth);
	}
	mContext->Unmap(CB.mBuffer.Get(), 0);
}

void GraphicDeviceDX11::BindVS(const Shader* const shader)
{
	Assert(shader, WCHAR_IS_NULLPTR);
	Assert(shader->mVS.Get(), WCHAR_IS_NULLPTR);

	mContext->VSSetShader(shader->mVS.Get(), nullptr, 0);
}

void GraphicDeviceDX11::BindPS(const Shader* const shader)
{
	Assert(shader, WCHAR_IS_NULLPTR);
	Assert(shader->mPS.Get(), WCHAR_IS_NULLPTR);

	mContext->PSSetShader(shader->mPS.Get(), nullptr, 0);
}

void GraphicDeviceDX11::Draw(const UINT StartVertexLocation, const Mesh* const mesh)
{
	Assert(mesh, WCHAR_IS_NULLPTR);

	const UINT vertexSize = mesh->GetVertexCount();
	mContext->Draw(vertexSize, StartVertexLocation);
}

void GraphicDeviceDX11::clearRenderTarget(const UINT screenWidth, const UINT screenHeight)
{
	const FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

	const D3D11_VIEWPORT mViewPort =
	{
		0.0f, 0.0f,
		static_cast<FLOAT>(screenWidth), static_cast<FLOAT>(screenHeight),
		0.0f, 1.0f
	};

	mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	mContext->RSSetViewports(1, &mViewPort);
	mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
	mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void GraphicDeviceDX11::present()
{
	mSwapChain->Present(0, 0);
}
