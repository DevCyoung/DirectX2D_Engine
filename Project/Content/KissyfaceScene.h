#pragma once
#include <Engine/Scene.h>

class KissyfaceScene : public Scene
{
public:
	KissyfaceScene();
	virtual ~KissyfaceScene();
	KissyfaceScene(const KissyfaceScene&) = delete;
	KissyfaceScene& operator=(const KissyfaceScene&) = delete;

	virtual void lateUpdate() override final;

	// Scene��(��) ���� ��ӵ�
	virtual Scene* Clone() override;
};

