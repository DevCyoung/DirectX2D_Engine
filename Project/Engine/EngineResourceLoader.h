#pragma once

class EngineResourceLoader
{
	friend class Engine;

private:
	EngineResourceLoader() = default;
	~EngineResourceLoader() = default;
	EngineResourceLoader(const EngineResourceLoader&) = delete;
	EngineResourceLoader& operator=(const EngineResourceLoader&) = delete;

	static void loadResource();

	static void loadShader();
	static void loadMesh();
};

