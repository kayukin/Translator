#include <gtest\gtest.h>
#include <gmock\gmock.h>
#include "../Translator/Translator.h"

class ITranslatorTests :public testing::Test
{
	Dictionary::ITranslator* translator;

};