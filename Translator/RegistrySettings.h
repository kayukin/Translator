#include "stdafx.h"
#pragma once
#include "Settings.h"
#include <Windows.h>
#include "TranslationState.h"

namespace Dictionary
{
	class RegistrySettingsLoader : public ISettingsLoader
	{
		std::wstring readString(HKEY hKey, std::wstring key);
		void setString(HKEY hKey, std::wstring key, std::wstring value);

	public:
		Settings load() override;
		void save(Settings settings) override;
	};
}