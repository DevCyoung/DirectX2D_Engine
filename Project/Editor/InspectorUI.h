#pragma once
#include "PanelUI.h"
class GameObject;
class InspectorUI : public PanelUI
{
public:
	InspectorUI();
	virtual ~InspectorUI();
	GameObject* mGameObject;
	// PanelUI을(를) 통해 상속됨
private:
	void drawForm() override;
	void update() override;	
};



