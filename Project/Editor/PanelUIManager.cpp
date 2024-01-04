#include "pch.h"
#include "PanelUIManager.h"
#include "PanelUI.h"

PanelUIManager::PanelUIManager()
	: mPanelUIs()
{
	mPanelUIs.reserve(100);
}

PanelUIManager::~PanelUIManager()
{
	memory::safe::DeleteVec(mPanelUIs);
}

void PanelUIManager::AddPanel(PanelUI* const panelUI)
{
	Assert(panelUI, WCHAR_IS_NULLPTR);
	
	mPanelUIs.push_back(panelUI);
}

PanelUI* PanelUIManager::FindPanelUIOrNull(const std::string& title)
{
	PanelUI* resultPanelUI = nullptr;

	for (PanelUI* const panelUI : mPanelUIs)
	{
		if (panelUI->GetTitle() == title)
		{
			resultPanelUI = panelUI;
			break;
		}
	}

	return resultPanelUI;
}

void PanelUIManager::run()
{
	for (PanelUI* panelUI : mPanelUIs)
	{
		panelUI->update();
	}

	for (PanelUI* panelUI : mPanelUIs)
	{
		panelUI->finalUpdate();
	}

	for (PanelUI* panelUI : mPanelUIs)
	{
		panelUI->render();
	}
}
