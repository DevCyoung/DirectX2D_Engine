#include "pch.h"
#include "Prefab.h"
#include "GameObject.h"

Prefab::Prefab(GameObject* gameObject)
	: mRoot(gameObject)
{
}

Prefab::~Prefab()
{
	SAFE_DELETE_POINTER(mRoot);
}

HRESULT Prefab::Load(const std::wstring& filePath)
{
	(void)filePath;
	return E_NOTIMPL;
}
