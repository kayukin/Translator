#include "stdafx.h"
#pragma once
#include "TranslationState.h"

namespace Dictionary
{
	class ITranslatorController
	{
	public:
		virtual void onStateChange() = 0;
		virtual std::vector<std::wstring> translate(std::wstring word) = 0;
		virtual std::vector<std::wstring> find(std::wstring word, size_t max_distance) = 0;
		virtual TranslationState& getState() = 0;
		virtual void switchState() = 0;
	};
}