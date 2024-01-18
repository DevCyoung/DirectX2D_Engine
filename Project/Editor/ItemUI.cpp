#include "pch.h"
#include "ItemUI.h"
#include "LogUI.h"
ItemUI::ItemUI()
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
		ImGui::SetMouseCursor(0);
		LogUI::Log("click resource %s\n", mItemName.c_str());
	}		
}
