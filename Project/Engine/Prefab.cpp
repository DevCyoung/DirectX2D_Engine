#include "pch.h"
#include "Prefab.h"
#include "GameObject.h"

Prefab::Prefab(GameObject* gameObject)
	: mRoot(gameObject)
{
}

Prefab::~Prefab()
{
	DELETE_POINTER_NOT_NULL(mRoot);
}

HRESULT Prefab::Load(const std::wstring& filePath)
{
	(void)filePath;
	return E_NOTIMPL;
}
