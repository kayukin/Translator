#include "stdafx.h"
#pragma once
#include "TranslationState.h"

namespace Dictionary
{
	struct Settings
	{
		TranslationState state;
		std::wstring dict_filename;
	};

	class ISettingsLoader
	{
	public:

		virtual Settings load() = 0;
		virtual void save(Settings) = 0;
	};
}