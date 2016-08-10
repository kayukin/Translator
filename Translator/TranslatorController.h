#include "stdafx.h"
#pragma once
#include "ITranslatorController.h"
#include "TranslatorFactory.h"
#include "Settings.h"

namespace Dictionary
{
	class TranslatorController : public ITranslatorController
	{
		std::shared_ptr<ITranslator> m_translator;
		std::shared_ptr<ISettingsLoader> m_settings_loader;
		std::wstring m_dict_filename;
		std::weak_ptr<IView> m_view;
		void TranslatorController::createTranslator();
	public:
		TranslatorController(std::shared_ptr<ISettingsLoader> settings_loader);
		~TranslatorController();
		void onStateChange() override;

		std::vector<std::wstring> translate(const std::wstring& word) override;
		std::vector<std::wstring> find(const std::wstring& word, size_t max_distance) override;
		std::vector<std::wstring> find_by_prefix(const std::wstring& prefix) override;
		TranslationState getState() override;
		void switchState() override;
		void setView(std::shared_ptr<IView> view) override;
		void loadDict(const std::wstring& filename) override;
	};
}