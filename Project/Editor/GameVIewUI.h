#pragma once
#include "PanelUI.h"


class GameViewUI : public PanelUI
{
	// PanelUI��(��) ���� ��ӵ�
	virtual void update() final;
	void drawForm() override;
};

