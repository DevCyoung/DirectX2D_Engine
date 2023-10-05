﻿#include "pch.h"
#include "EnumResourceTypeShader.h"

static constexpr const wchar_t* eResShaderPath[static_cast<UINT>(eResShader::End)]
{
	L"\\Shader\\Header\\ConstantBuffer.fxh",
	L"\\Shader\\Header\\Sampler.fxh",
	L"\\Shader\\Header\\Struct.fxh",
	L"\\Shader\\Header\\TestShaderHeader.fxh",
	L"\\Shader\\Header\\Texture.fxh",
	L"\\Shader\\Light2D.hlsl",
	L"\\Shader\\PSAnimation2D.hlsl",
	L"\\Shader\\PSFillDebug2D.hlsl",
	L"\\Shader\\PSGrayPostProcess.hlsl",
	L"\\Shader\\PSGrid2D.hlsl",
	L"\\Shader\\PSLightAnimation2D.hlsl",
	L"\\Shader\\PSLightSprite2D.hlsl",
	L"\\Shader\\PSLineDebug2D.hlsl",
	L"\\Shader\\PSSprite2D.hlsl",
	L"\\Shader\\PSUI2D.hlsl",
	L"\\Shader\\PSWave.hlsl",
	L"\\Shader\\stdCS.hlsl",
	L"\\Shader\\VSAnimation2D.hlsl",
	L"\\Shader\\VSFillDebug2D.hlsl",
	L"\\Shader\\VSGrayPostProcess.hlsl",
	L"\\Shader\\VSGrid2D.hlsl",
	L"\\Shader\\VSLightAnimation2D.hlsl",
	L"\\Shader\\VSLightSprite2D.hlsl",
	L"\\Shader\\VSLineDebug2D.hlsl",
	L"\\Shader\\VSSprite2D.hlsl",
	L"\\Shader\\VSUI2D.hlsl",
	L"\\Shader\\VSWave.hlsl",
};

const wchar_t* EnumResourcePath(eResShader type)
{
	return eResShaderPath[static_cast<UINT>(type)];
}

