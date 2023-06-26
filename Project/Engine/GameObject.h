﻿#pragma once
#include "Entity.h"
#include "ComponentTrait.h"
#include "ScriptComponentTrait.h"
#include "EnumComponent.h"

class Component;
class ScriptComponent;
enum class eScriptComponentType;

class GameObject : public Entity
{
	friend class Layer;
public:
	enum class eState
	{
		Active,
		Paused,
		Dead,
	};

	GameObject();
	virtual ~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

public:
	//FIXME! 이벤트방식으로 변경해야함
	template<typename T>
	void AddComponent(T* const component);
	template<typename T>
	void AddComponent();
	void AddComponent(ScriptComponent* const component);
	void AddComponent(Component* const component);

	template<typename T>
	T* GetComponentOrNull() const;
	template<typename T>
	T* GetComponent() const;
	Component* GetComponentOrNull(eComponentType type) const;
	Component* GetComponent(eComponentType type) const;
	ScriptComponent* GetComponentOrNull(eScriptComponentType type) const;
	ScriptComponent* GetComponent(eScriptComponentType type) const;

	void RemoveComponent(eComponentType type);
	void RemoveComponent(eScriptComponentType type);

private:
	void initialize();
	void update();
	void lateUpdate();
	void render();

private:
	eState mState;
	Component* mEngineComponents[static_cast<UINT>(eComponentType::End)];
	std::vector<ScriptComponent*> mUserComponents;
};

template<typename T>
inline void GameObject::AddComponent(T* const component)
{
	static_assert(engine_component_type<T>::value || script_component_type<T>::value);
	Assert(component, WCHAR_IS_NULLPTR);
	Assert(!(component->mOwner), WCHAR_IS_NOT_NULLPTR);

	if constexpr (engine_component_type<T>::value)
	{
		Assert(!mEngineComponents[static_cast<UINT>(engine_component_type<T>::type)], WCHAR_IS_NOT_NULLPTR);
		mEngineComponents[static_cast<UINT>(engine_component_type<T>::type)] = component;
	}
	else if constexpr (script_component_type<T>::value)
	{
		for (const ScriptComponent* const curScript : mUserComponents)
		{
			//이미존재한다면
			if (curScript->GetScriptType() == script_component_type<T>::type)
			{
				Assert(false, "already Exist Script");
				break;
			}
		}
		mUserComponents.push_back(component);
	}

	component->mOwner = this;
}

template<typename T>
inline void GameObject::AddComponent()
{
	static_assert(engine_component_type<T>::value || script_component_type<T>::value);

	T* const component = new T();
	Assert(component, WCHAR_IS_NULLPTR);

	AddComponent(component);
}

template<typename T>
inline T* GameObject::GetComponentOrNull() const
{
	static_assert(engine_component_type<T>::value || script_component_type<T>::value);

	T* component = nullptr;
	if constexpr (engine_component_type<T>::value) // engine component
	{
		component = dynamic_cast<T*>(mEngineComponents[static_cast<UINT>(engine_component_type<T>::type)]);
	}
	else if constexpr (script_component_type<T>::value) // user component
	{
		for (ScriptComponent* const script : mUserComponents)
		{
			if (script->GetScriptType() == script_component_type<T>::type)
			{
				component = dynamic_cast<T*>(script);
				break;
			}
		}
	}

	return component;
}

template<typename T>
inline T* GameObject::GetComponent() const
{
	static_assert(engine_component_type<T>::value || script_component_type<T>::value);

	T* component = GetComponentOrNull<T>();

	Assert(component, WCHAR_IS_NULLPTR);
	return component;
}
