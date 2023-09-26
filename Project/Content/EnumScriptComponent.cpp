﻿#include "pch.h"
#include "EnumScriptComponent.h"

#include "NoiseTest.h"
#include "PlayerPath.h"
#include "GangsterAI.h"
#include "AfterImage.h"
#include "AxeMovement.h"
#include "Bugiman.h"
#include "BulletMovement.h"
#include "CameraInputMoveMent.h"
#include "ChildTest.h"
#include "Chinatown04Controller.h"
#include "CursorMovement.h"
#include "FolowPlayer.h"
#include "GridPainter.h"
#include "InputMovementTest.h"
#include "KissyfaceAI.h"
#include "LerpTest.h"
#include "ParentTest.h"
#include "PathNode.h"
#include "PickPixelTest.h"
#include "PlayerController.h"
#include "PlayerMovementTest.h"
#include "Rect2DInterpolation.h"
#include "RewindComponent.h"
#include "ShiftController.h"
#include "SimpleDrawPoint.h"
#include "SimpleEditorCollider2D.h"
#include "TestScript.h"
#include "UIEffect.h"

static constexpr const wchar_t* const ScriptComponentNames[static_cast<UINT>(eScriptComponentType::End)]
{
	L"NoiseTest",
	L"PlayerPath",
	L"GangsterAI",
	L"AfterImage",
	L"AxeMovement",
	L"Bugiman",
	L"BulletMovement",
	L"CameraInputMoveMent",
	L"ChildTest",
	L"Chinatown04Controller",
	L"CursorMovement",
	L"FolowPlayer",
	L"GridPainter",
	L"InputMovementTest",
	L"KissyfaceAI",
	L"LerpTest",
	L"ParentTest",
	L"PathNode",
	L"PickPixelTest",
	L"PlayerController",
	L"PlayerMovementTest",
	L"Rect2DInterpolation",
	L"RewindComponent",
	L"ShiftController",
	L"SimpleDrawPoint",
	L"SimpleEditorCollider2D",
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

	if (L"NoiseTest" == scriptcomponentName)
		scriptcomponent = new NoiseTest;
	else if (L"PlayerPath" == scriptcomponentName)
		scriptcomponent = new PlayerPath;
	else if (L"GangsterAI" == scriptcomponentName)
		scriptcomponent = new GangsterAI;
	else if (L"AfterImage" == scriptcomponentName)
		scriptcomponent = new AfterImage;
	else if (L"AxeMovement" == scriptcomponentName)
		scriptcomponent = new AxeMovement;
	else if (L"Bugiman" == scriptcomponentName)
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
	else if (L"FolowPlayer" == scriptcomponentName)
		scriptcomponent = new FolowPlayer;
	else if (L"GridPainter" == scriptcomponentName)
		scriptcomponent = new GridPainter;
	else if (L"InputMovementTest" == scriptcomponentName)
		scriptcomponent = new InputMovementTest;
	else if (L"KissyfaceAI" == scriptcomponentName)
		scriptcomponent = new KissyfaceAI;
	else if (L"LerpTest" == scriptcomponentName)
		scriptcomponent = new LerpTest;
	else if (L"ParentTest" == scriptcomponentName)
		scriptcomponent = new ParentTest;
	else if (L"PathNode" == scriptcomponentName)
		scriptcomponent = new PathNode;
	else if (L"PickPixelTest" == scriptcomponentName)
		scriptcomponent = new PickPixelTest;
	else if (L"PlayerController" == scriptcomponentName)
		scriptcomponent = new PlayerController;
	else if (L"PlayerMovementTest" == scriptcomponentName)
		scriptcomponent = new PlayerMovementTest;
	else if (L"Rect2DInterpolation" == scriptcomponentName)
		scriptcomponent = new Rect2DInterpolation;
	else if (L"RewindComponent" == scriptcomponentName)
		scriptcomponent = new RewindComponent;
	else if (L"ShiftController" == scriptcomponentName)
		scriptcomponent = new ShiftController;
	else if (L"SimpleDrawPoint" == scriptcomponentName)
		scriptcomponent = new SimpleDrawPoint;
	else if (L"SimpleEditorCollider2D" == scriptcomponentName)
		scriptcomponent = new SimpleEditorCollider2D;
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
	case eScriptComponentType::NoiseTest:
		scriptcomponent = new NoiseTest;
		break;
	case eScriptComponentType::PlayerPath:
		scriptcomponent = new PlayerPath;
		break;
	case eScriptComponentType::GangsterAI:
		scriptcomponent = new GangsterAI;
		break;
	case eScriptComponentType::AfterImage:
		scriptcomponent = new AfterImage;
		break;
	case eScriptComponentType::AxeMovement:
		scriptcomponent = new AxeMovement;
		break;
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
	case eScriptComponentType::FolowPlayer:
		scriptcomponent = new FolowPlayer;
		break;
	case eScriptComponentType::GridPainter:
		scriptcomponent = new GridPainter;
		break;
	case eScriptComponentType::InputMovementTest:
		scriptcomponent = new InputMovementTest;
		break;
	case eScriptComponentType::KissyfaceAI:
		scriptcomponent = new KissyfaceAI;
		break;
	case eScriptComponentType::LerpTest:
		scriptcomponent = new LerpTest;
		break;
	case eScriptComponentType::ParentTest:
		scriptcomponent = new ParentTest;
		break;
	case eScriptComponentType::PathNode:
		scriptcomponent = new PathNode;
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
	case eScriptComponentType::Rect2DInterpolation:
		scriptcomponent = new Rect2DInterpolation;
		break;
	case eScriptComponentType::RewindComponent:
		scriptcomponent = new RewindComponent;
		break;
	case eScriptComponentType::ShiftController:
		scriptcomponent = new ShiftController;
		break;
	case eScriptComponentType::SimpleDrawPoint:
		scriptcomponent = new SimpleDrawPoint;
		break;
	case eScriptComponentType::SimpleEditorCollider2D:
		scriptcomponent = new SimpleEditorCollider2D;
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

