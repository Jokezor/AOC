#include <bits/stdc++.h>
#include <fstream>
#include <string>

#define ll long long

using namespace std;

bool isPalindrome(string s) {
  for (int i = 0; i < s.length() / 2; i++) {
    if (s[i] != s[s.length() - 1 - i]) {
      return false;
    }
  }
  return true;
}

ll getRank(vector<ll> hand) {
  vector<ll> counter(15);

  for (int i = 0; i < hand.size(); i++) {
    counter[hand[i]]++;
  }

  sort(counter.begin(), counter.end(), greater<>());

  if (counter[0] == 5) {
    return 7;
  }

  if (counter[0] == 4) {
    return 6;
  }

  if (counter[0] == 3 && counter[1] == 2) {
    return 5;
  }

  if (counter[0] == 3) {
    return 4;
  }

  if (counter[0] == 2 && counter[1] == 2) {
    return 3;
  }

  if (counter[0] == 2) {
    return 2;
  }

  return 1;
}

bool rankSorter(vector<ll> hand_1, vector<ll> hand_2) {

  ll rank_1 = getRank(hand_1);
  ll rank_2 = getRank(hand_2);

  if (rank_1 == rank_2) {
    for (int i = 0; i < 5; i++) {
      if (hand_1[i] != hand_2[i]) {
        return hand_1[i] < hand_2[i];
      }
    }
  }

  return rank_1 < rank_2;
}

ll get_number(string row, pair<int, int> coords) {
  int start_number = coords.first;
  int end_number = coords.second;

  string number = "";
  while (start_number <= end_number) {
    number += row[start_number];
    start_number++;
  }
  return stoll(number);
}

struct hash_pair {
  template <class T1, class T2> size_t operator()(const pair<T1, T2> &p) const {
    auto hash1 = hash<T1>{}(p.first);
    auto hash2 = hash<T2>{}(p.second);

    if (hash1 != hash2) {
      return hash1 ^ hash2;
    }

    // If hash1 == hash2, their XOR is zero.
    return hash1;
  }
};

struct hash_triplet {
  template <class T1, class T2, class T3>
  size_t operator()(const tuple<T1, T2, T3> &p) const {
    auto hash1 = hash<T1>{}(get<0>(p));
    auto hash2 = hash<T2>{}(get<1>(p));
    auto hash3 = hash<T3>{}(get<2>(p));

    size_t seed = 0;
    seed ^= hash1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);

    return seed;
  }
};

bool is_mirror_horizontal(const vector<string> &pattern, int row) {
  int n = pattern.size();
  for (int i = 0; i < pattern[0].length(); i++) {
    if (pattern[row][i] != pattern[n - row - 1][i]) {
      return false;
    }
  }
  return true;
}

void solution() {
  string row;
  ll ans = 0;

  vector<string> rows;

  ifstream input("example_input_2.txt");

  if (input.is_open()) {
    while (getline(input, row)) {
      rows.push_back(row);
    }
    input.close();
  }

  int pattern_nums = 1;
  for (int i = 0; i < rows.size(); i++) {
    if (rows[i] == "") {
      pattern_nums++;
    }
  }

  // Get the patterns grouped.
  vector<vector<string>> patterns(pattern_nums);
  int row_number = 0;
  for (int i = 0; i < rows.size(); i++) {
    if (rows[i] == "") {
      row_number++;
    } else {
      patterns[row_number].push_back(rows[i]);
    }
  }

  vector<vector<string>> col_patterns;
  // Create columns
  for (int i = 0; i < pattern_nums; i++) {
    vector<string> pattern = patterns[i];
    vector<string> col_pattern(pattern[0].length());

    for (int row = 0; row < pattern.size(); row++) {
      for (int i = 0; i < pattern[0].length(); i++) {
        col_pattern[i] += pattern[row][i];
      }
    }
    col_patterns.push_back(col_pattern);
  }

  for (int i = 0; i < pattern_nums; i++) {
    vector<string> pattern = patterns[i];
    vector<string> col_pattern = col_patterns[i];

    int n = pattern.size();
    int break_point = 0;

    // So instead, start at each row,
    // Check if below row and above row match.
    // If so, continue until one is 0 or n.
    // Meaning we hit the edge.
    for (int j = 0; j < n - 1; j++) {
      vector<string> pattern_copy(pattern);
      bool found = false;
      // Replace pattern[j] one character at a time.
      for (int smudge = 0; smudge < pattern[j].length(); smudge++) {
        pattern_copy[j][smudge] = pattern_copy[j][smudge] == '#' ? '.' : '#';
        int l = j + 1;
        int k = j;
        while (pattern_copy[l] == pattern_copy[k]) {
          l++;
          k--;
          if (l == n || k < 0) {
            found = true;
            break;
          }
        }
        if (found) {
          break_point = j + 1;
          break;
        }
      }
      if (found) {
        break;
      }
    }
    if (break_point > 0) {
      ans += break_point * 100;
      break_point = 0;
    }

    int m = col_pattern.size();

    for (int j = 0; j < m - 1; j++) {
      bool found = false;
      int l = j + 1;
      int k = j;

      while (col_pattern[l] == col_pattern[k]) {
        l++;
        k--;

        if (l == m || k < 0) {
          found = true;
          break;
        }
      }
      if (found) {
        break_point = j + 1;
      }
    }
    if (break_point > 0) {
      ans += break_point;
    }
  }

  printf("%lld\n", ans);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;

  while (t--)
    solution();

  return 0;
}
