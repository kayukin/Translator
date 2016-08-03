#include "stdafx.h"
#include "RuEngDictionary.h"


namespace Dictionary
{
	using namespace std;

	size_t levenshtein_distance(const std::wstring& s1, const std::wstring& s2)
	{
		const std::size_t len1 = s1.size(), len2 = s2.size();
		std::vector<size_t> col(len2 + 1), prevCol(len2 + 1);

		for (size_t i = 0; i < prevCol.size(); i++)
			prevCol[i] = i;
		for (size_t i = 0; i < len1; i++) {
			col[0] = i + 1;
			for (size_t j = 0; j < len2; j++)
				col[j + 1] = std::min({ prevCol[1 + j] + 1, col[j] + 1, prevCol[j] + (s1[i] == s2[j] ? 0 : 1) });
			col.swap(prevCol);
		}
		return prevCol[len2];
	}

	RuEngDictionary::RuEngDictionary()
	{
		m_switch[TranslateDirection::ENG_TO_RUS] = &en_ru;
		m_switch[TranslateDirection::RUS_TO_ENG] = &ru_en;
		m_dir_to_index[TranslateDirection::ENG_TO_RUS] = &en_index;
		m_dir_to_index[TranslateDirection::RUS_TO_ENG] = &ru_index;
	}

	wstring RuEngDictionary::translate(wstring word, TranslateDirection direction)
	{
		return m_switch[direction]->at(word);
	}

	vector<wstring> find_thr(vector<wstring>::iterator begin, vector<wstring>::iterator end, const wstring& word, size_t min_dist)
	{
		vector<wstring> words;
		for (auto it = begin; it != end; it++)
		{
			if (levenshtein_distance(word, *it) <= min_dist)
			{
				words.push_back(*it);
			}
		}
		return words;
	}

	vector<wstring> RuEngDictionary::find(wstring word, size_t min_dist, TranslateDirection direction)
	{
		vector<wstring> res;
		auto& cur_index = *m_dir_to_index[direction];
		size_t proc_count = thread::hardware_concurrency();
		size_t len_of_subarray = cur_index.size() / proc_count;
		vector<future<vector<wstring>>> results;
		auto b = cur_index.begin();
		for (size_t i = 0; i < proc_count; i++)
		{
			future<vector<wstring>> result = async(find_thr, b, b+len_of_subarray, word, min_dist);
			b += len_of_subarray;
			results.push_back(move(result));
		}
		if (b != cur_index.end())
		{
			future<vector<wstring>> result = async(find_thr, b, cur_index.end(), word, min_dist);
			results.push_back(move(result));
		}
		for (auto& r : results)
		{
			r.wait();
		}
		for (auto& r : results)
		{
			auto vec = r.get();
			res.insert(res.end(), vec.begin(), vec.end());
		}
		sort(res.begin(), res.end(), [word](const wstring& left, const wstring& right){return levenshtein_distance(word, left) < levenshtein_distance(word, right); });
		return res;
	}
}