#include "pch.h"
#include "AlphaHelper.h"
#include <Engine/ResourceManager.h>
#include <Engine/Texture.h>
#include <Engine/Engine.h>
#include <Engine/GraphicDeviceDx11.h>
#include <Engine/BSCollection.h>
#include <Engine/RSCollection.h>
#include <Engine/RSCollection.h>
#include <Engine/DSCollection.h>
#include <Engine/Shader.h>
#include <Engine/Mesh.h>
#include <Engine/ComputeShader.h>
#include <Engine/StructBuffer.h>
#include <Engine/EnumShaderBindStage.h>
#include <Engine/ConstantBuffer.h>
void TextureAlphaTo(Texture* const dst, Texture* const src, const float alpha)
{
	ComputeShader* cs = gResourceManager->Find<ComputeShader>(L"StdCS");
	{
		tMaterial mat;
		mat.g_int_0 = static_cast<int>(dst->GetWidth());
		mat.g_int_1 = static_cast<int>(dst->GetHeight());
		mat.g_float_0 = 1.0f;

		gGraphicDevice->PassCB(eCBType::Material, sizeof(tMaterial), &mat);
		gGraphicDevice->BindCB(eCBType::Material, eShaderBindType::CS);
	}	
	
	gGraphicDevice->BindUAV(0, src);
	gGraphicDevice->BindUAV(1, dst);
	gGraphicDevice->BindCS(cs);
	gGraphicDevice->Distpatch(cs);

	gGraphicDevice->UnBindUAV(0);
	gGraphicDevice->UnBindUAV(1);
}
