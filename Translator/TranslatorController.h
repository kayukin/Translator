#include "stdafx.h"
#pragma once
#include "ITranslatorController.h"
#include "TranslatorFactory.h"
#include "Settings.h"
#include "Locator.h"

namespace Dictionary
{
	class TranslatorController : public ITranslatorController
	{
		std::shared_ptr<ITranslator> m_translator;
		std::shared_ptr<ISettingsLoader> m_settings_loader = Locator::Instance().getSettingsLoader();
		std::wstring m_dict_filename;
		IView* m_view;
		void TranslatorController::createTranslator();
	public:
		TranslatorController();
		~TranslatorController();
		void onStateChange() override;

		std::vector<std::wstring> translate(const std::wstring& word) override;
		std::vector<std::wstring> find(const std::wstring& word, size_t max_distance) override;
		std::vector<std::wstring> find_by_prefix(const std::wstring& prefix) override;
		TranslationState& getState() override;
		void switchState() override;
		void setView(IView* view) override;
		void loadDict(const std::wstring& filename) override;
	};
}