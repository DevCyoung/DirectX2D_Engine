#include "pch.h"
#include "ComponentUIRender.h"
#include <Engine/ScriptComponent.h>
#include <Engine/EnumComponent.h>
#include <Content/EnumScriptComponent.h>
class ScriptComponent;
void ScriptComponentUI(ScriptComponent* component);
class CameraInputMoveMent;
void CameraInputMoveMentUI(CameraInputMoveMent* component);
class CursorMovement;
void CursorMovementUI(CursorMovement* component);

void ScriptComponentUIRender(ScriptComponent* component)
{
	switch (component->GetScriptType())
	{
	case eScriptComponentType::CameraInputMoveMent:
		CameraInputMoveMentUI((CameraInputMoveMent*)component);
		break;
	case eScriptComponentType::CursorMovement:
		CursorMovementUI((CursorMovement*)component);
		break;
	}
}

