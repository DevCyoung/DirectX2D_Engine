﻿#include "pch.h"
#include "EnumScriptComponent.h"

#include "Bugiman.h"
#include "BulletMovement.h"
#include "CameraInputMoveMent.h"
#include "ChildTest.h"
#include "Chinatown04Controller.h"
#include "CursorMovement.h"
#include "InputMovementTest.h"
#include "LerpTest.h"
#include "NoiseTest.h"
#include "ParentTest.h"
#include "PickPixelTest.h"
#include "PlayerController.h"
#include "PlayerMovementTest.h"
#include "ShiftController.h"
#include "TestScript.h"
#include "UIEffect.h"

static constexpr const wchar_t* const ScriptComponentNames[static_cast<UINT>(eScriptComponentType::End)]
{
	L"Bugiman",
	L"BulletMovement",
	L"CameraInputMoveMent",
	L"ChildTest",
	L"Chinatown04Controller",
	L"CursorMovement",
	L"InputMovementTest",
	L"LerpTest",
	L"NoiseTest",
	L"ParentTest",
	L"PickPixelTest",
	L"PlayerController",
	L"PlayerMovementTest",
	L"ShiftController",
	L"TestScript",
	L"UIEffect",
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type)
{
	assert(static_cast<UINT>(type) < static_cast<UINT>(eScriptComponentType::End));
	return ScriptComponentNames[static_cast<UINT>(type)];
}

ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName)
{
	ScriptComponent* scriptcomponent = nullptr;

	if (L"Bugiman" == scriptcomponentName)
		scriptcomponent = new Bugiman;
	else if (L"BulletMovement" == scriptcomponentName)
		scriptcomponent = new BulletMovement;
	else if (L"CameraInputMoveMent" == scriptcomponentName)
		scriptcomponent = new CameraInputMoveMent;
	else if (L"ChildTest" == scriptcomponentName)
		scriptcomponent = new ChildTest;
	else if (L"Chinatown04Controller" == scriptcomponentName)
		scriptcomponent = new Chinatown04Controller;
	else if (L"CursorMovement" == scriptcomponentName)
		scriptcomponent = new CursorMovement;
	else if (L"InputMovementTest" == scriptcomponentName)
		scriptcomponent = new InputMovementTest;
	else if (L"LerpTest" == scriptcomponentName)
		scriptcomponent = new LerpTest;
	else if (L"NoiseTest" == scriptcomponentName)
		scriptcomponent = new NoiseTest;
	else if (L"ParentTest" == scriptcomponentName)
		scriptcomponent = new ParentTest;
	else if (L"PickPixelTest" == scriptcomponentName)
		scriptcomponent = new PickPixelTest;
	else if (L"PlayerController" == scriptcomponentName)
		scriptcomponent = new PlayerController;
	else if (L"PlayerMovementTest" == scriptcomponentName)
		scriptcomponent = new PlayerMovementTest;
	else if (L"ShiftController" == scriptcomponentName)
		scriptcomponent = new ShiftController;
	else if (L"TestScript" == scriptcomponentName)
		scriptcomponent = new TestScript;
	else if (L"UIEffect" == scriptcomponentName)
		scriptcomponent = new UIEffect;
	else
		assert(false);
	return scriptcomponent;
}

ScriptComponent* CreateScriptComponentByEnum(const eScriptComponentType type)
{
	ScriptComponent* scriptcomponent = nullptr;

	switch (type)
	{
	case eScriptComponentType::Bugiman:
		scriptcomponent = new Bugiman;
		break;
	case eScriptComponentType::BulletMovement:
		scriptcomponent = new BulletMovement;
		break;
	case eScriptComponentType::CameraInputMoveMent:
		scriptcomponent = new CameraInputMoveMent;
		break;
	case eScriptComponentType::ChildTest:
		scriptcomponent = new ChildTest;
		break;
	case eScriptComponentType::Chinatown04Controller:
		scriptcomponent = new Chinatown04Controller;
		break;
	case eScriptComponentType::CursorMovement:
		scriptcomponent = new CursorMovement;
		break;
	case eScriptComponentType::InputMovementTest:
		scriptcomponent = new InputMovementTest;
		break;
	case eScriptComponentType::LerpTest:
		scriptcomponent = new LerpTest;
		break;
	case eScriptComponentType::NoiseTest:
		scriptcomponent = new NoiseTest;
		break;
	case eScriptComponentType::ParentTest:
		scriptcomponent = new ParentTest;
		break;
	case eScriptComponentType::PickPixelTest:
		scriptcomponent = new PickPixelTest;
		break;
	case eScriptComponentType::PlayerController:
		scriptcomponent = new PlayerController;
		break;
	case eScriptComponentType::PlayerMovementTest:
		scriptcomponent = new PlayerMovementTest;
		break;
	case eScriptComponentType::ShiftController:
		scriptcomponent = new ShiftController;
		break;
	case eScriptComponentType::TestScript:
		scriptcomponent = new TestScript;
		break;
	case eScriptComponentType::UIEffect:
		scriptcomponent = new UIEffect;
		break;
	default:
		assert(false);
		break;
	}
	return scriptcomponent;
}

