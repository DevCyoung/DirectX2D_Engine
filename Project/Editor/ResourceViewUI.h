#pragma once
#include "PanelUI.h"
#include "FolderUI.h"

class ResourceViewUI : public PanelUI
{
public:
	ResourceViewUI();
	virtual ~ResourceViewUI();

	// PanelUI을(를) 통해 상속됨
private:
	void drawForm() override;
	void update() override;

	FolderUI mResourceUI;
};

