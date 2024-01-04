#pragma once
#include <Engine/Scene.h>

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();
	TestScene(const TestScene&) = delete;
	TestScene& operator=(const TestScene&) = delete;

	// Scene을(를) 통해 상속됨
	Scene* Clone() override;
};

