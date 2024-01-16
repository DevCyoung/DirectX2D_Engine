#include "pch.h"
#include "GameManager.h"
#include <Engine/GameObject.h>
#include "Components.h"
#include <Engine/GameObject.h>

GameManager::GameManager()
	: mPlayer(nullptr)
	, mUITimer(nullptr)
	, mPathInfo(nullptr)
	, mRewindManager(nullptr)	
	, mEffectManager(nullptr)
	, mEventManager(nullptr)
	, mTimeController(nullptr)

{		
	mPathInfo = new PathInfo();
	mRewindManager = new RewindManager();	
	mEffectManager = new EffectManager();	
	mEventManager = new EventManager();
	mTimeController = new TimeController();
}

GameManager::~GameManager()
{
	DELETE_POINTER_NOT_NULL(mPathInfo);
	DELETE_POINTER_NOT_NULL(mRewindManager);	
	DELETE_POINTER_NOT_NULL(mEffectManager);
	DELETE_POINTER_NOT_NULL(mEventManager);
	DELETE_POINTER_NOT_NULL(mTimeController);
}
