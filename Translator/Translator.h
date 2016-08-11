#include "stdafx.h"
#pragma once
#include "Dictionary.h"
#include "ITranslator.h"
#include "ILanguageDetector.h"

#include <functional>


namespace Dictionary
{

	class Translator :public ITranslator
	{
		std::shared_ptr<IDictionary> m_first;
		std::shared_ptr<IDictionary> m_second;

		std::shared_ptr<ILanguageDetector> m_lang_detector;
		std::shared_ptr<TranslationState> m_state;

		std::weak_ptr<ITranslatorController> m_controller;

		bool isSupported(const Language& lang)const;
	public:
		Translator(const std::shared_ptr<IDictionary>& first,const std::shared_ptr<IDictionary>& second, TranslationState state, 
			std::shared_ptr<ILanguageDetector> lang_detector);
		TranslationState& getState() override;

		std::vector<std::wstring> translate(const std::wstring& word) override;
		std::vector<std::wstring> find(const std::wstring& word, size_t max_distance) override;
		std::vector<std::wstring> find_by_prefix(const std::wstring& prefix) override;
		void switchState() override;

		void setController(std::shared_ptr<ITranslatorController> controller) override;
	};
}