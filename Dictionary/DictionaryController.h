#include "stdafx.h"
#pragma once
#include "dllspec.h"
#include "RuEngDictionary.h"
#include "IDictionaryController.h"
#include <functional>
#include <regex>

namespace Dictionary
{
	template class DICTIONARY_API std::function<void(void)>;
	class DICTIONARY_API DictionaryController :public IDictionaryController
	{
		std::shared_ptr<IDictionary> dict;
		TranslateDirection direction;
		std::function<void(void)> sw_callback;
	public:
		DictionaryController(std::shared_ptr<IDictionary> _dict, std::function<void(void)> _sw_callback = nullptr, TranslateDirection _direction = ENG_TO_RUS) :dict(_dict), direction(_direction), sw_callback(_sw_callback){}
		void switchDirection() override;
		std::wstring getDirectionText() override;
		std::shared_ptr<IDictionary> getDictionary() override;
		TranslateDirection getDirection() override;
		void detectDirection(std::wstring word) override;
	};
}