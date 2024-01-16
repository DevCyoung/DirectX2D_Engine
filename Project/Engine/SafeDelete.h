#pragma once

#define DELETE_POINTER(p)		{ delete   p; p = nullptr; }
#define DELETE_ARRAY(p)			{ delete[] p; p = nullptr; }

#define DELETE_POINTER_NOT_NULL(p)  { Assert(p, ASSERT_MSG_NULL); DELETE_POINTER(p) }
#define DELETE_ARRAY_NOT_NULL(p)	{ Assert(p, ASSERT_MSG_NULL); DELETE_ARRAY(p) }

namespace mem
{
	template<typename T, UINT Size>
	void DeletePointerArrayElements(T* (* const pPointerArray)[Size])
	{
		for (auto& value : (*pPointerArray))
		{
			DELETE_POINTER(value);
		}
	}

	template<typename T>
	void DeleteMapElements(T* const pMap)
	{
		for (auto& value : (*pMap))
		{
			DELETE_POINTER(value.second);
		}

		pMap->clear();
	}

	template<typename T>
	void DeleteContainerElements(T* const pContainer)
	{
		for (auto& value : (*pContainer))
		{
			DELETE_POINTER(value);
		}

		pContainer->clear();
	}
}

namespace mem::del
{	
	template<typename T, UINT Size>
	void DeletePointerArrayElements(T* (*const pPointerArray)[Size])
	{		
		mem::DeletePointerArrayElements(pPointerArray);
	}	

	template<typename Pointer>
	void DeleteVectorElements(std::vector<Pointer>* const pVector)
	{
		mem::DeleteContainerElements(pVector);
	}

	template<typename Key, typename Pointer>
	void DeleteMapElements(std::map<Key, Pointer>* const map)
	{
		mem::DeleteMapElements(map);
	}

	template<typename Key, typename Pointer>
	void DeleteUnorderedMapElements(std::unordered_map<Key, Pointer>* const pUnorderedMap)
	{
		mem::DeleteMapElements(pUnorderedMap);
	}

	template<typename Pointer, UINT Size>
	void DeleteVectorArrayElements(std::vector<Pointer>(* const pVectorArray)[Size])
	{
		for (auto& value : (*pVectorArray))
		{
			DeleteVectorElements(&value);
		}
	}

	template<typename Key, typename Pointer, UINT Size>
	void DeleteMapArrayElements(std::map<Key, Pointer> (*const pMapArray)[Size])
	{
		for (auto& value : (*pMapArray))
		{
			DeleteMapElements(&value);
		}
	}

	template<typename Key, typename Pointer, UINT Size>
	void DeleteUnorderedMapArrayElements(std::unordered_map<Key, Pointer> (*const pUnorderedMapArray)[Size])
	{		
		for (auto& value : (*pUnorderedMapArray))
		{
			DeleteUnorderedMapElements(&value);
		}
	}
}
