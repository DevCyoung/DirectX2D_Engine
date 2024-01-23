#pragma once
#include <string>

class ScriptComponent;

enum class eScriptComponentType 
{
	AfterImage,
	CameraInputMoveMent,
	CursorMovement,
	GalssWindow,
	GlassParticle,
	GridPainter,
	HeadHunterLazer,
	SimpleEditorCollider2D,
	End
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type);
ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName);
ScriptComponent * CreateScriptComponentByEnum(const eScriptComponentType type);

