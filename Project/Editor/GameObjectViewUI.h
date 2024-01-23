#pragma once
#include "PanelUI.h"
class GameObjectViewUI : public PanelUI
{
public:
	GameObjectViewUI();
	~GameObjectViewUI();

private:
	// PanelUI을(를) 통해 상속됨
	virtual void update() final;
	void drawForm() override;
};

