#include "stdafx.h"
#include "TranslatorController.h"

namespace Dictionary
{
	TranslatorController::TranslatorController(ViewCallback callback) :m_state_changed_callback(callback)
	{
		Settings settings = m_settings_loader->load();
		m_dict_filename = settings.dict_filename;
		createTranslator();
	}

	TranslatorController::~TranslatorController()
	{
		Settings settings;
		settings.dict_filename = m_dict_filename;
		settings.state = m_translator->getState();
		m_settings_loader->save(settings);
	}

	void TranslatorController::createTranslator()
	{
		Settings settings = m_settings_loader->load();
		m_translator = TranslatorFactory().create(m_dict_filename, settings.state);
		m_translator->setController(this);
	}

	void TranslatorController::onStateChange()
	{
		m_state_changed_callback();
	}

	std::vector<std::wstring> TranslatorController::translate(std::wstring word)
	{
		return m_translator->translate(word);
	}

	std::vector<std::wstring> TranslatorController::find(std::wstring word, size_t max_distance)
	{
		return m_translator->find(word, max_distance);
	}

	TranslationState& TranslatorController::getState()
	{
		return m_translator->getState();
	}

	void TranslatorController::switchState()
	{
		m_translator->switchState();
	}
}