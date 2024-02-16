#include "pch.h"
#include "ItemUI.h"
#include "LogUI.h"
#include <Engine/String.h>
#include <Engine/GameObject.h>
#include "PanelUIManager.h"
#include "InspectorUI.h"
#include <Engine/ResourceManager.h>

#include <Engine/Texture.h>
#include <Engine/Material.h>
#include <Engine/Mesh.h>
#include <Engine/Shader.h>
#include <Engine/ComputeShader.h>

#include <Engine/String.h>
#include <Engine/Resource.h>

ItemUI::ItemUI()
	:mResource(nullptr)
{
}

ItemUI::~ItemUI()
{
	mem::del::DeleteVectorElements(&mChildItemUIs);
}

ItemUI* ItemUI::FindItemUIOrNull(const std::string& itemUIName)
{
	for (ItemUI* itemUI : mChildItemUIs)
	{
		if (itemUI->GetName() == itemUIName)
		{
			return itemUI;
		}
	}
	return nullptr;
}

void ItemUI::render()
{
	ImGui::Bullet();
	ImGui::Selectable(mItemName.c_str(), false);
	if (ImGui::IsItemClicked())
	{
		//ImGui::SetMouseCursor(0);
		//LogUI::Log("click resource %s\n", mItemName.c_str());

		ImGui::SetMouseCursor(0);
		PanelUI* inspectorUI =
			PanelUIManager::GetInstance()->FindPanelUIOrNull("InspectorUI");

		std::wstring path = helper::String::StrToWStr(mFullName);
		static_cast<InspectorUI*>(inspectorUI)->Register(mResource);	
	}		
}
