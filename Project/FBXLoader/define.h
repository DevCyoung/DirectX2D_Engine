#pragma once
#define ASSERT_MSG_SWITCH_DEFAULT "switch default"
#define ASSERT_MSG_NULL "value is nullptr"
#define ASSERT_MSG_NOT_NULL "value is not nullptr"
#define ASSERT_MSG_INVALID "value is invalid"

#define L_PREFIX(quote) L##quote
#define ASSERT_MSG(message) message

#define Assert(expression, message) assert(expression && L_PREFIX(message))
#define Static_Assert(expression, message) static_assert(expression, message)

#define FIXME(message) MessageBox(nullptr, L_PREFIX(message), L_PREFIX(message), MB_OK | MB_ICONWARNING)

#define CLONE(type) public: virtual type* Clone() { return new type(*this); }
#define CLONE_DISABLE(type) public: virtual type* Clone() { return nullptr; assert(nullptr); }

#define PUBLIC_SINGLETON_DECLARE(CLASSNAME)						\
public:													\
	static void Initialize()								\
	{														\
		Assert(!sInstance, ASSERT_MSG_NOT_NULL);			\
		sInstance = new CLASSNAME();						\
	}														\
static void DeleteInstance()								\
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
