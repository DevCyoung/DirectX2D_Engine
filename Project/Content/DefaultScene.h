#pragma once
#include <Engine/Scene.h>

class DefaultScene : public Scene
{
	// Scene��(��) ���� ��ӵ�
	Scene* Clone() override;
};

