#pragma once
#include "PanelUI.h"
class GameObject;


class EditorViewUI : public PanelUI
{
public:
	EditorViewUI();
	~EditorViewUI();

private:
	// PanelUI을(를) 통해 상속됨
	virtual void update() final;
	void drawForm() override;

private:
	GameObject* mEditorCamera;
};

