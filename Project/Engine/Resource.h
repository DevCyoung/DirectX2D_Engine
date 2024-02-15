#pragma once

enum class eResourceType;

class Resource
{
	friend class ResourceManager;
public:
	Resource();
	Resource(eResourceType mResourceType);
	virtual ~Resource();

	virtual HRESULT Load(const std::wstring& filePath) = 0;

	const std::wstring& GetRelativePath() const { return mRelativePath; }

	eResourceType GetType() { return mResourceType; }

private:
	eResourceType mResourceType;
	std::wstring mRelativePath;
};