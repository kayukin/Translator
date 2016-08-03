#include "stdafx.h"
#include "DictionaryController.h"

namespace Dictionary
{
	void DictionaryController::switchDirection()
	{
		if (direction == TranslateDirection::ENG_TO_RUS)
		{
			direction = TranslateDirection::RUS_TO_ENG;
		}
		else
		{
			direction = TranslateDirection::ENG_TO_RUS;
		}
		if (sw_callback)
		{
			sw_callback();
		}
	}



	std::wstring DictionaryController::getDirectionText()
	{
		if (direction == TranslateDirection::ENG_TO_RUS)
		{
			return L"ENG->RUS";
		}
		else
		{
			return L"RUS->ENG";
		}
	}

	std::shared_ptr<IDictionary> DictionaryController::getDictionary()
	{
		return dict;
	}
	TranslateDirection DictionaryController::getDirection()
	{
		return direction;
	}

	void DictionaryController::detectDirection(std::wstring word)
	{
		std::wregex rus_word(L"[À-ß¨à-ÿ¸][à-ÿ¸ -]+");
		std::wregex eng_word(L"[A-Za-z][a-z' -]+");
		TranslateDirection detected;
		if (std::regex_match(word, rus_word))
		{
			detected = TranslateDirection::RUS_TO_ENG;
		}
		else if (std::regex_match(word, eng_word))
		{
			detected = TranslateDirection::ENG_TO_RUS;
		}
		else
		{
			//throw exception;
		}
		if (detected != direction)
		{
			switchDirection();
		}
	}
}