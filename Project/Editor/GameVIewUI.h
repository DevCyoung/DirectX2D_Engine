#pragma once
#include "PanelUI.h"


class GameVIewUI : public PanelUI
{
	// PanelUI을(를) 통해 상속됨
	virtual void update() final;
	void drawForm() override;
};

