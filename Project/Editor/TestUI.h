#pragma once
#include "PanelUI.h"

class TestUI : public PanelUI
{
public:
	TestUI();
	virtual ~TestUI();

private:
	// PanelUI을(를) 통해 상속됨
	void drawForm() override;	
};

