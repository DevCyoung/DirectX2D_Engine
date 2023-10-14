#pragma once
#include "KatanaScene.h"

class TItleScene : public KatanaScene
{
public:
	TItleScene();
	virtual ~TItleScene();
	TItleScene(const TItleScene&) = delete;
	TItleScene& operator=(const TItleScene&) = delete;

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
	virtual Scene* NextScene() override;
};

