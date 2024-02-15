#include "pch.h"
#include "Resource.h"
#include "EnumResource.h"

Resource::Resource()	
	: mRelativePath(L"")
	, mResourceType(eResourceType::End)
{
}

Resource::Resource(eResourceType mResourceType)
	: mRelativePath(L"")
	, mResourceType(mResourceType)

{
}

Resource::~Resource()
{
}
