#pragma once

#include "KatanaScene.h"

class HeadHunterScene : public KatanaScene
{
public:
	HeadHunterScene();
	virtual ~HeadHunterScene();
	HeadHunterScene(const HeadHunterScene&) = delete;
	HeadHunterScene& operator=(const HeadHunterScene&) = delete;

	// KatanaScene��(��) ���� ��ӵ�
	virtual void AddMapObject() override;
	virtual void AddWallObject() override;
	virtual void AddDoorObject() override;
	virtual void AddMonsterObject() override;
	virtual void AddObject() override;
	virtual void AddLightObject() override;
	virtual void AddCameraObject() override;
	virtual void AddUIObject() override;
	virtual void AddPlayerObject() override;
	virtual Scene* Clone() override;

	// KatanaScene��(��) ���� ��ӵ�
	virtual KatanaScene* GetNextScene() override;
};

