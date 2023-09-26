#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

class CBCollection;
class RSCollection;
class BSCollection;
class DSCollection;
class SMCollection;
class SBCollection;

class Shader;
class ComputeShader;
class Mesh;
class Texture;

struct ID3D11Device;

enum class eCBType;
enum class eSBType;
enum class eRSType;
enum class eBSType;
enum class eDSType;
enum class eShaderBindType;

class GraphicDeviceDX11
{
	friend class Engine;
private:
	GraphicDeviceDX11(const HWND hWnd, const UINT renderTargetWidth, const UINT renderTargetHeight);
	virtual ~GraphicDeviceDX11();
	GraphicDeviceDX11(const GraphicDeviceDX11&) = delete;
	GraphicDeviceDX11& operator=(const GraphicDeviceDX11&) = delete;

public:
	ID3D11Device* UnSafe_GetDevice() const { Assert(mDevice, WCHAR_IS_NULLPTR); return mDevice.Get(); }

	void BindIA(const Shader* const shader) const;
	void BindMesh(const Mesh* const mesh) const;
	void BindSRV(const eShaderBindType stageType, const UINT startSlot, const Texture* const texture) const;
	void BindUAV(const UINT startSlot, const Texture* const texture) const;
	void UnBindUAV(const UINT startSlot) const;

	void BindCB(const eCBType CBType, const eShaderBindType stageType) const;
	void PassCB(const eCBType CBType, const UINT dataSize, const void* const data) const;
	void BindSB(const eSBType SBType, const eShaderBindType stageType) const;
	void PassSB(const eSBType SBType, const UINT dataSize, const UINT stride, const void* const data) const;
	void BindVS(const Shader* const shader) const;
	void BindPS(const Shader* const shader) const;
	void BindCS(const ComputeShader* const shader) const;
	void BindBS(const eBSType BSType) const;
	void BindDS(const eDSType DSType) const;
	void BindRS(const eRSType RSType) const;
	void BindRenderTarget(const UINT renderTargetWidth,
		const UINT renderTargetHeight,
		ID3D11RenderTargetView* const* const ppRnderTargetView,
		ID3D11DepthStencilView* const depthStencilView) const;

	void Draw(const Mesh* const mesh) const;
	//void DrawIndexedInstanced(const Mesh* const mesh) const;
	void Distpatch(const ComputeShader* const computeShader) const;

	void ClearRenderTarget(ID3D11RenderTargetView* const* const ppRnderTargetView,
		ID3D11DepthStencilView* const depthStencilView,
		const FLOAT backgroundColor[4]) const;

	void CopyResource(ID3D11Resource* const dst, ID3D11Resource* const src);

	const SMCollection* GetIEDCollection() const
	{
		Assert(mSMCollection, WCHAR_IS_NULLPTR);
		return mSMCollection;
	}

	ID3D11Texture2D* GetRenderTargetTexture() const
	{
		Assert(mRenderTargetTexture, WCHAR_IS_NULLPTR);

		return mRenderTargetTexture.Get();
	}

private:
	void present();

	ID3D11RenderTargetView** GetRenderTargetViewAddressOf()
	{
		Assert(mRenderTargetView, WCHAR_IS_NULLPTR);

		return mRenderTargetView.GetAddressOf();
	}

	ID3D11DepthStencilView* GetDepthStencilView()
	{
		Assert(mDepthStencilView, WCHAR_IS_NULLPTR);

		return mDepthStencilView.Get();
	}



private:
	Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTargetTexture;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilTexture;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler[2];

	CBCollection* mCBCollection;
	RSCollection* mRSCollection;
	BSCollection* mBSCollection;
	DSCollection* mDSCollection;
	SMCollection* mSMCollection;
	SBCollection* mSBCollection;
};

