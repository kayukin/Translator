#include "stdafx.h"
#pragma once
#include "Language.h"


namespace Dictionary
{
	class TranslationState
	{
		Language m_from;
		Language m_to;
	public:
		TranslationState() :m_from(Languages::UNKNOWN), m_to(Languages::UNKNOWN){}
		TranslationState(Language& from, Language& to) :m_from(from), m_to(to){}
		Language getFrom(){ return m_from; }
		Language getTo(){ return m_to; }
		void setFrom(Language from){ m_from = from; }
		void setTo(Language to){ m_to = to; }
		bool operator==(const TranslationState& other){ return m_from == other.m_from && m_to == other.m_to; }
	};
}