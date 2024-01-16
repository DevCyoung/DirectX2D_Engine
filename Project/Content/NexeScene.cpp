#include "pch.h"
#include "NexeScene.h"
#include "Components.h"
#include "GameManager.h"
#include "KatanaScene.h"
#include "KatanaZeroSystem.h"

#include "TitleScene.h"
#include "Chinatown01Scene.h"
#include "Chinatown04Scene.h"
#include "Chinatown05Scene.h"
#include "KissyfaceScene.h"
#include "HeadHunterScene.h"

NexeScene::NexeScene()
	: ScriptComponent(eScriptComponentType::NexeScene)
	, mSceneState(eNextSceneState::None)
{
}

NexeScene::~NexeScene()
{
}

void NexeScene::initialize()
{
	//KatanaZeroSystem::GetInstance()->SetNextEffect(GetOwner());
	//FadeOut();
}

void NexeScene::FadeIn()
{
	SpriteRenderer* spriteRenderer = GetOwner()->GetComponent<SpriteRenderer>();

	float scale = spriteRenderer->GetSprite2DInfo().A;

	mSceneState = eNextSceneState::EnterScene;
	gSoundManager->Play(eResAudioClip::TransitionEnd, 0.3f);
	scale = 0.0f;

	spriteRenderer->SetColorA(scale);
}

void NexeScene::FadeOut(eKatanaSceneType nextSceneType)
{
	SpriteRenderer* spriteRenderer = GetOwner()->GetComponent<SpriteRenderer>();

	float scale = spriteRenderer->GetSprite2DInfo().A;

	mSceneState = eNextSceneState::NextScene;

	gSoundManager->Play(eResAudioClip::TransitionBegin, 0.3f);
	scale = 1.0f;

	spriteRenderer->SetColorA(scale);

	mNextSceneType = nextSceneType;
}

void NexeScene::LoadNextScene(eKatanaSceneType sceneType)
{
	switch (sceneType)
	{	
	case eKatanaSceneType::Title:
		SceneManager::GetInstance()->RegisterLoadScene(new TitleScene());
		break;
	case eKatanaSceneType::ChinaTown01:
		SceneManager::GetInstance()->RegisterLoadScene(new Chinatown01Scene());
		break;
	case eKatanaSceneType::ChinaTown04:		
		SceneManager::GetInstance()->RegisterLoadScene(new Chinatown04Scene());
		break;
	case eKatanaSceneType::ChinaTown05:		
		SceneManager::GetInstance()->RegisterLoadScene(new Chinatown05Scene());
		break;
	case eKatanaSceneType::Kissyface:
		SceneManager::GetInstance()->RegisterLoadScene(new KissyfaceScene);
		break;
	case eKatanaSceneType::HeadHunter:
		SceneManager::GetInstance()->RegisterLoadScene(new HeadHunterScene);
		break;
	default:
		Assert(false, ASSERT_MSG_INVALID);
		break;
	}
}


void NexeScene::update()
{

	SpriteRenderer* spriteRenderer = GetOwner()->GetComponent<SpriteRenderer>();

	


	if (gInput->GetKeyDown(eKeyCode::P))
	{
		//FadeOut();
		/*
				KatanaScene* katanaScene = gKatanaZeroSystem->GetCurrentScene();
				if (katanaScene->IsClear())
				{
					gKatanaZeroSystem->LoadNextScene();
				}	*/

		KatanaScene* katanaScene = gKatanaZeroSystem->GetCurrentScene();
		gKatanaZeroSystem->LoadNextScene();

		if (katanaScene->IsClear())
		{
			
		}
	}

	float scale = spriteRenderer->GetSprite2DInfo().A;
	float _small = spriteRenderer->GetSprite2DInfo().B;

	switch (mSceneState)
	{
	case eNextSceneState::None:
		scale = 1.0f;
		break;
	case eNextSceneState::NextScene:
		scale -= gDeltaTime * 3.2f;

		if (scale < -1.f)
		{
			LoadNextScene(mNextSceneType);
			mSceneState = eNextSceneState::None;
		}

		break;
	case eNextSceneState::EnterScene:
		scale += gDeltaTime * 3.2f;
		break;
	default:
		break;
	}

	

	/*if (gInput->GetKeyDown(eKeyCode::J))
	{
		mNextSceneState = eNextSceneState::NextScene;
		gSoundManager->Play(eResAudioClip::TransitionEnd, 0.3f);
		scale = 0.0f;
	}

	if (gInput->GetKeyDown(eKeyCode::K))
	{
		mNextSceneState = eNextSceneState::EnterScene;
		gSoundManager->Play(eResAudioClip::TransitionBegin, 0.3f);
		scale = 1.0f;
	}
*/


	spriteRenderer->SetColorB(_small);
	spriteRenderer->SetColorA(scale);
}

void NexeScene::lateUpdate()
{
}
