# include "pch.h"
#include <Engine/Component.h>


void ComponentUI(Component* component)
{
	
	ImGui::Text("%d", component->GetID());
}
	