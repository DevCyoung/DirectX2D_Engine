#pragma once
#include "DefineMacro.h"

#define SINGLETON_DECLARE(CLASSNAME)						\
private:													\
	static void initialize()								\
	{														\
		Assert(!sInstance, ASSERT_MSG_NOT_NULL);			\
		sInstance = new CLASSNAME();						\
	}														\
static void deleteInstance()								\
	{														\
		Assert(sInstance, ASSERT_MSG_NULL);				\
		delete sInstance;									\
		sInstance = nullptr;								\
	}														\
public:														\
	static CLASSNAME* GetInstance()							\
	{														\
		Assert(sInstance, ASSERT_MSG_NULL);				\
		return sInstance;									\
	}														\
private:													\
	CLASSNAME();											\
	virtual ~CLASSNAME();									\
	CLASSNAME(const CLASSNAME&) = delete;					\
	CLASSNAME& operator=(const CLASSNAME&) = delete;		\
private:													\
	inline static CLASSNAME* sInstance = nullptr;			\
