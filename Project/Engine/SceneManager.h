#include "Singleton.h"
#include "Scene.h"

struct ID3D11DepthStencilView;
struct ID3D11RenderTargetView;

class SceneManager
{
	friend class Engine;
	SINGLETON_DECLARE(SceneManager);

public:
	void LoadScene(Scene* const scene);
	Scene* GetCurrentScene() const { Assert(mCurrentScene, WCHAR_IS_NULLPTR); return mCurrentScene; }

public:
	void Initialize(Scene* const scene) const
	{
		scene->initialize();
	}

	void Update(Scene* const scene) const
	{
		scene->update();
	}

	void LateUpdate(Scene* const scene) const
	{
		scene->lateUpdate();
	}


	void Render(Scene* const scene,
		const UINT renderTargetWidth,
		const UINT renderTargetHeight,
		ID3D11RenderTargetView**
		const ppRenderTargetView,
		ID3D11DepthStencilView* const depthStencilView) const
	{
		scene->render(renderTargetWidth,
			renderTargetHeight,
			ppRenderTargetView,
			depthStencilView);
	}

	void EventUpdate(Scene* const scene) const
	{
		scene->eventUpdate();
	}

	void RenderFlush(Scene* const scene) const
	{
		scene->renderFlush();
	}

	void RegisterLoadScene(Scene* const scene);


private:
	void update();
	void lateUpdate();
	void lastUpdate();

	void eventUpdate();
	void render(const UINT renderTargetWidth,
		const UINT renderTargetHeight,
		ID3D11RenderTargetView** const ppRenderTargetView,
		ID3D11DepthStencilView* const depthStencilView);

private:
	Scene* mCurrentScene;
	Scene* mNextScene;
};

#define gCurrentScene SceneManager::GetInstance()->GetCurrentScene()
