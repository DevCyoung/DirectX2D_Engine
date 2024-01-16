#include "pch.h"
#include "PanelUI.h"
#include "Editor.h"

PanelUI::PanelUI()
	: mbRender(true)
	, mTitle("NONE")
{
}

PanelUI::~PanelUI()
{
	memory::safe::DeleteVec(mItemUIs);
	memory::safe::DeleteVec(mChildPanels);
}

void PanelUI::render()
{
	if (false == mbRender)
	{
		return;
	}

	drawForm();	
}
