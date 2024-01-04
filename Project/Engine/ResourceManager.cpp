#include "pch.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (Dictionary& item : mResources)
	{
		memory::safe::DeleteUnorderedMap(item);
	}
}

const ResourceManager::Dictionary& ResourceManager::GetDictionary(const eResourceType type)
{
	return mResources[static_cast<UINT>(type)];
}
