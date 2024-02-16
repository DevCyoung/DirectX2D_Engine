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

	// PanelUI��(��) ���� ��ӵ�
private:
	void drawForm() override;
	void update() override;	
};



