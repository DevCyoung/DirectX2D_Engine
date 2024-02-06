#include "pch.h"
#include "Light3D.h"
#include "CBCollection.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include  "Transform.h"
Light3D::Light3D()
	: Component(eComponentType::Light3D)
	, mLightInfo{}
{
	tLight3DInfo info = {};
	info.LightDir = { 1.f, -1.f, 1.f };
	info.LightColor = { 1.f, 1.f, 1.f };
	info.LightSpecCoeff = 0.3f;
	info.LightAmb = { 0.15f, 0.15f, 0.15f };

	mLightInfo = info;
}

Light3D::~Light3D()
{
}

void Light3D::initialize()
{
}

void Light3D::update()
{
}

void Light3D::lateUpdate()
{
	//mLightInfo.LightDir

	Vector3 f = GetComponent<Transform>()->GetForward();
	mLightInfo.LightDir = Vector4(f.x, f.y, f.z, 0.f);

	gGraphicDevice->PassCB(eCBType::Light3D, sizeof(mLightInfo), &mLightInfo);
	gGraphicDevice->BindCBAllShader(eCBType::Light3D);
}
