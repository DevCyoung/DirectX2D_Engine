#pragma once
#include "PanelUI.h"
class GameObject;
class InspectorUI : public PanelUI
{
public:
	InspectorUI();
	virtual ~InspectorUI();
	GameObject* mGameObject;
	// PanelUI��(��) ���� ��ӵ�
private:
	void drawForm() override;
	void update() override;	
};



