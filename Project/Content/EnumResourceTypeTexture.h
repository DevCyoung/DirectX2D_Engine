#pragma once

enum class eResTexture
{
	Dragon_Dragon_Bump_Col2,
	Dragon_Dragon_ground_color,
	Dragon_Dragon_Nor,
	Dragon_Dragon_Nor_mirror2,
	Dragon_Fire_A_2,
	Dragon_Floor_C,
	Dragon_Floor_N,
	Dragon_Floor_S,
	Noise_01,
	Noise_02,
	Noise_03,
	Noise_04,
	Noise_noise_01,
	Noise_noise_02,
	Noise_noise_03,
	TILE_01,
	TILE_01_N,
	T_Mon_BlackDragon31a_D,
	T_Mon_BlackDragon31a_M,
	T_Mon_BlackDragon31a_N,
	T_Mon_BlackDragon31b_D,
	T_Mon_BlackDragon31b_M,
	T_Mon_BlackDragon31b_N,
	End
};

const wchar_t* EnumResourcePath(eResTexture type);

