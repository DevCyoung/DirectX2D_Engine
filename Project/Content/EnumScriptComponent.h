﻿#pragma once
#include <string>

class ScriptComponent;

enum class eScriptComponentType 
{
	BlaBLa,
	Bugiman,
	CameraInputMove,
	CursorMovement,
	End
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type);
ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName);
ScriptComponent * CreateScriptComponentByEnum(const eScriptComponentType type);

