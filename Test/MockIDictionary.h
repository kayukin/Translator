namespace Dictionary {

class MockIDictionary : public IDictionary {
 public:
  MOCK_METHOD1(translate,
      std::vector<std::wstring>(const std::wstring& word));
  MOCK_METHOD2(find,
      std::vector<std::wstring>(const std::wstring& word, size_t max_distance));
  MOCK_METHOD1(find_by_prefix,
      std::vector<std::wstring>(const std::wstring& prefix));
  MOCK_METHOD2(addWord,
      void(const std::wstring& word, const std::wstring& translation));
  MOCK_METHOD0(getFrom,
      Language());
  MOCK_METHOD0(getTo,
      Language());
};

}  // namespace Dictionary
