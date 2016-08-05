#include "stdafx.h"
#pragma once
#include "Language.h"

namespace Dictionary
{
	class ILanguageDetector
	{
	public:
		virtual Language detectLanguage(std::wstring word) = 0;
	};
}