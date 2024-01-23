#pragma once
#include <Engine/Scene.h>

class DefaultScene : public Scene
{
	// Scene을(를) 통해 상속됨
	Scene* Clone() override;
};

