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
		virtual std::vector<std::wstring> translate(const std::wstring& word) = 0;
		virtual std::vector<std::wstring> find(const std::wstring& word, size_t max_distance) = 0;
		virtual std::vector<std::wstring> find_by_prefix(const std::wstring& prefix) = 0;
		virtual TranslationState& getState() = 0;
		virtual void switchState() = 0;
	};
}