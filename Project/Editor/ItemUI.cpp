#include "pch.h"
#include "ItemUI.h"

ItemUI::ItemUI()
{
}

ItemUI::~ItemUI()
{
	memory::safe::DeleteVec(mChildItemUIs);
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
	ImGui::BulletText(mItemName.c_str());
}
