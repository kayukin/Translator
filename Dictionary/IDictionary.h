#include "stdafx.h"
#pragma once
#include "dllspec.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Dictionary
{
	enum DICTIONARY_API TranslateDirection
	{
		RUS_TO_ENG, ENG_TO_RUS
	};
	class DICTIONARY_API IDictionary
	{
	protected:
		IDictionary(){}
	public:
		virtual ~IDictionary(){}
		virtual std::wstring translate(std::wstring word, TranslateDirection direction) = 0;
		virtual std::vector<std::wstring> find(std::wstring word, size_t max_distance, TranslateDirection direction) = 0;
		friend class IDictionaryFactory;
	};

	template class DICTIONARY_API std::shared_ptr<IDictionary>;
}