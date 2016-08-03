#include "stdafx.h"
#pragma once
#include "IDictionary.h"

namespace Dictionary
{
	class ISettings
	{
	public:
		virtual TranslateDirection load() = 0;
		virtual void save(TranslateDirection) = 0;
	};
}