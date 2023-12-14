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

  ifstream input("input.txt");

  if (input.is_open()) {
    while (getline(input, row)) {
      rows.push_back(row);
    }
    input.close();
  }

  int n = rows.size();
  int m = rows[0].length();

  vector<string> columns(m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      columns[j] += rows[i][j];
    }
  }

  vector<int> positions;

  unordered_map<string, int> cycle_loads;
  unordered_map<string, int> cycles_map;
  // Look for the same starting position at cycles
  set<string> cycle_starts;
  set<string> repeated_cycles;
  vector<string> test;

  for (int k = 0; k < 1000; k++) {
    // North
    for (int j = 0; j < m; j++) {
      string column_copy = columns[j];
      int max = 0;
      for (int i = 0; i < m; i++) {
        if (columns[j][i] == '#') {
          max = i + 1;
        } else if (columns[j][i] == 'O') {
          swap(column_copy[i], column_copy[max]);
          max++;
        }
      }
      columns[j] = column_copy;
    }
    // West
    for (int i = 0; i < n; i++) {
      string row_copy = "";
      for (int j = 0; j < m; j++) {
        row_copy += columns[j][i];
      }
      int max = 0;
      for (int j = 0; j < m; j++) {
        if (columns[j][i] == '#') {
          max = j + 1;
        } else if (columns[j][i] == 'O') {
          swap(row_copy[j], row_copy[max]);
          max++;
        }
      }
      for (int j = 0; j < m; j++) {
        columns[j][i] = row_copy[j];
      }
    }
    // South
    for (int j = 0; j < m; j++) {
      string column_copy = columns[j];
      int max = m - 1;
      for (int i = m - 1; i >= 0; i--) {
        if (columns[j][i] == '#') {
          max = i - 1;
        } else if (columns[j][i] == 'O') {
          swap(column_copy[i], column_copy[max]);
          max--;
        }
      }
      columns[j] = column_copy;
    }
    // East
    for (int i = 0; i < n; i++) {
      string row_copy = "";
      for (int j = 0; j < m; j++) {
        row_copy += columns[j][i];
      }
      int max = m - 1;
      for (int j = m - 1; j >= 0; j--) {
        if (columns[j][i] == '#') {
          max = j - 1;
        } else if (columns[j][i] == 'O') {
          swap(row_copy[j], row_copy[max]);
          max--;
        }
      }
      for (int j = 0; j < m; j++) {
        columns[j][i] = row_copy[j];
      }
    }
    int cycle_ans = 0;
    for (string column : columns) {
      for (int i = 0; i < m; i++) {
        if (column[i] == 'O') {
          cycle_ans += (m - i);
        }
      }
    }

    // Insert board as one string.
    string board = "";
    for (string column : columns) {
      board += column;
    }

    if (cycle_starts.find(board) != cycle_starts.end()) {
      if (repeated_cycles.find(board) == repeated_cycles.end()) {
        repeated_cycles.insert(board);

        // Added vector since set does not maintain insertion order
        // But rather using less.
        test.push_back(board);
      }
    } else {
      cycles_map[board] = k;
    }
    cycle_starts.insert(board);
    cycle_loads[board] = cycle_ans;

    if (k % 10000 == 0) {
      cout << k << "\n";
    }
  }

  for (string t : test) {
    cout << cycle_loads[t] << "\n";
  }

  cout << cycle_starts.size() << "\n";
  cout << repeated_cycles.size() << "\n";

  // First we need to check so we go through all combinations
  ll ans_ind = 1000000000 - cycle_starts.size();

  // Then we can check which cycle we repeat.
  ans_ind = ans_ind % repeated_cycles.size() - 1;

  cout << ans_ind << "; " << cycle_loads[test[ans_ind]] << "\n";

  ans = cycle_loads[test[ans_ind]];

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
