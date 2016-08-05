#include "stdafx.h"
#pragma once
#include "ITranslator.h"
#include "Dictionary.h"
#include "Translator.h"
#include <fstream>
#include <codecvt>
#include "Locator.h"


namespace Dictionary
{
	class TranslatorFactory
	{
	public:
		std::shared_ptr<ITranslator> create(std::wstring filename, TranslationState state);
	};
}