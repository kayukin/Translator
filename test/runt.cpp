#include "../Translator/TranslatorAPI.h"

int main()
{
	using namespace Dictionary;
	TranslatorFactory factory;
	auto translator = factory.create(L"debugdict.dat");
	TranslationState state(Language(L"Russian"), Language(L"English"));
	
	auto words = translator->find(L"an", 2, state.getFrom());
	auto trans = translator->translate(words[0], state.getFrom());
}