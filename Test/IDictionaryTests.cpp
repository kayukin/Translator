#include <gtest\gtest.h>
#include "../Translator/IDictionary.h"
#include "../Translator/Dictionary.h"

class IDictionaryTests :public ::testing::Test
{
protected:
	Dictionary::IDictionary* dict;
	IDictionaryTests()
	{
		dict = new Dictionary::Dictionary(Dictionary::Languages::ENGLISH, Dictionary::Languages::RUSSIAN);
	}
	~IDictionaryTests()
	{
		delete dict;
	}
};

TEST_F(IDictionaryTests, CheckWordTranslate)
{
	std::wstring word = L"word";
	std::wstring translation = L"слово";
	dict->addWord(word, translation);
	auto result_of_translation_word = dict->translate(L"word");
	EXPECT_STREQ(result_of_translation_word[0].c_str(), translation.c_str());
}