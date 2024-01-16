#include "pch.h"
#include "SceneManager.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
SceneManager::SceneManager()
	: mCurrentScene(nullptr)
	, mNextScene(nullptr)
{	
}

SceneManager::~SceneManager()
{
	DELETE_POINTER(mCurrentScene);
}

void SceneManager::LoadScene(Scene* const scene)
{
	//Assert(scene, WCHAR_IS_NULLPTR);
	DELETE_POINTER(sInstance->mCurrentScene);

	mCurrentScene = scene;
	scene->initialize();
}

void SceneManager::RegisterLoadScene(Scene* const scene)
{
	Assert(scene, ASSERT_MSG_NULL);
	Assert(!mNextScene, ASSERT_MSG_NOT_NULL);

	mNextScene = scene;
}

void SceneManager::update()
{
	mCurrentScene->update();
}

void SceneManager::lateUpdate()
{
	mCurrentScene->fixedUpdate();

	mCurrentScene->lateUpdate();	
}

void SceneManager::eventUpdate()
{
	mCurrentScene->eventUpdate();

	//scene chagne
	if (nullptr != mNextScene)
	{
		LoadScene(mNextScene);
		mNextScene = nullptr;
	}
}

void SceneManager::render(const UINT renderTargetWidth,
	const UINT renderTargetHeight,
	ID3D11RenderTargetView** const ppRenderTargetView,
	ID3D11DepthStencilView* const depthStencilView)
{
	const Vector4& color = mCurrentScene->GetBackgroundColor();

	const FLOAT backgroundColor[4] = { color.x, color.y, color.z, color.w };

	gGraphicDevice->ClearRenderTarget(ppRenderTargetView,
		depthStencilView,
		backgroundColor);

	mCurrentScene->render(renderTargetWidth,
		renderTargetHeight,		
		ppRenderTargetView,
		depthStencilView);

	mCurrentScene->renderFlush();
}
