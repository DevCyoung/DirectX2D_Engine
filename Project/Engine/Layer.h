#pragma once
class GameObject;

class Layer
{
	friend class Scene;

public:
	const std::vector<GameObject*>& GetGameObjects() const { return mGameObjects; }
	std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }

private:
	Layer();
	virtual ~Layer();
	Layer(const Layer&) = delete;
	Layer& operator=(const Layer&) = delete;

	

private:
	void initialize();
	void update();
	void fixedUpdate();
	void lateUpdate();
	void lastUpdate();

private:
	std::vector<GameObject*> mGameObjects;
};
