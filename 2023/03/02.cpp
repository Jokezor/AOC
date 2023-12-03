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

  unordered_map<pair<int, int>, pair<int, int>, hash_pair> numbers;
  vector<pair<int, int>> symbols;
  vector<string> rows;

  ifstream input("input.txt");
  int row_number = 0;

  if (input.is_open()) {
    while (getline(input, row)) {
      rows.push_back(row);
    }
    input.close();
  }
  for (string row : rows) {
    // Get number positions
    int num_start = -1;
    int num_end = -1;
    string number = "";

    for (int col = 0; col < row.length(); ++col) {
      if (row[col] - '0' >= 0 && '9' - row[col] >= 0) {
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
          int i = num_start;
          while (i <= num_end) {
            numbers[{row_number, i}] = {num_start, num_end};
            i++;
          }
        }
        num_start = -1;
        num_end = -1;
        number = "";

        // Add symbol.
        if (row[col] != '.') {
          symbols.push_back({row_number, col});
        }
      }
    }
    if (num_start != -1) {
      int number_int = (int)stoi(number);
      int i = num_start;
      while (i <= num_end) {
        numbers[{row_number, i}] = {num_start, num_end};
        i++;
      }
    }

    row_number++;
  }

  // Go through all symbols and check the 8 directions.
  for (auto s : symbols) {
    ll x = s.first;
    ll y = s.second;

    bool is_gear = rows[x][y] == '*';
    unordered_set<tuple<int, int, int>, hash_triplet> adjacent_numbers;

    // W
    if (numbers.find({x, y - 1}) != numbers.end()) {
      pair<int, int> coords = numbers[{x, y - 1}];
      adjacent_numbers.insert({x, coords.first, coords.second});
    }
    // SW
    if (numbers.find({x + 1, y - 1}) != numbers.end()) {
      pair<int, int> coords = numbers[{x + 1, y - 1}];
      adjacent_numbers.insert({x + 1, coords.first, coords.second});
    }
    // S
    if (numbers.find({x + 1, y}) != numbers.end()) {
      pair<int, int> coords = numbers[{x + 1, y}];
      adjacent_numbers.insert({x + 1, coords.first, coords.second});
    }
    // SE
    if (numbers.find({x + 1, y + 1}) != numbers.end()) {
      pair<int, int> coords = numbers[{x + 1, y + 1}];
      adjacent_numbers.insert({x + 1, coords.first, coords.second});
    }
    // E
    if (numbers.find({x, y + 1}) != numbers.end()) {
      pair<int, int> coords = numbers[{x, y + 1}];
      adjacent_numbers.insert({x, coords.first, coords.second});
    }
    // NE
    if (numbers.find({x - 1, y + 1}) != numbers.end()) {
      pair<int, int> coords = numbers[{x - 1, y + 1}];
      adjacent_numbers.insert({x - 1, coords.first, coords.second});
    }
    // N
    if (numbers.find({x - 1, y}) != numbers.end()) {
      pair<int, int> coords = numbers[{x - 1, y}];
      adjacent_numbers.insert({x - 1, coords.first, coords.second});
    }
    // NW
    if (numbers.find({x - 1, y - 1}) != numbers.end()) {
      pair<int, int> coords = numbers[{x - 1, y - 1}];
      adjacent_numbers.insert({x - 1, coords.first, coords.second});
    }

    if (is_gear && adjacent_numbers.size() == 2) {
      ll prod = 1;
      for (auto a : adjacent_numbers) {
        int row = get<0>(a);
        pair<int, int> coords = {get<1>(a), get<2>(a)};
        prod *= get_number(rows[row], coords);
      }
      ans += prod;
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
