#include "stdafx.h"
#pragma once
#include "ILanguageDetector.h"
#include <regex>

namespace Dictionary
{
	class RegexpLanguageDetector : public ILanguageDetector
	{
	public:
		Language detectLanguage(std::wstring word) override
		{
			std::wregex rus_word(L"[À-ß¨à-ÿ¸]*[à-ÿ¸ -]+");
			std::wregex eng_word(L"[A-Za-z]*[a-z' -]+");
			if (std::regex_search(word, rus_word))
			{
				return Languages::RUSSIAN;
			}
			else if (std::regex_search(word, eng_word))
			{
				return Languages::ENGLISH;
			}
			throw UnknownLanguage();
		}
	};
}