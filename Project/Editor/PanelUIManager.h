#pragma once
#include <Engine/Singleton.h>

class PanelUI;

class PanelUIManager
{
	friend class Editor;
	SINGLETON_DECLARE(PanelUIManager);

public:
	void AddPanel(PanelUI* const panelUI);
	PanelUI* FindPanelUIOrNull(const std::string& title);

private:
	void run();

private:
	std::vector<PanelUI*> mPanelUIs;
};

