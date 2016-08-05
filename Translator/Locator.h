#include "stdafx.h"
#pragma once
#include "ILanguageDetector.h"
#include "RegexpLanguageDetector.h"
#include "RegistrySettings.h"

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