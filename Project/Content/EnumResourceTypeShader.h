﻿#pragma once

enum class eResShader
{
	Header_ConstantBuffer,
	Header_Sampler,
	Header_Struct,
	Header_TestShaderHeader,
	Header_Texture,
	Light2D,
	PSAnimation2D,
	PSFillDebug2D,
	PSGrayPostProcess,
	PSGrid2D,
	PSLightAnimation2D,
	PSLightSprite2D,
	PSLineDebug2D,
	PSSprite2D,
	PSUI2D,
	PSWave,
	stdCS,
	VSAnimation2D,
	VSFillDebug2D,
	VSGrayPostProcess,
	VSGrid2D,
	VSLightAnimation2D,
	VSLightSprite2D,
	VSLineDebug2D,
	VSSprite2D,
	VSUI2D,
	VSWave,
	End
};

const wchar_t* EnumResourcePath(eResShader type);

