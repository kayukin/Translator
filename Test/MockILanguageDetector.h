namespace Dictionary {

class MockILanguageDetector : public ILanguageDetector {
 public:
  MOCK_METHOD1(detectLanguage,
      Language(std::wstring word));
};

}  // namespace Dictionary
