#pragma once

#define SAFE_DELETE_POINTER(p)  { Assert(p, ASSERT_MSG_NULL); delete   p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p)	{ Assert(p, ASSERT_MSG_NULL); delete[] p; p = nullptr; }

#define DELETE_POINTER(p)		{ delete   p; p = nullptr; }
#define DELETE_ARRAY(p)			{ delete[] p; p = nullptr; }

namespace memory::safe
{
	template<typename T, UINT Size>
	void DeleteArray(T* (&arr)[Size])
	{
		for (UINT i = 0; i < Size; ++i)
		{
			SAFE_DELETE_POINTER(arr[i]);
		}
	}

	template<typename Pointer>
	void DeleteVec(std::vector<Pointer>& vector)
	{
		for (size_t i = 0; i < vector.size(); ++i)
		{
			SAFE_DELETE_POINTER(vector[i]);
		}

		vector.clear();
	}

	template<typename Key, typename Pointer>
	void DeleteUnorderedMap(std::unordered_map<Key, Pointer>& unordered_map)
	{
		for (auto& value : unordered_map)
		{
			SAFE_DELETE_POINTER(value.second);
		}

		unordered_map.clear();
	}
}

namespace memory::unsafe
{
	template<typename T, UINT Size>
	void DeleteArray(T* (&arr)[Size])
	{
		for (UINT i = 0; i < Size; ++i)
		{
			DELETE_POINTER(arr[i]);
		}
	}

	template<typename T>
	void DeleteVec(std::vector<T>& vector)
	{
		for (size_t i = 0; i < vector.size(); ++i)
		{
			DELETE_POINTER(vector[i]);
		}

		vector.clear();
	}

	template<typename Key, typename T>
	void DeleteUnorderedMap(std::unordered_map<Key, T>& unordered_map)
	{
		for (auto& value : unordered_map)
		{
			DELETE_POINTER(value.second);
		}

		unordered_map.clear();
	}
}
