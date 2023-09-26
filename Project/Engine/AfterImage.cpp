#include "pch.h"
#include "AfterImage.h"
#include "TimeManager.h"
#include "GameSystem.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "CBCollection.h"
#include "StructBuffer.h"
#include "EnumShaderBindStage.h"
#include "EnumSRV.h"
#include "Material.h"
#include "Shader.h"
#include "Animation2D.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Material.h"

#include "Rigidbody2D.h"

AfterImage::AfterImage()
	: RenderComponent(eComponentType::AfterImage)
	, mAnimator(nullptr)
	, mCreateDeltaTime(0.003f)
	, mCurTime(0.f)
	, mAlphaTime(0.5f)
	, mAlphaMaxTime(1.3f)
	, mAlphaSpeed(4.f)
	, colorType(0)
	, count(0)
{
	SetMaterial(gResourceManager->FindOrNull<Material>(L"Animation2D"));
	SetMesh(gResourceManager->FindOrNull<Mesh>(L"FillRect2D"));
}

AfterImage::~AfterImage()
{
}

void AfterImage::initialize()
{
	mAnimator = GetOwner()->GetComponent<Animator2D>();	
}

void AfterImage::update()
{
	RenderComponent::update();

	//Rigidbody2D * rigidbody = GetOwner()->GetComponent<Rigidbody2D>();

	

	//if (rigidbody->GetVelocity().Length() > 400.f)
	//{
	//	mAlphaTime = 1.f;
	//}
	//else
	//{
	//	mAlphaTime = 1.4f;
	//}
	//
	//if (rigidbody->GetVelocity().Length() == 0.f)
	//{
	//	mAlphaTime = 2.f;
	//}


}

void AfterImage::lateUpdate()
{
	//Rigidbody2D* const rigidbody2D = GetOwner()->GetComponentOrNull<Rigidbody2D>();

	mCurTime += gDeltaTime;

	if (count >= 4)
	{
		count = 0;
		colorType = (colorType + 1) % 3;
	}

	if (mCurTime >= mCreateDeltaTime)
	{
		tAfterImageInfo info = {};
		info.CBTransform = mAnimator->GetCBTransform();		
		info.CurTime = mAlphaTime;
		info.MaxTime = mAlphaMaxTime;
		info.CBAnimationInfo = mAnimator->GetCBAnimationInfo();
		info.texture = mAnimator->GetCurAnimationOrNull()->GetAtlas();
		info.colorType = colorType;		

		mCurTime = 0.f;
		afters.push_back(info);

		++count;
	}

	for (auto& item : afters)
	{
		item.CurTime += gDeltaTime * mAlphaSpeed;
		item.Alpha = 1.f - (item.CurTime / item.MaxTime);
	}

	afters.erase(std::remove_if(afters.begin(), afters.end(),
		[](const tAfterImageInfo& info)
		{
			return info.CurTime >= info.MaxTime;
		}), afters.end());
}

void AfterImage::render(const Camera* const camera)
{
	//Rigidbody2D* const rigidbody2D = GetOwner()->GetComponentOrNull<Rigidbody2D>();

	//if (rigidbody2D && rigidbody2D->GetVelocity().Length() == 0.f)
	//{
	//	return;
	//}

	//if (false == IsVisible())
	//{
	//	return;
	//}



	for (auto& info : afters)
	{
		tCBTransform CBTransform = info.CBTransform;
		{
			CBTransform.View = camera->GetView();
			CBTransform.Proj = camera->GetProjection();
			gGraphicDevice->PassCB(eCBType::Transform, sizeof(CBTransform), &CBTransform);
			gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);
		}

		Mesh* mesh = mAnimator->GetMesh();
		Material* material = mAnimator->GetMaterial();

		gGraphicDevice->BindMesh(mesh);
		gGraphicDevice->BindIA(material->GetShader());
		gGraphicDevice->BindPS(material->GetShader());
		gGraphicDevice->BindVS(material->GetShader());
		gGraphicDevice->BindBS(material->GetShader()->GetBSType());
		gGraphicDevice->BindDS(material->GetShader()->GetDSType());
		gGraphicDevice->BindRS(material->GetShader()->GetRSType());

		const Texture* const P_ATLAS = info.texture;
		Assert(P_ATLAS, WCHAR_IS_NULLPTR);

		tCBAnimationInfo CBAnimationInfo = info.CBAnimationInfo;
		{
			gGraphicDevice->PassCB(eCBType::Animation2DInfo, sizeof(CBAnimationInfo), &CBAnimationInfo);
			gGraphicDevice->BindCB(eCBType::Animation2DInfo, eShaderBindType::PS);
		}

		tCBColorInfo CBColorInfo = {};
		{
			CBColorInfo.bUseColor = 1;
			CBColorInfo.Color = Vector4(0.f, 0.f, 0.f, info.Alpha);
			CBColorInfo.bColorType = info.colorType;

			gGraphicDevice->PassCB(eCBType::ColorInfo, sizeof(CBColorInfo), &CBColorInfo);
			gGraphicDevice->BindCB(eCBType::ColorInfo, eShaderBindType::PS);
		}

		gGraphicDevice->BindSRV(eShaderBindType::PS, static_cast<UINT>(eSRVTpye::AtlasAnimation2D), P_ATLAS);

		gGraphicDevice->Draw(mMesh);
	}



	tCBColorInfo CBColorInfo = {};
	{
		CBColorInfo.bUseColor = 0;
		CBColorInfo.Color = Vector4(0.f, 0.f, 0.f, 1.f);

		gGraphicDevice->PassCB(eCBType::ColorInfo, sizeof(CBColorInfo), &CBColorInfo);
		gGraphicDevice->BindCB(eCBType::ColorInfo, eShaderBindType::PS);
	}
}
