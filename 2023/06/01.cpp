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

  ifstream input("input.txt");

  if (input.is_open()) {
    while (getline(input, row)) {
      rows.push_back(row);
    }
    input.close();
  }

  int row_number = 0;
  string type = "Time:";
  vector<ll> times;
  vector<ll> distances;

  for (string row : rows) {
    // Get number positions
    int num_start = -1;
    int num_end = -1;
    string number = "";

    if (row.find("Distance:") != string::npos) {
      type = "Distance:";
    }

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
          ll number_int = stoll(number);
          if (type == "Time:") {
            times.push_back(number_int);
          } else {
            distances.push_back(number_int);
          }
        }
        num_start = -1;
        num_end = -1;
        number = "";
      }
    }
    if (num_start != -1) {
      ll number_int = stoll(number);
      if (type == "Time:") {
        times.push_back(number_int);
      } else {
        distances.push_back(number_int);
      }
    }

    row_number++;
  }

  int n = times.size();
  vector<vector<ll>> winning_races(n);

  for (int i = 0; i < n; i++) {
    ll start_time = 0;
    while (start_time < times[i]) {
      ll distance = (times[i] - start_time) * start_time;
      if (distance > distances[i]) {
        winning_races[i].push_back(start_time);
      }
      start_time++;
    }
    if (ans <= 0) {
      ans = winning_races[i].size();
    } else {
      ans *= winning_races[i].size();
    }
  }
  // Check for each race, h

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
