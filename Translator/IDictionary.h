#include "stdafx.h"
#pragma once
#include "Language.h"


namespace Dictionary
{
	class IDictionary
	{
	protected:
		IDictionary(){}
	public:
		virtual ~IDictionary(){}
		virtual std::vector<std::wstring> translate(const std::wstring& word) = 0;
		virtual std::vector<std::wstring> find(const std::wstring& word, size_t max_distance) = 0;
		virtual std::vector<std::wstring> find_by_prefix(const std::wstring& prefix) = 0;
		virtual void addWord(const std::wstring& word, const std::wstring& translation) = 0;
		virtual Language getFrom() = 0;
		virtual Language getTo() = 0;
	};
}