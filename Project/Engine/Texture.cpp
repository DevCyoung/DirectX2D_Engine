#include "pch.h"
#include "Texture.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "String.h"
#include "EnumResource.h"

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/Debug/DirectXTex_d.lib")
#else
#pragma comment(lib, "DirectXTex/Release/DirectXTex.lib")
#endif

Texture::Texture(UINT _Width, UINT _Height, 
	DXGI_FORMAT _pixelformat, 
	UINT _BindFlag, D3D11_USAGE _Usage)
	: Texture()	
{
	mWidth = _Width;
	mHeight = _Height;

	D3D11_TEXTURE2D_DESC                m_Desc = {};

	// ID3D11Texture2D 생성
	m_Desc.Format = _pixelformat;

	// 반드시 렌더타겟과 같은 해상도로 설정해야 함
	m_Desc.Width = _Width;
	m_Desc.Height = _Height;
	m_Desc.ArraySize = 1;

	m_Desc.BindFlags = _BindFlag;
	m_Desc.Usage = _Usage;

	//if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == _Usage)
	//{
	//	m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//}		
	//else if (D3D11_USAGE::D3D11_USAGE_STAGING == _Usage)
	//{
	//	m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	//}
		
	m_Desc.MipLevels = 1;    // 원본만 생성
	m_Desc.SampleDesc.Count = 1;
	m_Desc.SampleDesc.Quality = 0;

	ID3D11Device* const device = gGraphicDevice->UnSafe_GetDevice();

	if (FAILED(device->CreateTexture2D(&m_Desc, nullptr, mTexture.GetAddressOf())))
	{
		Assert(false, ASSERT_MSG_INVALID);
	}

	// 바인드 플래그에 맞는 View 를 생성해준다.
	if (m_Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
	{
		if (FAILED(device->CreateDepthStencilView(mTexture.Get(), nullptr, mDSV.GetAddressOf())))
		{
			Assert(false, ASSERT_MSG_INVALID);
		}
	}
	else
	{
		if (m_Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			if (FAILED(device->CreateRenderTargetView(mTexture.Get(), nullptr, mRTV.GetAddressOf())))
			{
				Assert(false, ASSERT_MSG_INVALID);
			}
		}

		if (m_Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			if (FAILED(device->CreateShaderResourceView(mTexture.Get(), nullptr, mSRV.GetAddressOf())))
			{
				Assert(false, ASSERT_MSG_INVALID);
			}
		}

		if (m_Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			if (FAILED(device->CreateUnorderedAccessView(mTexture.Get(), nullptr, mUAV.GetAddressOf())))
			{
				Assert(false, ASSERT_MSG_INVALID);
			}
		}
	}
}

Texture::Texture()
	: Resource(eResourceType::Texture)
	, mImage()
	, mWidth(0)
	, mHeight(0)
	, mTexture(nullptr)
	, mSRV(nullptr)
	, mRTV(nullptr)
	, mDSV(nullptr)
	, mUAV(nullptr)
{
}

Texture::~Texture()
{
}

HRESULT Texture::Load(const std::wstring& filePath)
{
	const std::wstring& FILE_EXTENSION = helper::String::SplitFilePathExtension(filePath);

	if (FILE_EXTENSION == L".dds" || FILE_EXTENSION == L".DDS")
	{
		if (FAILED(LoadFromDDSFile(filePath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
		{
			Assert(false, ASSERT_MSG("fail load file .dds"));
		}
	}
	else if (FILE_EXTENSION == L".tga" || FILE_EXTENSION == L".TGA")
	{
		if (FAILED(LoadFromTGAFile(filePath.c_str(), nullptr, mImage)))
		{
			Assert(false, ASSERT_MSG("fail load file .tga"));
		}
	}
	else if (FILE_EXTENSION == L".png" || FILE_EXTENSION == L".PNG" ||
		FILE_EXTENSION == L".jpg" || FILE_EXTENSION == L".JPG" ||
		FILE_EXTENSION == L".jpeg" || FILE_EXTENSION == L".JPEG" ||
		FILE_EXTENSION == L".bmp" || FILE_EXTENSION == L".BMP") // WIC (png, jpg, jpeg, bmp )
	{
		if (FAILED(LoadFromWICFile(filePath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
		{
			Assert(false, ASSERT_MSG("fail load file other"));
		}
	}
	else
	{				
		Assert(false, ASSERT_MSG("is not supported"));
	}

	if (FAILED(CreateShaderResourceView(gGraphicDevice->UnSafe_GetDevice()
		, mImage.GetImages()
		, mImage.GetImageCount()
		, mImage.GetMetadata(), mSRV.GetAddressOf())))
	{
		Assert(false, ASSERT_MSG("fail create resource view"));
	}

	Assert(mSRV, ASSERT_MSG_NULL);

	mSRV->GetResource(reinterpret_cast<ID3D11Resource**>(mTexture.GetAddressOf()));

	mWidth  = static_cast<UINT>(mImage.GetMetadata().width);
	mHeight = static_cast<UINT>(mImage.GetMetadata().height);

	return S_OK;
}

