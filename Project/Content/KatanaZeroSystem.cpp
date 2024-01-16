#include "pch.h"
#include "KatanaZeroSystem.h"
#include "GameManager.h"
#include <Engine/SceneManager.h>
#include "NexeScene.h"

#include "Chinatown01Scene.h"
#include "Chinatown04Scene.h"
#include "Chinatown05Scene.h"
#include "KissyfaceScene.h"
#include "HeadHunterScene.h"

KatanaZeroSystem::KatanaZeroSystem()
	: mCurrentSceneType(eKatanaSceneType::None)
	, mNextEffect(nullptr)
	, mMainCamera(nullptr)
	, mSystemState(eKatanaSystemState::None)
	, mCRTEffect(nullptr)
	, mCRTText(nullptr)
	, mCRTTextTime(nullptr)
	, mCRTTimeLine(nullptr)
	, mCRTReadyText(nullptr)
	, mCRTBlackOut(nullptr)
	, mbPlayerDamaged(true)
{
}

KatanaZeroSystem::~KatanaZeroSystem()
{
}

void KatanaZeroSystem::SetCurentScene(KatanaScene* const katanaScene)
{
	Assert(katanaScene, ASSERT_MSG_NULL);

	eKatanaSceneType nextType = katanaScene->GetKatanaSceneType();

	if (eKatanaSceneType::None == mCurrentSceneType ||
		nextType != mCurrentSceneType)
	{
		mCurrentSceneType = nextType;
		EnterScene(mCurrentSceneType);
	}
}

KatanaScene* KatanaZeroSystem::GetCurrentScene() const
{
	Scene* scene = SceneManager::GetInstance()->GetCurrentScene();
	Assert(scene, ASSERT_MSG_NULL);

	KatanaScene* katanaScene = dynamic_cast<KatanaScene*>(scene);
	Assert(katanaScene, ASSERT_MSG_NULL);

	return katanaScene;
}

void KatanaZeroSystem::TurnOnCRT()
{
	mCRTEffect->GetComponent<SpriteRenderer>()->TurnOnVisiblelity();	
}

void KatanaZeroSystem::TurnOffCRT()
{
}

void KatanaZeroSystem::PlayCRT()
{
	mCRTEffect->GetComponent<SpriteRenderer>()->SetColorR(1.f);
}

void KatanaZeroSystem::RewindCRT()
{
	mCRTEffect->GetComponent<SpriteRenderer>()->SetColorR(-1.f);
}

void KatanaZeroSystem::PauseCRT()
{
	mCRTEffect->GetComponent<SpriteRenderer>()->SetColorR(0.f);
}

void KatanaZeroSystem::SetCRTText(const std::wstring& text)
{
	mCRTText->GetComponent<EngineText>()->SetPosition(XMUINT2(170, 100));
	mCRTText->GetComponent<EngineText>()->SetScale(50.f);
	mCRTText->GetComponent<EngineText>()->SetText(text);
}

void KatanaZeroSystem::SetCRTTextTime(const std::wstring& text)
{
	mCRTTextTime->GetComponent<EngineText>()->SetPosition(XMUINT2(790, 610));
	mCRTTextTime->GetComponent<EngineText>()->SetScale(40.f);
	mCRTTextTime->GetComponent<EngineText>()->SetText(text);

	mCRTTimeLine->GetComponent<EngineText>()->SetPosition(XMUINT2(200, 530));
	mCRTTimeLine->GetComponent<EngineText>()->SetScale(50.f);
	//mCRTTimeLine->GetComponent<EngineText>()->SetText(L"B - - - - - + - - - - - + - - - - - + - - - - - E");
	mCRTTimeLine->GetComponent<EngineText>()->SetText(L"B - - - - - - - - - - - - - - - - - - - - - - - - E");
}

void KatanaZeroSystem::SetCRTTimeLine(float time)
{
	//Start 240 1025
	int start = 238;
	int end = 1022;
	int interver = 34;

	if (time < 0.f)
	{
		time = 0.f;
	}
	else if (time > 1.f)
	{
		time = 1.f;
	}

	int current = static_cast<int>((end - start) * time);	
	current = (current / interver) * interver + start;	

	mCRTTimeLineBar->GetComponent<EngineText>()->SetScale(42.f);
	mCRTTimeLineBar->GetComponent<EngineText>()->SetText(L"▋");
	mCRTTimeLineBar->GetComponent<EngineText>()->SetPosition(XMUINT2(current, 535));
}


void KatanaZeroSystem::LoadNextScene()
{
	gSoundManager->TurnOnSound();

	switch (mCurrentSceneType)
	{
	case eKatanaSceneType::None:
		break;
	case eKatanaSceneType::Title:		
		SceneManager::GetInstance()->RegisterLoadScene(new Chinatown01Scene());
		break;
	case eKatanaSceneType::ChinaTown01:
		mNextEffect->GetComponent<NexeScene>()->FadeOut(eKatanaSceneType::ChinaTown04);
		break;
	case eKatanaSceneType::ChinaTown04:
		mNextEffect->GetComponent<NexeScene>()->FadeOut(eKatanaSceneType::ChinaTown05);
		//SceneManager::GetInstance()->RegisterLoadScene(new Chinatown05Scene());
		break;
	case eKatanaSceneType::ChinaTown05:
		mNextEffect->GetComponent<NexeScene>()->FadeOut(eKatanaSceneType::HeadHunter);
		//SceneManager::GetInstance()->RegisterLoadScene(new Chinatown01Scene());
		break;
	case eKatanaSceneType::HeadHunter:		
		mNextEffect->GetComponent<NexeScene>()->FadeOut(eKatanaSceneType::Title);
		break;
	case eKatanaSceneType::Kissyface:
		//SceneManager::GetInstance()->RegisterLoadScene(new Chinatown01Scene());
		break;
	default:
		break;
	}

}

void KatanaZeroSystem::playBackGroundBGM(const eKatanaSceneType type)
{
	switch (type)
	{
	case eKatanaSceneType::Title:
		gSoundManager->PlayBackGround(eResAudioClip::song_rainonbrick, 0.2f);
		break;
	case eKatanaSceneType::ChinaTown01:
		gSoundManager->PlayBackGround(eResAudioClip::song_chinatown, 0.2f);
		break;
	case eKatanaSceneType::HeadHunter:
		gSoundManager->PlayBackGround(eResAudioClip::song_fullconfession, 0.2f);
		break;
	case eKatanaSceneType::Kissyface:
		gSoundManager->PlayBackGround(eResAudioClip::song_bossbattle, 0.2f);
		break;
	default:
		//Assert(false, WCHAR_IS_INVALID_TYPE);
		break;
	}
}

void KatanaZeroSystem::Rewind()
{
	RewindManager* rewindManager = GameManager::GetInstance()->GetRewindManager();

	rewindManager->Rewind();	
}

void KatanaZeroSystem::CCTVPlay()
{
	//RewindManager* rewindManager = GameManager::GetInstance()->GetRewindManager();
	
	//rewindManager->CCTVPlay();
	//mCRTEffect->GetComponent<SpriteRenderer>()->TurnOnVisiblelity();
}

void KatanaZeroSystem::CCTVPlayBack()
{
	//RewindManager* rewindManager = GameManager::GetInstance()->GetRewindManager();

}

void KatanaZeroSystem::GameClear()
{
	GameManager::GetInstance()->GetRewindManager()->GameClear();
}


void KatanaZeroSystem::EnterScene(const eKatanaSceneType nextSceneType)
{
	playBackGroundBGM(nextSceneType);

	switch (nextSceneType)
	{
	case eKatanaSceneType::None:
		break;
	case eKatanaSceneType::Title:
		break;
	case eKatanaSceneType::ChinaTown01:
		mNextEffect->GetComponent<NexeScene>()->FadeIn();
		break;
	case eKatanaSceneType::ChinaTown04:
		mNextEffect->GetComponent<NexeScene>()->FadeIn();
		break;
	case eKatanaSceneType::ChinaTown05:
		mNextEffect->GetComponent<NexeScene>()->FadeIn();
		break;
	case eKatanaSceneType::HeadHunter:
		mNextEffect->GetComponent<NexeScene>()->FadeIn();
		break;
	case eKatanaSceneType::Kissyface:
		mNextEffect->GetComponent<NexeScene>()->FadeIn();
		break;
	default:
		break;
	}
}