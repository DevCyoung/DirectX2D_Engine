#include "pch.h"
#include "ComponentUI.h"
#include <Engine/EnumComponent.h>
#include <Content/EnumScriptComponent.h>

void TransformUI(eComponentType componentType)
{

}

void ImGui::ComponentUI(eComponentType componentType)
{
	switch (componentType)
	{
	case eComponentType::Transform:
		TransformUI(componentType);
		break;
	case eComponentType::Animator2D:
		break;
	case eComponentType::AudioListener:
		break;
	case eComponentType::AudioSource:
		break;
	case eComponentType::Camera:
		break;
	case eComponentType::CircleCollider2D:
		break;
	case eComponentType::EngineText:
		break;
	case eComponentType::Light2D:
		break;
	case eComponentType::LineCollider2D:
		break;
	case eComponentType::ParticleSystem:
		break;
	case eComponentType::RectCollider2D:
		break;
	case eComponentType::Rigidbody2D:
		break;
	case eComponentType::SpriteRenderer:
		break;
	case eComponentType::End:
		break;
	case eComponentType::ScriptComponent:
		break;
	default:
		break;
	}
}

void ImGui::ScriptComponentUI(eScriptComponentType scriptComponentType)
{
	switch (scriptComponentType)
	{
	case eScriptComponentType::CameraInputMoveMent:
		break;
	case eScriptComponentType::CursorMovement:
		break;
	case eScriptComponentType::End:
		break;
	default:
		break;
	}
}

