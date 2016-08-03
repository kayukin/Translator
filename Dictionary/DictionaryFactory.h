#include "stdafx.h"
#pragma once
#include "dllspec.h"
#include "RuEngDictionary.h"
#include <fstream>


namespace Dictionary
{
	class DICTIONARY_API DictionaryFactory
	{
	public:
		std::shared_ptr<IDictionary> create(std::wstring filename);
	};
}