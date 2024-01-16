#include "pch.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include "CBCollection.h"
#include "StructBuffer.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "Transform.h"
#include "EnumSRV.h"
#include "ResourceManager.h"
#include "Mesh.h"

SpriteRenderer::SpriteRenderer()
	: RenderComponent(eComponentType::SpriteRenderer)
	, mTestColor(Vector4::One)
	, testX(Vector4::One)
	, bColorInfo(0)	
	, mUvOffsetX(1.f)
	, mSprite2DInfo{}
{	
	mSprite2DInfo.UV = Vector2::One;
	SetMesh(gResourceManager->FindOrNull<Mesh>(L"FillRect2D"));
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::SetUvOffsetX(float uvOffsetX)
{
	mSprite2DInfo.UV.x = uvOffsetX;
}

void SpriteRenderer::SetColorR(float r)
{
	mSprite2DInfo.bSetColorR = 1;
	mSprite2DInfo.R = r;
}

void SpriteRenderer::SetColorG(float g)
{
	mSprite2DInfo.bSetColorG = 1;
	mSprite2DInfo.G = g;
}

void SpriteRenderer::SetColorB(float b)
{
	mSprite2DInfo.bSetColorB = 1;
	mSprite2DInfo.B = b;
}

void SpriteRenderer::SetColorA(float a)
{
	mSprite2DInfo.bSetColorA = 1;
	mSprite2DInfo.A = a;
}

void SpriteRenderer::SetColorReset()
{
	mSprite2DInfo.bSetColorR = 0;
	mSprite2DInfo.bSetColorG = 0;
	mSprite2DInfo.bSetColorB = 0;
	mSprite2DInfo.bSetColorA = 0;
}

void SpriteRenderer::MulColorR(float r)
{
	mSprite2DInfo.bMulColorR = 1;
	mSprite2DInfo.R = r;
}

void SpriteRenderer::MulColorG(float g)
{
	mSprite2DInfo.bMulColorG = 1;
	mSprite2DInfo.G = g;
}

void SpriteRenderer::MulColorB(float b)
{
	mSprite2DInfo.bMulColorB = 1;
	mSprite2DInfo.B = b;
}

void SpriteRenderer::MulColorA(float a)
{
	mSprite2DInfo.bMulColorA = 1;
	mSprite2DInfo.A = a;
}

void SpriteRenderer::MulColorReset()
{
	mSprite2DInfo.bMulColorR = 0;
	mSprite2DInfo.bMulColorG = 0;
	mSprite2DInfo.bMulColorB = 0;
	mSprite2DInfo.bMulColorA = 0;
}

void SpriteRenderer::initialize()
{
}

void SpriteRenderer::update()
{	
	RenderComponent::update();
}

void SpriteRenderer::lateUpdate()
{
}

void SpriteRenderer::render(const Camera* const camera)
{
	Assert(mMesh, ASSERT_MSG_NULL);
	Assert(mMaterial, ASSERT_MSG_NULL);
	Assert(camera, ASSERT_MSG_NULL);

	tCBTransform CBTransform = {};
	{
		const Vector3& SCALE 
			= Vector3(mMaterial->GetTexture()->GetWidth(), mMaterial->GetTexture()->GetHeight(), 1.f);
		const Matrix& SCALE_MATRIX = Matrix::CreateScale(SCALE);

		CBTransform.World = SCALE_MATRIX * GetOwner()->GetComponent<Transform>()->GetWorldMatrix();
		CBTransform.View = camera->GetView();
		CBTransform.Proj = camera->GetProjection();

		gGraphicDevice->PassCB(eCBType::Transform, sizeof(CBTransform), &CBTransform);
		gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);
	}	

	//FIXME: Material Info 범용성있는 방법으로 수정
	tCBColorInfo CBColorInfo = {};
	{
		CBColorInfo.bUseColor = bColorInfo;
		CBColorInfo.Color = testX;

		gGraphicDevice->PassCB(eCBType::ColorInfo, sizeof(CBColorInfo), &CBColorInfo);
		gGraphicDevice->BindCB(eCBType::ColorInfo, eShaderBindType::PS);
	}

	tSprite2DInfo sprite2DInfo = mSprite2DInfo;
	{		
		gGraphicDevice->PassCB(eCBType::Sprite2D, sizeof(sprite2DInfo), &sprite2DInfo);
		gGraphicDevice->BindCB(eCBType::Sprite2D, eShaderBindType::PS);
	}	

	gGraphicDevice->BindMesh(mMesh);
	gGraphicDevice->BindIA(mMaterial->GetShader());
	gGraphicDevice->BindPS(mMaterial->GetShader());
	gGraphicDevice->BindVS(mMaterial->GetShader());
	gGraphicDevice->BindBS(mMaterial->GetShader()->GetBSType());
	gGraphicDevice->BindDS(mMaterial->GetShader()->GetDSType());
	gGraphicDevice->BindRS(mMaterial->GetShader()->GetRSType());	
	gGraphicDevice->BindSRV(eShaderBindType::PS, static_cast<UINT>(eSRVTpye::Sprite2D), mMaterial->GetTexture());
	gGraphicDevice->Draw(mMesh);
}
