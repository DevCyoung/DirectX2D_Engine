#include "pch.h"
#include "EnumResourceTypeTexture.h"

static constexpr const wchar_t* eResTexturePath[static_cast<UINT>(eResTexture::End)]
{
	L"\\Texture\\Dragon\\Dragon_Bump_Col2.jpg",
	L"\\Texture\\Dragon\\Dragon_ground_color.jpg",
	L"\\Texture\\Dragon\\Dragon_Nor.jpg",
	L"\\Texture\\Dragon\\Dragon_Nor_mirror2.jpg",
	L"\\Texture\\Dragon\\Fire_A_2.png",
	L"\\Texture\\Dragon\\Floor_C.jpg",
	L"\\Texture\\Dragon\\Floor_N.jpg",
	L"\\Texture\\Dragon\\Floor_S.jpg",
	L"\\Texture\\Noise\\01.png",
	L"\\Texture\\Noise\\02.png",
	L"\\Texture\\Noise\\03.png",
	L"\\Texture\\Noise\\04.png",
	L"\\Texture\\Noise\\noise_01.png",
	L"\\Texture\\Noise\\noise_02.png",
	L"\\Texture\\Noise\\noise_03.jpg",
	L"\\Texture\\TILE_01.tga",
	L"\\Texture\\TILE_01_N.tga",
	L"\\Texture\\T_Mon_BlackDragon31a_D.png",
	L"\\Texture\\T_Mon_BlackDragon31a_M.png",
	L"\\Texture\\T_Mon_BlackDragon31a_N.png",
	L"\\Texture\\T_Mon_BlackDragon31b_D.png",
	L"\\Texture\\T_Mon_BlackDragon31b_M.png",
	L"\\Texture\\T_Mon_BlackDragon31b_N.png",
};

const wchar_t* EnumResourcePath(eResTexture type)
{
	return eResTexturePath[static_cast<UINT>(type)];
}

