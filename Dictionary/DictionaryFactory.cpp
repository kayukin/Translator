#include "stdafx.h"
#include "DictionaryFactory.h"

namespace Dictionary
{
	template <typename T>
	void vector_unique(std::vector<T>& vec)
	{
		
		std::set<T> s(vec.begin(), vec.end());
		vec.assign(s.begin(), s.end());
	}

	std::shared_ptr<IDictionary> DictionaryFactory::create(std::wstring filename)
	{
		RuEngDictionary* dict = new RuEngDictionary();
		const std::locale empty_locale = std::locale::empty();
		typedef std::codecvt_utf8<wchar_t> converter_type;
		const converter_type* converter = new converter_type;
		const std::locale utf8_locale = std::locale(empty_locale, converter);
		std::wifstream input(filename);
		input.imbue(utf8_locale);

		std::wstring line;
		while (input&&!input.eof())
		{
			std::getline(input, line);
			auto words = StringUtils::split(line, L"<>");
			if (words.size() == 2)
			{
				std::wstring en = words[0];
				std::wstring ru = words[1];
				dict->en_ru[en] = ru;
				dict->ru_en[ru] = en;
				dict->en_index.push_back(en);
				dict->ru_index.push_back(ru);
			}
		}
		vector_unique(dict->en_index);
		vector_unique(dict->ru_index);
		dict->ru_index.erase(std::unique(dict->ru_index.begin(), dict->ru_index.end()), dict->ru_index.end());
		return std::shared_ptr<IDictionary>(dict);
	}
}