#pragma once
#include "PanelUI.h"
#include "FolderUI.h"

class InspectorUI : public PanelUI
{
public:
	InspectorUI();
	virtual ~InspectorUI();

	// PanelUI��(��) ���� ��ӵ�
private:
	void drawForm() override;
	void update() override;

	FolderUI mResourceUI;	
};

