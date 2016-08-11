#include "stdafx.h"
#pragma once
#include "TranslationState.h"
#include "IView.h"

namespace Dictionary
{
	class ITranslatorController
	{
	public:
		virtual ~ITranslatorController(){}
		virtual void onStateChange() = 0;
		virtual std::vector<std::wstring> translate(const std::wstring& word) = 0;
		virtual std::vector<std::wstring> find(const std::wstring& word, size_t max_distance) = 0;
		virtual std::vector <std::wstring> find_by_prefix(const std::wstring& prefix) = 0;
		virtual TranslationState getState() = 0;
		virtual void switchState() = 0;
		virtual void createTranslator() = 0;
		virtual void setView(std::shared_ptr<IView> view) = 0;
		virtual void loadDict(const std::wstring& filename) = 0;
		virtual void setAutoDetect(bool val) = 0;
	};
}