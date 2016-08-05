#include "stdafx.h"
#pragma once

namespace Dictionary
{
	class Language
	{
		std::wstring m_name;
	protected:
		Language(std::wstring name) :m_name(name){}
		Language(){
			m_name = L"Unknown";
		}
	public:
		bool operator==(const Language& other)const{ return m_name == other.m_name; }
		bool operator!=(const Language& other)const{ return !(*this == other); }
		std::wstring getName()const { return m_name; }
		friend class Languages;
	};

	class UnknownLanguage{};
	
	class Languages
	{
	public:
		static Language getByName(const std::wstring& name);
		static const Language RUSSIAN;
		static const Language ENGLISH;
		static const Language UNKNOWN;
	};
}