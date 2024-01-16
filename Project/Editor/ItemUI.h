#pragma once
#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_dx11.h>
#include <ImGUI/imgui_impl_win32.h>

class ItemUI
{
public:
	ItemUI();
	virtual ~ItemUI();

	void AddChildItemUI(ItemUI* const itemUI) 
	{ 
		Assert(itemUI, ASSERT_MSG_NOT_NULL); 
		mChildItemUIs.push_back(itemUI); 
	}

	void SetName(const std::string& itemName) { mItemName = itemName; }
	const std::string& GetName() { return mItemName; };
	ItemUI* FindItemUIOrNull(const std::string& itemUIName);

public:
	virtual void render();

private:
	std::string mItemName;
	std::vector<ItemUI*> mChildItemUIs;
};

