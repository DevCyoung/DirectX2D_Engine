#pragma once
#include "PanelUI.h"
class GameObject;


class EditorViewUI : public PanelUI
{
public:
	EditorViewUI();
	~EditorViewUI();

private:
	// PanelUI��(��) ���� ��ӵ�
	virtual void update() final;
	void drawForm() override;

private:
	GameObject* mEditorCamera;
};

