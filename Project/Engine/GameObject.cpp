#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "ScriptComponent.h"
#include "EnumLayer.h"

GameObject::GameObject()
	: mEngineComponents{0, }
	, mScriptComponents()
	, mLayerType(eLayerType::Default)
	, mState(eState::Active)
	, mParent(nullptr)
	, mGameSystem(nullptr)
{
	AddComponent<Transform>();
}

GameObject::~GameObject()
{
	mem::del::DeleteVectorElements(&mScriptComponents);
	mem::del::DeletePointerArrayElements(&mEngineComponents);
}

GameObject::GameObject(const GameObject& other)
	: mEngineComponents{0, }
	, mScriptComponents()
	, mLayerType(other.mLayerType)
	, mState(other.mState)
	, mParent(other.mParent)
	, mGameSystem(other.mGameSystem)
{
	//AddComponent<Transform>();

	for (UINT i = 0; i < static_cast<UINT>(eComponentType::End); i++)
	{
		if (other.mEngineComponents[i])
		{
			AddComponent(other.mEngineComponents[i]->Clone());			
		}
	}

	for (UINT i = 0; i < mScriptComponents.size(); i++)
	{
		AddComponent(other.mScriptComponents[i]->Clone());
	}
}

void GameObject::initialize()
{
	Assert(mGameSystem, ASSERT_MSG_NULL);

	for (Component* const component : mEngineComponents)
	{
		if (component)
		{
			component->initialize();
		}
	}

	for (ScriptComponent* const script : mScriptComponents)
	{
		script->initialize();
	}
}

void GameObject::update()
{
	for (Component* const component : mEngineComponents)
	{
		if (component)
		{
			component->update();
		}
	}

	for (ScriptComponent* const script : mScriptComponents)
	{
		script->update();
	}
}

void GameObject::fixedUpdate()
{
	for (Component* const component : mEngineComponents)
	{
		if (component)
		{
			component->fixedUpdate();
		}
	}

	for (ScriptComponent* const script : mScriptComponents)
	{
		script->fixedUpdate();
	}
}


void GameObject::lateUpdate()
{
	for (Component* const component : mEngineComponents)
	{
		if (component)
		{
			component->lateUpdate();
		}
	}

	for (ScriptComponent* const script : mScriptComponents)
	{
		script->lateUpdate();
	}
}


void GameObject::lastUpdate()
{
	for (Component* const component : mEngineComponents)
	{
		if (component)
		{
			component->lastUpdate();
		}
	}

	for (ScriptComponent* const script : mScriptComponents)
	{
		script->lastUpdate();
	}
}

void GameObject::AddComponent(ScriptComponent* const scriptComponent)
{
	Assert(scriptComponent, ASSERT_MSG_NULL);
	Assert(!(scriptComponent->mOwner), ASSERT_MSG_NOT_NULL);
	Assert(!(GetComponentOrNull(scriptComponent->GetScriptType())), ASSERT_MSG_NOT_NULL);

	scriptComponent->mOwner = this;

	mScriptComponents.push_back(scriptComponent);
}

void GameObject::AddComponent(Component* const component)
{
	Assert(component, ASSERT_MSG_NULL);
	Assert(!(component->mOwner), ASSERT_MSG_NOT_NULL);

	component->mOwner = this;

	if (component->GetType() == eComponentType::ScriptComponent)
	{
		ScriptComponent* const scriptComponent = dynamic_cast<ScriptComponent*>(component);

		Assert(scriptComponent, ASSERT_MSG_NULL);

		AddComponent(scriptComponent);
	}
	else
	{
		Assert(!mEngineComponents[static_cast<UINT>(component->GetType())], ASSERT_MSG_NOT_NULL);

		mEngineComponents[static_cast<UINT>(component->GetType())] = component;
	}
}

Component* GameObject::GetComponentOrNull(const eComponentType componentType) const
{
	Assert(static_cast<UINT>(eComponentType::End) > static_cast<UINT>(componentType),
		ASSERT_MSG_INVALID);

	return mEngineComponents[static_cast<UINT>(componentType)];
}

ScriptComponent* GameObject::GetComponentOrNull(const eScriptComponentType scriptComponentType) const
{
	ScriptComponent* component = nullptr;

	for (ScriptComponent* const curScript : mScriptComponents)
	{
		if (curScript->GetScriptType() == scriptComponentType)
		{
			component = curScript;

			break;
		}
	}

	return component;

}

Component* GameObject::GetComponent(const eComponentType componentType) const
{
	Component* const component = GetComponentOrNull(componentType);

	Assert(component, ASSERT_MSG_NULL);

	return component;
}

ScriptComponent* GameObject::GetComponent(const eScriptComponentType scriptComponentType) const
{
	ScriptComponent* const scriptComponent = GetComponentOrNull(scriptComponentType);

	Assert(scriptComponent, ASSERT_MSG_NULL);

	return scriptComponent;
}
