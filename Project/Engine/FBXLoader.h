#pragma once
class Mesh;

#include <FBXLoader/FBXLoadManager.h>

class FBXLoader
{
public:
	static void LoadFBX(const std::wstring& relativePath);
	static void CreateMeshFromFBX();
};

