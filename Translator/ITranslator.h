#include "stdafx.h"
#pragma once
#include "IDictionary.h"
#include "TranslationState.h"
#include "ITranslatorController.h"

namespace Dictionary
{
	class ITranslator
	{
	public:
		virtual ~ITranslator() {}
		virtual std::vector<std::wstring> translate(std::wstring word) = 0;
		virtual std::vector<std::wstring> find(std::wstring word, size_t max_distance) = 0;
		virtual TranslationState& getState() = 0;
		virtual void switchState() = 0;

		virtual void setController(ITranslatorController* controller) = 0;
	};
}