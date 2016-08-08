#include "stdafx.h"
#include "Language.h"

namespace Dictionary
{
	Language Languages::getByName(const std::wstring& name)
	{
		if (RUSSIAN.getName() == name)
		{
			return RUSSIAN;
		}
		if (ENGLISH.getName() == name)
		{
			return ENGLISH;
		}
		return UNKNOWN;
	}

	const Language Languages::RUSSIAN(L"Russian");
	const Language Languages::ENGLISH(L"English");
	const Language Languages::UNKNOWN(L"Unknown");
}