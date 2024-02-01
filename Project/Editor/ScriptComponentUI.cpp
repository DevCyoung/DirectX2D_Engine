# include "pch.h"
#include <Engine/ScriptComponent.h>
class Component;
void ComponentUI(Component* component);

void ScriptComponentUI(ScriptComponent* component)
{
	ComponentUI(component);
}
