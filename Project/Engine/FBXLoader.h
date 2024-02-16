#pragma once
class Mesh;
class GameObject;
#include <FBXLoader/FBXLoadManager.h>

class FBXLoader
{
public:
	static void LoadFBX(const std::wstring& relativePath);
	static void CreateMeshFromFBX();
	static GameObject* FbxInstantiate(const std::wstring& relativePath);
};

