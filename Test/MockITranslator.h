namespace Dictionary {

class MockITranslator : public ITranslator {
 public:
  MOCK_METHOD1(translate,
      std::vector<std::wstring>(const std::wstring& word));
  MOCK_METHOD2(find,
      std::vector<std::wstring>(const std::wstring& word, size_t max_distance));
  MOCK_METHOD1(find_by_prefix,
      std::vector<std::wstring>(const std::wstring& prefix));
  MOCK_METHOD0(getState,
      TranslationState&());
  MOCK_METHOD0(switchState,
      void());
  MOCK_METHOD1(setController,
      void(std::shared_ptr<ITranslatorController> controller));
};

}  // namespace Dictionary
