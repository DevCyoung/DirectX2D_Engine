#pragma once
#include <string>

class Component;

enum class eComponentType 
{
	Transform,
	Animator2D,
	AudioListener,
	AudioSource,
	Camera,
	CircleCollider2D,
	Collider2D,
	Light2D,
	LineCollider2D,
	ParticleSystem,
	RectCollider2D,
	RenderComponent,
	Rigidbody2D,
	SpriteRenderer,
	End,
	ScriptComponent
};

const wchar_t* GetComponentName(const eComponentType type);
Component* CreateComponentByName(const std::wstring& componentName);
Component * CreateComponentByEnum(const eComponentType type);

