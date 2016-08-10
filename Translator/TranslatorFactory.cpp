#include "stdafx.h"
#include "TranslatorFactory.h"
#include "Locator.h"

namespace Dictionary
{

	std::vector<std::wstring> split(const std::wstring& line, const std::wstring& delim)
	{
		std::vector<std::wstring> tokens;
		size_t begin = 0;
		size_t end = 0;
		while ((end = line.find(delim, begin)) != std::wstring::npos) {
			std::wstring token = line.substr(begin, end - begin);
			tokens.push_back(token);
			begin = end + delim.length();
		}
		tokens.push_back(line.substr(begin, line.length() - begin));
		return tokens;
	}

	std::shared_ptr<ITranslator> TranslatorFactory::create(std::wstring filename, TranslationState state)
	{
		const std::locale empty_locale = std::locale::empty();
		typedef std::codecvt_utf8<wchar_t> converter_type;
		const converter_type* converter = new converter_type;
		const std::locale utf8_locale = std::locale(empty_locale, converter);
		std::wifstream input(filename);
		if (!input)
		{
			return nullptr;
		}
		input.imbue(utf8_locale);


		std::wstring line;

		std::getline(input, line);
		auto words = split(line, L"<>");
		Language first_lang = Languages::getByName(words[0]);
		Language second_lang = Languages::getByName(words[1]);


		std::shared_ptr<IDictionary> first(new Dictionary(first_lang, second_lang)), second(new Dictionary(second_lang, first_lang));

		while (input&&!input.eof())
		{
			std::getline(input, line);
			words = split(line, L"<>");
			if (words.size() == 2)
			{
				first->addWord(words[0], words[1]);
				second->addWord(words[1], words[0]);
			}
		}
		
		return Locator::Instance().getTranslator(first, second, state);
	}
}