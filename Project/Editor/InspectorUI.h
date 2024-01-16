#pragma once
#include "PanelUI.h"
#include "FolderUI.h"

class InspectorUI : public PanelUI
{
public:
	InspectorUI();
	virtual ~InspectorUI();

	// PanelUI을(를) 통해 상속됨
private:
	void drawForm() override;
	void update() override;

	FolderUI mResourceUI;	
};

