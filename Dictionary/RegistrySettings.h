#include "stdafx.h"
#pragma once
#include "ISettings.h"

namespace Dictionary
{
	class RegistrySettings : public ISettings
	{
	public:
		TranslateDirection load() override
		{
			HKEY hKey;
			Dictionary::TranslateDirection res = Dictionary::TranslateDirection::ENG_TO_RUS;
			if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Gehtsoft\\Dictionary", NULL, KEY_READ, &hKey) == ERROR_SUCCESS)
			{
				DWORD direct;
				DWORD dwSize = sizeof(DWORD);
				if (RegQueryValueEx(hKey, L"Direction", NULL, NULL, (LPBYTE)&direct, &dwSize) == ERROR_SUCCESS)
				{
					res = (Dictionary::TranslateDirection)direct;
				}
				RegCloseKey(hKey);
			}
			return res;
		}
		void save(TranslateDirection dir) override
		{
			HKEY hKey;
			if (RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Gehtsoft\\Dictionary", NULL, NULL, NULL, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS)
			{
				DWORD val = dir;
				RegSetValueEx(hKey, L"Direction", NULL, REG_DWORD, (const BYTE*)&val, sizeof(val));
				RegCloseKey(hKey);
			}
		}
	};
}