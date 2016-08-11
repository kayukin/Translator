#include "stdafx.h"
#include "TranslatorController.h"

namespace Dictionary
{
	TranslatorController::TranslatorController(std::shared_ptr<ISettingsLoader> settings_loader) :m_settings_loader(settings_loader)
	{
		Settings settings = m_settings_loader->load();
		m_dict_filename = settings.dict_filename;
	}

	TranslatorController::~TranslatorController()
	{
		Settings settings;
		settings.dict_filename = m_dict_filename;
		settings.state = getState();
		m_settings_loader->save(settings);
	}

	void TranslatorController::createTranslator()
	{
		Settings settings = m_settings_loader->load();
		m_translator = TranslatorFactory().create(m_dict_filename, settings.state);
		if (m_translator)
		{
			m_translator->setController(shared_from_this());
		}
	}

	void TranslatorController::onStateChange()
	{
		if (auto view = m_view.lock())
		{
			view->onSwitchState();
		}
	}

	std::vector<std::wstring> TranslatorController::translate(const std::wstring& word)
	{
		if (m_translator)
		{
			return m_translator->translate(word);
		}
		return std::vector<std::wstring>();
	}

	std::vector<std::wstring> TranslatorController::find(const std::wstring& word, size_t max_distance)
	{
		if (m_translator)
		{
			return m_translator->find(word, max_distance);
		}
		return std::vector<std::wstring>();
	}

	TranslationState TranslatorController::getState()
	{
		if (m_translator)
		{
			return m_translator->getState();
		}
		return TranslationState();
	}

	void TranslatorController::switchState()
	{
		if (m_translator)
		{
			m_translator->switchState();
		}
	}

	void TranslatorController::setView(std::shared_ptr<IView> view)
	{
		m_view = view;
	}

	void TranslatorController::loadDict(const std::wstring& filename)
	{
		m_dict_filename = filename;
		createTranslator();
	}

	std::vector<std::wstring> TranslatorController::find_by_prefix(const std::wstring& prefix)
	{
		if (m_translator)
		{
			return m_translator->find_by_prefix(prefix);
		}
		return std::vector<std::wstring>();
	}

	void TranslatorController::setAutoDetect(bool val)
	{
		m_translator->setAutoDetect(val);
	}

}