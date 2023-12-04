#include <bits/stdc++.h>
#include <fstream>
#include <string>

#define ll long long

using namespace std;

ll get_number(string row, pair<int, int> coords) {
  int start_number = coords.first;
  int end_number = coords.second;

  string number = "";
  while (start_number <= end_number) {
    number += row[start_number];
    start_number++;
  }
  return stoi(number);
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

  ifstream input("input.txt");

  if (input.is_open()) {
    while (getline(input, row)) {
      rows.push_back(row);
    }
    input.close();
  }

  int row_number = 0;

  // Keeps the numbers we have.
  vector<unordered_set<int>> card_numbers;

  // Keeps the winning numbers
  vector<vector<int>> winning_numbers;

  for (string row : rows) {
    // Get number positions
    int num_start = -1;
    int num_end = -1;
    string number = "";

    bool is_card_numbers = true;
    bool started = false;
    unordered_set<int> card_number;
    vector<int> winning_number;

    for (int col = 0; col < row.length(); ++col) {
      if (row[col] == ':') {
        started = true;
        continue;
      } else if (row[col] == '|') {
        is_card_numbers = false;
        continue;
      } else if (started && row[col] - '0' >= 0 && '9' - row[col] >= 0) {
        if (num_start == -1) {
          num_start = col;
          num_end = col;
        } else {
          num_end++;
        }
        number += row[col];
      } else {
        // Check if there was a num, add it.
        if (num_start != -1) {
          int number_int = (int)stoi(number);
          if (is_card_numbers) {
            card_number.insert(number_int);
          } else {
            winning_number.push_back(number_int);
          }
        }
        num_start = -1;
        num_end = -1;
        number = "";
      }
    }
    if (num_start != -1) {
      int number_int = (int)stoi(number);
      winning_number.push_back(number_int);
    }
    card_numbers.push_back(card_number);
    winning_numbers.push_back(winning_number);
    row_number++;
  }

  for (int i = 0; i < winning_numbers.size(); i++) {
    ll card_points = 0;
    for (int j = 0; j < winning_numbers[i].size(); j++) {
      if (card_numbers[i].find(winning_numbers[i][j]) !=
          card_numbers[i].end()) {
        card_points = max(1LL, card_points * 2);
      }
    }
    ans += card_points;
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
