#include "stdafx.h"
#pragma once
#include "IDictionary.h"
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <codecvt>
#include <thread>
#include <future>

namespace Dictionary
{
	class Dictionary :public IDictionary
	{
		std::map<std::wstring, std::vector<std::wstring>> m_translation;
		std::vector<std::wstring> m_index;
		Language m_language_from;
		Language m_language_to;
	public:
		Dictionary(Language from, Language to) : m_language_from(from), m_language_to(to) {}
		std::vector<std::wstring> translate(std::wstring word) override;
		std::vector<std::wstring> find(std::wstring word, size_t max_distance) override;
		void addWord(std::wstring word, std::wstring translation) override;

		Language getFrom() override { return m_language_from; }
		Language getTo() override { return m_language_to; }
	};

	size_t levenshtein_distance(const std::wstring& s1, const std::wstring& s2);
}