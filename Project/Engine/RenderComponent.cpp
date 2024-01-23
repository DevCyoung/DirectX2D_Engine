#include "pch.h"
#include "RenderComponent.h"
#include "RenderTargetRenderer.h"
#include "GameObject.h"
#include "GameSystem.h"


RenderComponent::RenderComponent()
	: Component(eComponentType::RenderComponent)
	, mbVisible(true)
	, mMesh(nullptr)
	, mMaterial(nullptr)
{
}

RenderComponent::RenderComponent(const eComponentType componentType)
	: Component(componentType)
	, mbVisible(true)
	, mMesh(nullptr)
	, mMaterial(nullptr)
{
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
