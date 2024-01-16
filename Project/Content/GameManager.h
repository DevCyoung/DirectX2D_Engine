#pragma once
#include <Engine/Singleton.h>
#include "PathInfo.h"
#include "RewindManager.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "EventManager.h"
#include "TimeController.h"

class GameObject;
class PathInfo;

class GameManager
{
public:
	static void initialize()
	{
		Assert(!sInstance, ASSERT_MSG_NOT_NULL);
		sInstance = new GameManager();
	}

	static void deleteInstance()
	{
		Assert(sInstance, ASSERT_MSG_NULL);
		delete sInstance;
		sInstance = nullptr;
	}

	static GameManager* GetInstance()
	{
		Assert(sInstance, ASSERT_MSG_NULL);
		return sInstance;
	}

	GameManager();
	virtual ~GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

public:
	void SetPlayer(GameObject* const player) { this->mPlayer = player; }
	void SetUITimer(GameObject* const uiTimer) { this->mUITimer = uiTimer; }
	//void SetPathInfo(PathInfo* const pathInfo) { this->mPathInfo = pathInfo; }

	GameObject* const GetUITimer() const { return mUITimer; }

	GameObject* const GetPlayer() const { return mPlayer; }
	
	PathInfo* const GetPathInfo() const { return mPathInfo; }

	RewindManager* const GetRewindManager() const { return mRewindManager; }	
	EffectManager* const GetEffectManager() const { return mEffectManager; }	
	EventManager* const GetEventManager() const { return mEventManager; }
	TimeController* const GetTimeController() const { return mTimeController; }

private:
	inline static GameManager* sInstance = nullptr;
	GameObject* mPlayer;
	GameObject* mUITimer;
	PathInfo* mPathInfo;

	RewindManager* mRewindManager;	
	EffectManager* mEffectManager;
	EventManager* mEventManager;
	TimeController* mTimeController;
};

#define gSoundManager SoundManager::GetInstance()
#define gRewindManager GameManager::GetInstance()->GetRewindManager()
#define gEffectManager GameManager::GetInstance()->GetEffectManager()
