#pragma once
#include "PanelUI.h"
#include "FolderUI.h"

class ResourceViewUI : public PanelUI
{
public:
	ResourceViewUI();
	virtual ~ResourceViewUI();

	// PanelUI��(��) ���� ��ӵ�
private:
	void drawForm() override;
	void update() override;

	FolderUI mResourceUI;
};

