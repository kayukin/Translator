#include <gtest\gtest.h>
#include <gmock\gmock.h>
#include "../Translator/Translator.h"
#include "MockIDictionary.h"
#include "MockILanguageDetector.h"

namespace Dictionary
{
	using namespace ::testing;
	class ITranslatorTests :public testing::Test
	{
	protected:
		std::shared_ptr<ITranslator> translator;
		std::shared_ptr<MockIDictionary> firstDict;
		std::shared_ptr<MockIDictionary> secondDict;
		std::shared_ptr<MockILanguageDetector> lang_detector;
		void SetUp()
		{
			firstDict = std::make_shared<MockIDictionary>();
			EXPECT_CALL(*firstDict, getFrom()).WillRepeatedly(Return(Languages::ENGLISH));
			EXPECT_CALL(*firstDict, getTo()).WillRepeatedly(Return(Languages::RUSSIAN));

			secondDict = std::make_shared<MockIDictionary>();
			EXPECT_CALL(*secondDict, getFrom()).WillRepeatedly(Return(Languages::RUSSIAN));
			EXPECT_CALL(*secondDict, getTo()).WillRepeatedly(Return(Languages::ENGLISH));

			translator = std::shared_ptr<ITranslator>(new Translator(firstDict, secondDict, TranslationState(), lang_detector));
		}
	};

	TEST_F(ITranslatorTests, Find)
	{
		std::wstring word = L"hello";
		std::vector<std::wstring> will_return = { L"mello", L"hallo" };
		EXPECT_CALL(*firstDict, find(word, 2)).WillOnce(Return(will_return));
		auto words = translator->find(word, 2);
		EXPECT_EQ(words, will_return);
	}

	TEST_F(ITranslatorTests, FindWithPrefix)
	{
		std::wstring pref = L"he";
		std::vector<std::wstring> will_return = { L"hello", L"here" };
		EXPECT_CALL(*firstDict, find_by_prefix(pref)).WillOnce(Return(will_return));
		auto res = translator->find_by_prefix(pref);
		EXPECT_EQ(res, will_return);
	}
}