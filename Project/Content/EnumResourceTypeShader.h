#pragma once

enum class eResShader
{
	Header_ConstantBuffer,
	Header_Sampler,
	Header_Struct,
	Header_TestShaderHeader,
	Header_Texture,
	animation3d,
	ColorFun,
	copybone,
	Light2D,
	PSAfterImage,
	PSAlphaTo,
	PSAnimation2D,
	PSFillDebug2D,
	PSGrayPostProcess,
	PSGrid2D,
	PSLightAnimation2D,
	PSLightSprite2D,
	PSLineDebug2D,
	PSNextScene,
	PSSprite2D,
	PSUI2D,
	PSWave,
	std3d,
	stdCS,
	VSAfterImage,
	VSAlphaTo,
	VSAnimation2D,
	VSFillDebug2D,
	VSGrayPostProcess,
	VSGrid2D,
	VSLightAnimation2D,
	VSLightSprite2D,
	VSLineDebug2D,
	VSNextScene,
	VSSprite2D,
	VSUI2D,
	VSWave,
	End
};

const wchar_t* EnumResourcePath(eResShader type);

