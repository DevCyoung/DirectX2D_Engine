#include "pch.h"
#include "RenderComponent.h"
#include "RenderTargetRenderer.h"
#include "GameObject.h"
#include "GameSystem.h"
#include "Mesh.h"

RenderComponent::RenderComponent()
	: Component(eComponentType::RenderComponent)
	, mbVisible(true)
	, mMesh(nullptr)
	, mMaterials()
{
}

RenderComponent::RenderComponent(const eComponentType componentType)
	: Component(componentType)
	, mbVisible(true)
	, mMesh(nullptr)
	, mMaterials()
{
}

void RenderComponent::SetMesh(Mesh* const mesh)
{
	Assert(mesh, ASSERT_MSG_NULL);
	mMesh = mesh;
	mMaterials.resize(mMesh->GetIndexBufferCount());

}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::initialize()
{
}

void RenderComponent::update()
{
	if (GetOwner()->GetState() == GameObject::eState::Active && mbVisible)
	{
		GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->registerRenderComponent(this);
	}
}

void RenderComponent::lateUpdate()
{
}
