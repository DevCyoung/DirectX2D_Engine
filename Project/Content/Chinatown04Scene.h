#pragma once
#include "KatanaScene.h"

class Chinatown04Scene : public KatanaScene
{
public:
	Chinatown04Scene();
	virtual ~Chinatown04Scene();
	Chinatown04Scene(const Chinatown04Scene&) = delete;
	Chinatown04Scene& operator=(const Chinatown04Scene&) = delete;

	// KatanaScene��(��) ���� ��ӵ�
	virtual void AddMapObject() override final;
	virtual void AddWallObject() override final;
	virtual void AddDoorObject() override final;
	virtual void AddMonsterObject() override final;
	virtual void AddObject() override final;
	virtual void AddLightObject() override final;
	virtual void AddCameraObject() override final;
	virtual void AddUIObject() override final;
	virtual void AddPlayerObject() override final;

	// Scene��(��) ���� ��ӵ�
	virtual Scene* Clone() override;

	// KatanaScene��(��) ���� ��ӵ�
	virtual Scene* NextScene() override;
};