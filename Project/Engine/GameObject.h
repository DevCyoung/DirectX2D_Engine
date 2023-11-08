#pragma once
#include "Entity.h"
#include "ComponentTrait.h"
#include "EnumComponent.h"
#include "EnumLayer.h"
#include "ScriptType.h"

class ScriptComponent;
class GameSystem;

class GameObject : public Entity
{
	friend class Layer;
	friend class Scene;

public:
	enum class eState
	{
		InActive,
		Active,
		Destroy,
	};

	GameObject();
	virtual ~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

public:
	template<typename T>
		requires (std::is_base_of_v<Component, T>)
	T* GetComponentOrNull() const;
	template<typename T>
		requires (is_component_type<T>::value)
	T* GetComponent() const;	

	Component* GetComponentOrNull(const eComponentType componentType) const;
	ScriptComponent* GetComponentOrNull(const eScriptComponentType scriptComponentType) const;

	const std::vector<ScriptComponent*>& GetScriptComponents() const { return mUserComponents; }

	eState GetState() const { return mState; }
	eLayerType GetLayer() const { return mLayerType; };

	GameObject* GetParentOrNull() const { return mParent; }
	GameSystem* GetGameSystem() const { return mGameSystem; }

	//RenderTargetRenderer* GetRenderTargetRenderer() const
	//{
	//	Assert(mRenderTargetRenderer, WCHAR_IS_NULLPTR);
	//
	//	return mRenderTargetRenderer;
	//}

	//FIXME:
	void SetParent(GameObject* const parent) { mParent = parent; }

	template<typename T>
		requires (is_component_type<T>::value)
	void AddComponent(T* const component);
	template<typename T>
		requires (is_component_type<T>::value)
	void AddComponent();
	void AddComponent(ScriptComponent* const component);
	void AddComponent(Component* const component);

	void RemoveComponent(const eComponentType componentType);
	void RemoveComponent(const eScriptComponentType scriptComponentType);

private:
	void initialize();	
	void update();	
	void fixedUpdate();
	void lateUpdate();
	void lastUpdate();

private:
	Component* mEngineComponents[static_cast<UINT>(eComponentType::End)];
	std::vector<ScriptComponent*> mUserComponents;
	eLayerType mLayerType;
	eState mState;
	GameObject* mParent;
	GameSystem* mGameSystem;
	//RenderTargetRenderer* mRenderTargetRenderer;
};

template<typename T>
	requires (is_component_type<T>::value)
inline void GameObject::AddComponent(T* const component)
{	
	Assert(component, WCHAR_IS_NULLPTR);
	Assert(!(component->mOwner), WCHAR_IS_NOT_NULLPTR);
	Assert(!(GetComponentOrNull<T>()), WCHAR_IS_NOT_NULLPTR);

	component->mOwner = this;

	if constexpr (engine_component_type<T>::value)
	{		
		mEngineComponents[static_cast<UINT>(engine_component_type<T>::type)] = component;
	}
	else if constexpr (script_component_type<T>::value)
	{		
		mUserComponents.push_back(component);
	}
}

template<typename T>
	requires (is_component_type<T>::value)
inline void GameObject::AddComponent()
{
	T* const component = new T();

	AddComponent(component);
}

template<typename T>
	requires (std::is_base_of_v<Component, T>)
inline T* GameObject::GetComponentOrNull() const
{
	T* component = nullptr;

	if constexpr (engine_component_type<T>::value) // engine component
	{
		component = dynamic_cast<T*>(mEngineComponents[static_cast<UINT>(engine_component_type<T>::type)]);
	}
	else if constexpr (script_component_type<T>::value) // user component
	{
		for (ScriptComponent* const script : mUserComponents)
		{
			if (GetScriptComponentType(script) == script_component_type<T>::type)
			{
				component = dynamic_cast<T*>(script);

				break;
			}
		}
	}
	else
	{
		if constexpr (std::is_base_of_v<ScriptComponent, T>)
		{
			for (ScriptComponent* scriptComponent : mUserComponents)
			{
				component = dynamic_cast<T*>(scriptComponent);

				if (component)
				{
					break;
				}
			}
		}
		else
		{
			for (Component* engineComponent : mEngineComponents)
			{
				component = dynamic_cast<T*>(engineComponent);

				if (component)
				{
					break;
				}
			}

		}		
	}
	return component;
}

template<typename T>
	requires (is_component_type<T>::value)
inline T* GameObject::GetComponent() const
{	
	T* const component = GetComponentOrNull<T>();

	Assert(component, WCHAR_IS_NULLPTR);

	return component;
}
