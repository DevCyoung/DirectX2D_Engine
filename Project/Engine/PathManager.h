#pragma once
#include "Singleton.h"

class PathManager
{
	friend class Engine;
	SINGLETON_DECLARE(PathManager);

public:
	LPCWSTR	GetResourcePath() const { return mResourcePath; }

private: 
	WCHAR	mResourcePath[MAX_PATH];
};

#define gPathManager PathManager::GetInstance()
