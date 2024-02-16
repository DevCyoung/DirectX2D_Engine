#include "pch.h"
#include "Material.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "ConstantBuffer.h"
#include "EnumShaderBindStage.h"
#include "Shader.h"
#include "EnumResource.h"

Material::Material()
	: Resource(eResourceType::Material)
	, mShader(nullptr)
	, mTextures{ 0, }
	, mRenderType(eRenderPriorityType::Opqaue)
{
}
Material::Material(const eRenderPriorityType renderPriorityType)
	: Resource(eResourceType::Material)
	, mShader(nullptr)
	, mTextures{0,}
	, mRenderType(renderPriorityType)
{
}

Material::~Material()
{
}

HRESULT Material::Load(const std::wstring& filePath)
{
	Assert(false, "");

	(void)filePath;
	return E_NOTIMPL;
}

void Material::UpdateData()
{
	gGraphicDevice->BindIA(mShader);
	gGraphicDevice->BindVS(mShader);
	//gGraphicDevice->BindHS(mShader);
	//gGraphicDevice->BindGS(mShader);
	//gGraphicDevice->BindDS(mShader);
	gGraphicDevice->BindPS(mShader);

	gGraphicDevice->BindRS(mShader->GetRSType());
	gGraphicDevice->BindDS(mShader->GetDSType());
	gGraphicDevice->BindBS(mShader->GetBSType());

		
	// Texture Update
	for (UINT i = 0; i < TEX_END; ++i)
	{
		if (nullptr == mTextures[i])
		{
			mData.arrBTex[i] = 0;
			continue;
		}

		else
		{
			mData.arrBTex[i] = 1;
			gGraphicDevice->BindSRV(eShaderBindType::VS, i, mTextures[i]);
			gGraphicDevice->BindSRV(eShaderBindType::HS, i, mTextures[i]);
			gGraphicDevice->BindSRV(eShaderBindType::GS, i, mTextures[i]);
			gGraphicDevice->BindSRV(eShaderBindType::DS, i, mTextures[i]);
			gGraphicDevice->BindSRV(eShaderBindType::PS, i, mTextures[i]);
		}
	}


	gGraphicDevice->PassCB(eCBType::Material, sizeof(mData), &mData);
	gGraphicDevice->BindCB(eCBType::Material, eShaderBindType::VS);
	gGraphicDevice->BindCB(eCBType::Material, eShaderBindType::HS);
	gGraphicDevice->BindCB(eCBType::Material, eShaderBindType::GS);
	gGraphicDevice->BindCB(eCBType::Material, eShaderBindType::DS);
	gGraphicDevice->BindCB(eCBType::Material, eShaderBindType::PS);
}
