#pragma once
#include "PanelUI.h"

class TestUI : public PanelUI
{
public:
	TestUI();
	virtual ~TestUI();

private:
	// PanelUI��(��) ���� ��ӵ�
	void drawForm() override;
};

