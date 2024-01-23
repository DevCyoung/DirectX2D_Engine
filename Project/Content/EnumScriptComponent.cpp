#include "pch.h"
#include "EnumScriptComponent.h"

#include "AfterImage.h"
#include "CameraInputMoveMent.h"
#include "CursorMovement.h"
#include "GalssWindow.h"
#include "GlassParticle.h"
#include "GridPainter.h"
#include "HeadHunterLazer.h"
#include "SimpleEditorCollider2D.h"

static constexpr const wchar_t* const ScriptComponentNames[static_cast<UINT>(eScriptComponentType::End)]
{
	L"AfterImage",
	L"CameraInputMoveMent",
	L"CursorMovement",
	L"GalssWindow",
	L"GlassParticle",
	L"GridPainter",
	L"HeadHunterLazer",
	L"SimpleEditorCollider2D",
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type)
{
	assert(static_cast<UINT>(type) < static_cast<UINT>(eScriptComponentType::End));
	return ScriptComponentNames[static_cast<UINT>(type)];
}

ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName)
{
	ScriptComponent* scriptcomponent = nullptr;

	if (L"AfterImage" == scriptcomponentName)
		scriptcomponent = new AfterImage;
	else if (L"CameraInputMoveMent" == scriptcomponentName)
		scriptcomponent = new CameraInputMoveMent;
	else if (L"CursorMovement" == scriptcomponentName)
		scriptcomponent = new CursorMovement;
	else if (L"GalssWindow" == scriptcomponentName)
		scriptcomponent = new GalssWindow;
	else if (L"GlassParticle" == scriptcomponentName)
		scriptcomponent = new GlassParticle;
	else if (L"GridPainter" == scriptcomponentName)
		scriptcomponent = new GridPainter;
	else if (L"HeadHunterLazer" == scriptcomponentName)
		scriptcomponent = new HeadHunterLazer;
	else if (L"SimpleEditorCollider2D" == scriptcomponentName)
		scriptcomponent = new SimpleEditorCollider2D;
	else
		assert(false);
	return scriptcomponent;
}

ScriptComponent* CreateScriptComponentByEnum(const eScriptComponentType type)
{
	ScriptComponent* scriptcomponent = nullptr;

	switch (type)
	{
	case eScriptComponentType::AfterImage:
		scriptcomponent = new AfterImage;
		break;
	case eScriptComponentType::CameraInputMoveMent:
		scriptcomponent = new CameraInputMoveMent;
		break;
	case eScriptComponentType::CursorMovement:
		scriptcomponent = new CursorMovement;
		break;
	case eScriptComponentType::GalssWindow:
		scriptcomponent = new GalssWindow;
		break;
	case eScriptComponentType::GlassParticle:
		scriptcomponent = new GlassParticle;
		break;
	case eScriptComponentType::GridPainter:
		scriptcomponent = new GridPainter;
		break;
	case eScriptComponentType::HeadHunterLazer:
		scriptcomponent = new HeadHunterLazer;
		break;
	case eScriptComponentType::SimpleEditorCollider2D:
		scriptcomponent = new SimpleEditorCollider2D;
		break;
	default:
		assert(false);
		break;
	}
	return scriptcomponent;
}

