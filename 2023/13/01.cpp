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

void solution() {
  string row;
  ll ans = 0;

  vector<string> rows;

  ifstream input("example_input.txt");

  if (input.is_open()) {
    while (getline(input, row)) {
      rows.push_back(row);
    }
    input.close();
  }

  // What we should do is:
  // 1. Find palindromes.
  // For each row, find which index has a palindrome.
  // So for each row, we check if the start and end substring
  // makes a palindrome.
  // If not, then we shrink index and restart.

  int pattern_nums = 1;

  for (int i = 0; i < rows.size(); i++) {
    if (rows[i] == "") {
      pattern_nums++;
    }
  }

  vector<vector<string>> patterns(pattern_nums);

  int row_number = 0;
  for (int i = 0; i < rows.size(); i++) {
    if (rows[i] == "") {
      row_number++;
    } else {
      patterns[row_number].push_back(rows[i]);
    }
  }

  vector<int> mirror_points;
  vector<vector<string>> col_patterns;
  // Create columns
  for (int i = 0; i < pattern_nums; i += 2) {
    vector<string> pattern = patterns[i];
    vector<string> col_pattern(pattern[0].length());

    for (int row = 0; row < pattern.size(); row++) {
      for (int i = 0; i < pattern[0].length(); i++) {
        col_pattern[i] += pattern[row][i];
      }
    }
    col_patterns.push_back(col_pattern);
  }

  // Instead, check if each number is mirrored.
  for (int i = 1; i < pattern_nums; i += 2) {
    cout << i << "\n";
    vector<string> pattern = patterns[i];
    int n = pattern.size();
    int break_point = 0;
    for (int i = 0; i < n; i++) {
      if (pattern[i] == pattern[n - i]) {
        break_point = i;
      }
    }
    if (break_point > 0) {
      mirror_points.push_back(break_point);
      ans += break_point * 100;
    }
  }

  for (vector<string> pattern : col_patterns) {
    int n = pattern.size();
    int break_point = 0;
    for (int i = 0; i < n; i++) {
      cout << pattern[i] << "\n";
      if (pattern[i] == pattern[n - i]) {
        break_point = i + 1;
      }
    }
    if (break_point > 0) {
      mirror_points.push_back(break_point);
      ans += break_point;
    }
  }

  // Now check each column.

  // For each character in a row,
  // Check current character + right until end
  // Record any palindromes found.
  // Check all left as well.
  // Then we can instead for each row:
  //
  // Check if any other row has the same index as the
  // palindrome start and end.
  //
  // vector<vector<set<pair<int, int>>>> row_palindromes;
  //
  // for (int i = 0; i < patterns.size(); i += 2) {
  //   vector<string> pattern = patterns[i];
  //   vector<set<pair<int, int>>> pattern_palindromes;
  //
  //   // Find all palindromes per row
  //   for (string row : pattern) {
  //     set<pair<int, int>> current_palindromes;
  //     for (int i = 0; i < row.length(); i++) {
  //       for (int j = 2; j + i <= row.length(); j++) {
  //         if (isPalindrome(row.substr(i, j))) {
  //           current_palindromes.insert({i, i + j - 1});
  //         }
  //       }
  //     }
  //     pattern_palindromes.push_back(current_palindromes);
  //   }
  //   row_palindromes.push_back(pattern_palindromes);
  // }
  // //
  // // // Same for columns
  // vector<vector<set<pair<int, int>>>> column_palindromes;
  // //
  // for (int i = 1; i < patterns.size(); i += 2) {
  //   vector<string> pattern = patterns[i];
  //   vector<set<pair<int, int>>> pattern_palindromes;
  //
  //   // Find all palindromes per column
  //   for (int col = 0; col < pattern[0].length(); col++) {
  //     set<pair<int, int>> current_palindromes;
  //
  //     // Need to scan for each row.
  //     for (int start = 0; start < pattern.size(); start++) {
  //       // Start with one char
  //       string current = "";
  //       current += pattern[start][col];
  //       for (int end = start + 1; end < pattern.size(); end++) {
  //         current += pattern[end][col];
  //         if (isPalindrome(current)) {
  //           current_palindromes.insert({start, end});
  //           // cout << current << "\n";
  //         }
  //       }
  //     }
  //     pattern_palindromes.push_back(current_palindromes);
  //   }
  //   column_palindromes.push_back(pattern_palindromes);
  // }
  //
  // // every even is row
  // // every odd is column
  //
  // for (vector<set<pair<int, int>>> pattern_palindrome : row_palindromes) {
  //   int n = pattern_palindrome.size();
  //   // seg fault?
  //   set<pair<int, int>> palindrome_set = pattern_palindrome[0];
  //
  //   for (pair<int, int> palindrome : palindrome_set) {
  //     int j = 1;
  //     for (; j < n; j++) {
  //       set<pair<int, int>> palindrome_set = pattern_palindrome[j];
  //
  //       if (palindrome_set.find(palindrome) == palindrome_set.end()) {
  //         break;
  //       }
  //     }
  //     if (j == n) {
  //
  //       ans += ceil((double)(palindrome.first + palindrome.second) / 2);
  //       break;
  //     }
  //   }
  //   // cout << ans << "\n\n";
  // }
  //
  // for (vector<set<pair<int, int>>> pattern_palindrome : column_palindromes) {
  //   int n = pattern_palindrome.size();
  //   // seg fault?
  //   set<pair<int, int>> palindrome_set = pattern_palindrome[0];
  //
  //   for (pair<int, int> palindrome : palindrome_set) {
  //     int j = 1;
  //     for (; j < n; j++) {
  //       set<pair<int, int>> palindrome_set = pattern_palindrome[j];
  //
  //       if (palindrome_set.find(palindrome) == palindrome_set.end()) {
  //         break;
  //       }
  //       // cout << palindrome.first << ":" << palindrome.second << "\n";
  //     }
  //     if (j == n) {
  //       cout << palindrome.first << ":" << palindrome.second << "\n";
  //       ans += 100 * ceil((double)(palindrome.first + palindrome.second) /
  //       2); break;
  //     }
  //   }
  //   // cout << ans << "\n\n";
  // }

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
