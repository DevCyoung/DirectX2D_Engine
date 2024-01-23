#pragma once

class GameObject;
enum class eComponentType;
enum class eScriptComponentType;

namespace ImGui
{
	void ComponentUI(const eComponentType componentType);
	void ScriptComponentUI(const eScriptComponentType scriptComponentType);
}