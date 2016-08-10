#include "stdafx.h"
#include "RegistrySettings.h"

namespace Dictionary
{
	std::wstring RegistrySettingsLoader::readString(HKEY hKey, std::wstring key)
	{
		TCHAR buf[1024];
		DWORD dwSize = sizeof(buf);
		std::wstring res;
		if (RegQueryValueEx(hKey, key.c_str(), NULL, NULL, (LPBYTE)&buf, &dwSize) == ERROR_SUCCESS)
		{
			res = buf;
		}
		return res;
	}

	void RegistrySettingsLoader::setString(HKEY hKey, std::wstring key, std::wstring value)
	{
		RegSetValueEx(hKey, key.c_str(), NULL, REG_SZ, (const BYTE*)value.c_str(), value.length()*sizeof(TCHAR));
	}

	Settings RegistrySettingsLoader::load()
	{
		Settings settings;
		HKEY hKey;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Gehtsoft\\Dictionary", NULL, KEY_READ, &hKey) == ERROR_SUCCESS)
		{

			std::wstring from = readString(hKey, L"From");
			std::wstring to = readString(hKey, L"To");
			std::wstring filename = readString(hKey, L"Filename");
			settings.dict_filename = filename;
			settings.state.setFrom(Languages::getByName(from));
			settings.state.setTo(Languages::getByName(to));
			RegCloseKey(hKey);
		}
		return settings;
	}


	void RegistrySettingsLoader::save(Settings settings)
	{
		HKEY hKey;
		if (RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Gehtsoft\\Dictionary", NULL, NULL, NULL, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS)
		{
			setString(hKey, L"From", settings.state.getFrom().getName());
			setString(hKey, L"To", settings.state.getTo().getName());
			setString(hKey, L"Filename", settings.dict_filename);
			//auto to = state->getTo().getName();
			//RegSetValueEx(hKey, L"Direction", NULL, REG_S, (const BYTE*), sizeof(val));
			RegCloseKey(hKey);
		}
	}
}