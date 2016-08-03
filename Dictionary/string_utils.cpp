#include "stdafx.h"
#include "string_utils.h"

using namespace std;

wstring StringUtils::trim(const wstring& str, const wstring& whitespace)
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == wstring::npos)
		return L""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

wstring StringUtils::reduce(const wstring& str, const wstring& fill, const wstring& whitespace)
{
	// trim first
	auto result = trim(str, whitespace);

	// replace sub ranges
	auto beginSpace = result.find_first_of(whitespace);
	while (beginSpace != wstring::npos)
	{
		const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
		const auto range = endSpace - beginSpace;

		result.replace(beginSpace, range, fill);

		const auto newStart = beginSpace + fill.length();
		beginSpace = result.find_first_of(whitespace, newStart);
	}

	return result;
}

vector<wstring> StringUtils::split(const wstring& line, const wstring& delim)
{
	vector<wstring> tokens;
	size_t begin = 0;
	size_t end = 0;
	while ((end = line.find(delim, begin)) != wstring::npos) {
		wstring token = line.substr(begin, end - begin);
		tokens.push_back(token);
		begin = end + delim.length();
	}
	tokens.push_back(line.substr(begin, line.length() - begin));
	return tokens;
}

vector<wstring> StringUtils::split(const wstring& line, char delim)
{
	vector<wstring> tokens;
	size_t begin = 0;
	size_t end = 0;
	while ((end = line.find(delim, begin)) != wstring::npos) {
		wstring token = line.substr(begin, end - begin);
		tokens.push_back(token);
		begin = end + 1;
	}
	tokens.push_back(line.substr(begin, line.length() - begin));
	return tokens;
}