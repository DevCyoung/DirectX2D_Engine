#pragma once
#include "PanelUI.h"
class GameObject;
class Resource;
class InspectorUI : public PanelUI
{
public:
	InspectorUI();
	virtual ~InspectorUI();

	GameObject* mGameObject;
	Resource* mResource;

	void Register(GameObject* Object);
	void Register(Resource* resource);

	// PanelUI을(를) 통해 상속됨
private:
	void drawForm() override;
	void update() override;	
};



