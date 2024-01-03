#pragma once
#include <string>

class Component;

enum class eComponentType 
{
	Transform,
	Camera,
	AfterImage,
	Animator2D,
	AudioListener,
	AudioSource,
	CircleCollider2D,
	EngineText,
	Light2D,
	LineCollider2D,
	ParticleSystem,
	RectCollider2D,
	Rigidbody2D,
	SpriteRenderer,
	End,
	ScriptComponent
};

const wchar_t* GetComponentName(const eComponentType type);
Component* CreateComponentByName(const std::wstring& componentName);
Component * CreateComponentByEnum(const eComponentType type);

