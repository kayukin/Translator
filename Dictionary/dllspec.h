#ifdef DICTIONARY_EXPORTS
#define DICTIONARY_API __declspec(dllexport)
#else
#define DICTIONARY_API __declspec(dllimport)
#endif