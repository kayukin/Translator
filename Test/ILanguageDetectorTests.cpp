#include <gtest\gtest.h>
#include "../Translator/RegexpLanguageDetector.h"

class ILanguageDetectorTests : public testing::Test
{
protected:
	static Dictionary::ILanguageDetector* detector;
	static void SetUpTestCase() { detector = new Dictionary::RegexpLanguageDetector(); }
	static void TearDownTestCase(){ delete detector; }
};

Dictionary::ILanguageDetector* ILanguageDetectorTests::detector = nullptr;

TEST_F(ILanguageDetectorTests, CheckEnglishWord)
{
	EXPECT_EQ(detector->detectLanguage(L"word"), Dictionary::Languages::ENGLISH);
}

TEST_F(ILanguageDetectorTests, CheckRussianWord)
{
	EXPECT_EQ(detector->detectLanguage(L"слово"), Dictionary::Languages::RUSSIAN);
}