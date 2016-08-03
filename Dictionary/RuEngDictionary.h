#include "stdafx.h"
#include "dllspec.h"
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
#include "string_utils.h"

namespace Dictionary
{
	template class DICTIONARY_API std::map<std::wstring, std::wstring>;
	template class DICTIONARY_API std::vector<std::wstring>;
	template class DICTIONARY_API std::map<TranslateDirection, std::map<std::wstring, std::wstring>*>;
	template class DICTIONARY_API std::map<TranslateDirection, std::vector<std::wstring>*>;

	class DICTIONARY_API RuEngDictionary :public IDictionary
	{
		std::map<std::wstring, std::wstring> en_ru;
		std::map<std::wstring, std::wstring> ru_en;
		std::vector<std::wstring> ru_index;
		std::vector<std::wstring> en_index;
		std::map<TranslateDirection, std::map<std::wstring, std::wstring>*> m_switch;
		std::map<TranslateDirection, std::vector<std::wstring>*> m_dir_to_index;
	protected:
		RuEngDictionary();
	public:
		std::wstring translate(std::wstring word, TranslateDirection direction) override;
		std::vector<std::wstring> find(std::wstring word, size_t max_distance, TranslateDirection direction) override;
		friend class DictionaryFactory;
	};

	size_t levenshtein_distance(const std::wstring& s1, const std::wstring& s2);
}