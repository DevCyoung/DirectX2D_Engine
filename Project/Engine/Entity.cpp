#include "pch.h"
#include "Entity.h"

Entity::Entity()
	: mName(L"None")
	, mID(sID++)
{
}

Entity::~Entity()
{
}
