﻿#pragma once

namespace engine
{
	enum class eResMaterial
	{
		dummy,
		End
	};

	const wchar_t* EnumResourcePath(eResMaterial type);
}//namespace engine End
