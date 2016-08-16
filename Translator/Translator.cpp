#include "stdafx.h"
#include "Translator.h"

namespace Dictionary
{

	Translator::Translator(const std::shared_ptr<IDictionary>& first, const std::shared_ptr<IDictionary>& second, TranslationState state,
		std::shared_ptr<ILanguageDetector> lang_detector)
		:m_first(first), m_second(second), m_lang_detector(lang_detector), m_auto_detect(false){
		if (isSupported(state.getFrom()) && isSupported(state.getTo()))
		{
			m_state = std::shared_ptr<TranslationState>(new TranslationState(state));
		}
		else
		{
			m_state = std::shared_ptr<TranslationState>(new TranslationState(m_first->getFrom(), m_first->getTo()));
		}
	}


	TranslationState& Translator::getState()
	{
		return *m_state;
	}

	bool Translator::isSupported(const Language& lang) const
	{
		return lang == m_first->getFrom() || lang == m_second->getFrom();
	}

	std::vector<std::wstring> Translator::translate(const std::wstring& word)
	{
		if (m_state->getFrom() == m_first->getFrom())
		{
			return m_first->translate(word);
		}
		else
		{
			return m_second->translate(word);
		}
	}

	std::vector<std::wstring> Translator::find(const std::wstring& word, size_t max_distance)
	{
		if (m_auto_detect)
		{
			auto lang = m_lang_detector->detectLanguage(word);
			if (lang != getState().getFrom())
			{
				switchState();
			}
		}
		if (m_state->getFrom() == m_first->getFrom())
		{
			return m_first->find(word, max_distance);
		}
		else
		{
			return m_second->find(word, max_distance);
		}
	}

	std::vector<std::wstring> Translator::find_by_prefix(const std::wstring& prefix)
	{
		if (m_state->getFrom() == m_first->getFrom())
		{
			return m_first->find_by_prefix(prefix);
		}
		else
		{
			return m_second->find_by_prefix(prefix);
		}
	}

	void Translator::switchState()
	{
		Language temp = m_state->getFrom();
		m_state->setFrom(m_state->getTo());
		m_state->setTo(temp);
		if (auto controller = m_controller.lock())
		{
			controller->onStateChange();
		}
	}

	void Translator::setController(std::shared_ptr<ITranslatorController> controller)
	{
		m_controller = controller;
	}

	void Translator::setAutoDetect(bool val)
	{
		m_auto_detect = val;
	}
}