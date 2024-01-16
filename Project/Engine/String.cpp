#include "pch.h"
#include "String.h"

namespace helper
{
	String::String()
	{
	}

	String::~String()
	{
	}

	//현재핵으로 하였음 추후에 정확히 사용법을 익힐것
	std::wstring String::StrToWStr(const std::string& str)
	{
		const int WSTR_LEN = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		std::wstring wstr(WSTR_LEN, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr.data(), WSTR_LEN);
		return wstr;
	}

	std::string String::WStrToStr(const std::wstring& wstr)
	{
		const int STR_LEN = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string str(STR_LEN, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, str.data(), STR_LEN, nullptr, nullptr);
		return str;
	}
	//핵핵핵

	std::wstring String::SplitFilePathExtension(const std::wstring& filePath)
	{
		constexpr UINT FILE_PATH_MAX_LEN = 512;
		wchar_t szExtension[FILE_PATH_MAX_LEN] = { 0, };

		errno_t err = _wsplitpath_s(filePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, FILE_PATH_MAX_LEN);
		(void)(err);

		Assert(!err, ASSERT_MSG("error file path"));

		return szExtension;
	}

	void String::SplitDirectoryPathAndFileName(const std::wstring& filePath,
		std::wstring* outDirectoryPath, std::wstring* outFileName)
	{
		Assert(outDirectoryPath, ASSERT_MSG_NULL);
		Assert(outFileName, ASSERT_MSG_NULL);

		std::wstring copyPath = filePath;
		std::wstring retDirectoryPath;
		std::wstring retFileName;

		retDirectoryPath.reserve(100);
		retFileName.reserve(100);

		int i = static_cast<int>(copyPath.length()) - 1;

		for (; i >= 0; --i)
		{
			if (L'\\' == filePath[i])
			{
				break;
			}

			retFileName += copyPath[i];
		}

		for (; i >= 0; --i)
		{
			retDirectoryPath += copyPath[i];
		}

		std::reverse(retFileName.begin(), retFileName.end());
		std::reverse(retDirectoryPath.begin(), retDirectoryPath.end());

		*outDirectoryPath = retDirectoryPath;
		*outFileName = retFileName;
	}

	void String::SplitRootNameAndFilePath(const std::wstring& filePath, 
		std::wstring* outRootName, std::wstring* outFilePath)
	{
		Assert(outRootName, ASSERT_MSG_NULL);
		Assert(outFilePath, ASSERT_MSG_NULL);

		constexpr UINT FILE_PATH_MAX_LEN = 512;
		int check = 0;

		std::wstring retRootName;
		std::wstring retFilePath;

		retRootName.reserve(FILE_PATH_MAX_LEN);
		retFilePath.reserve(FILE_PATH_MAX_LEN);

		int i = 0;

		for (; i < filePath.length(); ++i)
		{
			if (filePath[i] == L'\\')
			{
				++check;
			}
			if (2 == check)
			{
				break;
			}

			retRootName += filePath[i];
		}

		for (; i < filePath.length(); ++i)
		{
			retFilePath += filePath[i];
		}		

		//파일혼자남았다!
		if (retFilePath.empty())
		{
			retFilePath = retRootName;
			retRootName.clear();
		}

		*outRootName = retRootName;
		*outFilePath = retFilePath;
	}

	std::wstring String::SWPrintf(const wchar_t* const format, ...)
	{
		constexpr UINT STRING_MAX_LEN = 512;

		wchar_t szBuffer[STRING_MAX_LEN] = { 0, };

		va_list args;
		va_start(args, format);
		swprintf_s(szBuffer, STRING_MAX_LEN, format, args);
		va_end(args);

		return szBuffer;
	}
}