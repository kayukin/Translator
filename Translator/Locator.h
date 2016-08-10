#include "stdafx.h"
#pragma once

#include "ILanguageDetector.h"
#include "RegexpLanguageDetector.h"

#include "RegistrySettings.h"

#include "ITranslatorController.h" 
#include "TranslatorController.h"

#include "IDictionary.h"
#include "Dictionary.h"

#include "ITranslator.h"
#include "Translator.h"

namespace Dictionary
{
	class Locator
	{
		std::shared_ptr<ILanguageDetector> lang_detector;
		std::shared_ptr<ISettingsLoader> settings_loader;
	public:
		static Locator& Instance()
		{ 
			static Locator inst;
			return inst;
		}

		std::shared_ptr<ILanguageDetector> getLanguageDetector(){ return lang_detector; }
		std::shared_ptr<ISettingsLoader> getSettingsLoader(){ return settings_loader; }
		std::shared_ptr<ITranslatorController> createTranslatorController(){ return std::shared_ptr<ITranslatorController>(new TranslatorController(settings_loader)); }

		std::shared_ptr<IDictionary> getDictionary(Language& from, Language& to){ return std::shared_ptr<IDictionary>(new Dictionary(from, to)); }
		std::shared_ptr<ITranslator> createTranslator(std::shared_ptr<IDictionary>& first, std::shared_ptr<IDictionary>& second, TranslationState state){ return std::shared_ptr<ITranslator>(new Translator(first, second, state, lang_detector)); }
	private:
		Locator()
		{
			lang_detector = std::shared_ptr<ILanguageDetector>(new RegexpLanguageDetector());
			settings_loader = std::shared_ptr<ISettingsLoader>(new RegistrySettingsLoader());
		}
		~Locator(){}
		Locator(Locator const&) = delete;
		Locator& operator= (Locator const&) = delete;	
	};
}