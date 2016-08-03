#include "stdafx.h"
#pragma once
#include "dllspec.h"
#include "IDictionary.h"

namespace Dictionary
{
	class DICTIONARY_API IDictionaryController
	{
	public:
		virtual ~IDictionaryController() {}
		virtual void switchDirection() = 0;
		virtual std::wstring getDirectionText() = 0;
		virtual std::shared_ptr<IDictionary> getDictionary() = 0;
		virtual TranslateDirection getDirection() = 0;
		virtual void detectDirection(std::wstring word) = 0;
	};
}