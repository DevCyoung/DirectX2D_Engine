#include "pch.h"
#include "FontManager.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

#ifdef _DEBUG
#pragma comment(lib, "FW1FontWrapper/Debug/FW1FontWrapperL.lib")
#else
#pragma comment(lib, "FW1FontWrapper/Release/FW1FontWrapper.lib")
#endif

FontManager::FontManager()
{
	if (FAILED(FW1CreateFactory(FW1_VERSION, &mFW1Factory)))
	{
		Assert(false, ASSERT_MSG_INVALID);
	}

	ID3D11Device* pDevice = Engine::GetInstance()->GetGraphicDevice()->UnSafe_GetDevice();

	if (FAILED(mFW1Factory->CreateFontWrapper(pDevice, L"Russo", &mFontWrapper)))
	{
		Assert(false, ASSERT_MSG_INVALID);
	}
}

FontManager::~FontManager()
{
	mFW1Factory->Release();
	mFW1Factory = nullptr;

	mFontWrapper->Release();
	mFontWrapper = nullptr;
}


void FontManager::DrawFont(const wchar_t* str, float x, float y, float size, UINT rgb)
{	
	//RGB();
	ID3D11DeviceContext* pContext = Engine::GetInstance()->GetGraphicDevice()->UnSafe_Context();

	mFontWrapper->DrawString(
		pContext,
		str, // String
		size,// Font size
		x,// X position
		y,// Y position
		rgb,// Text color, 0xAaBbGgRr
		FW1_RESTORESTATE      // Flags (for example FW1_RESTORESTATE to keep context states unchanged)
	);
}

