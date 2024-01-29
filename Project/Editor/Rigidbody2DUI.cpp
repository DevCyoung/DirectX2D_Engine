# include "pch.h"
#include <Engine/Rigidbody2D.h>


void Rigidbody2DUI(Rigidbody2D* component)
{
	bool useGravity = component->IsGravity();
	ImGui::Checkbox("useGravity", &useGravity);
	if (useGravity)
	{
		component->TurnOnGravity();
	}
	else
	{
		component->TurnOffGravity();
	}
}
