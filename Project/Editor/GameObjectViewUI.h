#pragma once
#include "PanelUI.h"
class GameObjectViewUI : public PanelUI
{
public:
	GameObjectViewUI();
	~GameObjectViewUI();

private:
	// PanelUI��(��) ���� ��ӵ�
	virtual void update() final;
	void drawForm() override;
};

