#include "ladder.h"

void error(string word1, string word2, string msg) {
  cout << word1 << " " << word2 << " " << msg;
}

bool edit_distance_within(const std::string &str1, const std::string &str2,
                          int d) {
  int m = str1.size(), n = str2.size();

  // If length difference is greater than d, edit distance must be greater
  if (std::abs(m - n) > d)
    return false;

  // Ensure str1 is the smaller string for space efficiency
  if (m > n)
    return edit_distance_within(str2, str1, d);

  std::vector<int> prev(n + 1), curr(n + 1);

  // Initialize the first row
  for (int j = 0; j <= n; ++j)
    prev[j] = j;

  for (int i = 1; i <= m; ++i) {
    curr[0] = i; // Base case for first column
    int minValue = curr[0];

    for (int j = 1; j <= n; ++j) {
      if (str1[i - 1] == str2[j - 1]) {
        curr[j] = prev[j - 1]; // No operation needed
      } else {
        curr[j] = 1 + min({prev[j], curr[j - 1],
                           prev[j - 1]}); // Min of insert, delete, replace
      }
      minValue = std::min(minValue, curr[j]); // Track min in the row
    }

    // Early termination if minValue > d
    if (minValue > d)
      return false;

    prev.swap(curr); // Move to the next row
  }

  return prev[n] <= d;
}
bool is_adjacent(const string &word1, const string &word2) {
  return (edit_distance_within(word1, word2, 1));
}

vector<string> generate_word_ladder(const string &begin_word,
                                    const string &end_word,
                                    const set<string> &word_list) {
  queue<vector<string>> wordLadder;
  wordLadder.push({begin_word});
  set<string> visited;
  visited.insert(begin_word);
  while (!wordLadder.empty()) {
    vector<string> front_ladder = wordLadder.front();
    wordLadder.pop();
    string last_word = front_ladder.back();
    for (string word : word_list) {
      if (is_adjacent(word, last_word)) {
        if (auto search = visited.find(word); search == visited.end()) {
          visited.insert(word);
          vector<string> new_ladder = front_ladder;
          new_ladder.push_back(word);
          if (word == end_word)
            return new_ladder;
          wordLadder.push(new_ladder);
        }
      }
    }
  }
  return {};
}

void load_words(set<string> &word_list, const string &file_name) {
  ifstream in(file_name);
  if (!in) {
    throw runtime_error("Can't open input file");
  }
  for (string s; in >> s;) {
    word_list.insert(s);
  }
}
void print_word_ladder(const vector<string> &ladder) {
	if (ladder.empty()){
		cout << "No word ladder found." << endl;
		return;
	}
  cout << "Word ladder found: ";
	for (string word : ladder)
    cout << word << " ";
	cout << endl;
}
#define my_assert(e)                                                           \
  {                                                                            \
    cout << #e << ((e) ? " passed" : " failed") << endl;                       \
  }
void verify_word_ladder() {
  set<string> word_list;
  load_words(word_list, "../src/words.txt");
  my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
  my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
  my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
  my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
  my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
  my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
