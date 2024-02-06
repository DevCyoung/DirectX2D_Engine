#include "pch.h"
#include "MeshRenderer.h"
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

MeshRenderer::MeshRenderer()
	: RenderComponent(eComponentType::MeshRenderer)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::render(const Camera* const camera)
{
	Assert(mMesh, ASSERT_MSG_NULL);
	Assert(mMaterial, ASSERT_MSG_NULL);
	Assert(camera, ASSERT_MSG_NULL);

	tCBTransform CBTransform = {};
	{
		const Vector3& SCALE = 
			Vector3(mMaterial->GetTexture(TEX_0)->GetWidth(),
				mMaterial->GetTexture(TEX_0)->GetHeight(), 1.f);

		const Matrix& SCALE_MATRIX = Matrix::CreateScale(SCALE);

		CBTransform.World	= SCALE_MATRIX * GetOwner()->GetComponent<Transform>()->GetWorldMatrix();
		CBTransform.View	= camera->GetView();
		CBTransform.Proj	= camera->GetProjection();

		CBTransform.WV		= CBTransform.World * CBTransform.View;
		CBTransform.WVP		= CBTransform.WV * CBTransform.Proj;

		gGraphicDevice->PassCB(eCBType::Transform, sizeof(CBTransform), &CBTransform);	
		gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);
		gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::PS);
	}	
	//shader, Texture
	GetMaterial()->UpdateData();

	gGraphicDevice->BindMesh(mMesh, 0);	
	gGraphicDevice->Draw(mMesh, 0);
}
