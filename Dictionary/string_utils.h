#include "stdafx.h"
#pragma once
#include <string>
#include <vector>

class StringUtils {
public:
	static std::wstring trim(const std::wstring& str, const std::wstring& whitespace = L" \t");
	static std::wstring reduce(const std::wstring& str, const std::wstring& fill = L" ", const std::wstring& whitespace = L" \t");
	static std::vector<std::wstring> split(const std::wstring& line, const std::wstring& delim);
	static std::vector<std::wstring> split(const std::wstring& line, char delim);
};