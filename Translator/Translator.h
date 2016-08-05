#include "stdafx.h"
#pragma once
#include "Dictionary.h"
#include "ITranslator.h"
#include "ILanguageDetector.h"
#include "Locator.h"

#include <functional>


namespace Dictionary
{

	class Translator :public ITranslator
	{
		std::shared_ptr<IDictionary> m_first;
		std::shared_ptr<IDictionary> m_second;

		std::shared_ptr<ILanguageDetector> m_lang_detector = Locator::Instance().getLanguageDetector();
		std::shared_ptr<TranslationState> m_state;

		ITranslatorController* m_controller;

		bool isSupported(const Language& lang)const;
	public:
		Translator(std::shared_ptr<IDictionary> first, std::shared_ptr<IDictionary> second, TranslationState state);
		TranslationState& getState() override;

		std::vector<std::wstring> translate(std::wstring word) override;
		std::vector<std::wstring> find(std::wstring word, size_t max_distance) override;
		void switchState() override;

		void setController(ITranslatorController* controller) override;
	};
}