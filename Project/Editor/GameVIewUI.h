#pragma once
#include "PanelUI.h"


class GameVIewUI : public PanelUI
{
	// PanelUI��(��) ���� ��ӵ�
	virtual void update() final;
	void drawForm() override;
};

