#include "pch.h"
#include "PathManager.h"

namespace engine
{
	PathManager::PathManager()
		: mResourcePath{0,}
	{
		GetCurrentDirectory(256, mResourcePath);

		// ���������� ��
		const int PATH_LEN = static_cast<int>(wcslen(mResourcePath));

		for (int i = PATH_LEN - 1; i >= 0; --i)
		{
			if (L'\\' == mResourcePath[i])
			{
				mResourcePath[i] = 0;
				break;
			}
		}

		wcscat_s(mResourcePath, L"\\bin\\Resources");
	}

	PathManager::~PathManager()
	{
	}
}