#include "stdafx.h"
#include "Translator.h"

namespace Dictionary
{

	Translator::Translator(std::shared_ptr<IDictionary> first, std::shared_ptr<IDictionary> second, TranslationState state)
		:m_first(first), m_second(second){
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

	std::vector<std::wstring> Translator::translate(std::wstring word)
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

	std::vector<std::wstring> Translator::find(std::wstring word, size_t max_distance)
	{
		if (m_state->getFrom() == m_first->getFrom())
		{
			return m_first->find(word, max_distance);
		}
		else
		{
			return m_second->find(word, max_distance);
		}
	}

	void Translator::switchState()
	{
		Language temp = m_state->getFrom();
		m_state->setFrom(m_state->getTo());
		m_state->setTo(temp);
		if (m_controller != nullptr)
		{
			m_controller->onStateChange();
		}
	}

	void Translator::setController(ITranslatorController* controller)
	{
		m_controller = controller;
	}
}