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

  vector<map<string, int>> hashmap(256);

  map<string, int> insertion_order;
  // Go through all maps at an index.
  //

  int curr = 0;
  int curr_start = 0;
  int order = 1;

  for (int i = 0; i < rows[0].length(); i++) {
    char c = rows[0][i];
    if (c == ',') {
      curr = 0;
      curr_start = i + 1;
    }
    if (c == '\0' || c == '\n' || c == ',') {
      continue;
    }
    if (c == '=') {
      string label = rows[0].substr(curr_start, i - curr_start);
      hashmap[curr][label] = rows[0][i + 1] - '0';
      if (insertion_order[label] == 0 || insertion_order[label] == -1) {
        insertion_order[label] = order;
      }
      order++;
      i++;
    } else if (c == '-') {
      string label = rows[0].substr(curr_start, i - curr_start);
      hashmap[curr][label] = 0;
      insertion_order[label] = -1;
    } else {
      curr += int(c);
      curr *= 17;
      curr %= 256;
    }
  }

  for (int i = 0; i < 256; i++) {
    // Need to sort lenses by insertion order.
    // Take out zero order.
    map<string, int> lenses = hashmap[i];
    vector<pair<string, int>> lense_strengths;
    for (pair<string, int> lens : lenses) {
      if (lens.second > 0) {
        lense_strengths.push_back(lens);
      }
    }

    sort(lense_strengths.begin(), lense_strengths.end(),
         [&](const pair<string, int> i, const pair<string, int> j) {
           return insertion_order[i.first] < insertion_order[j.first];
         });

    for (int j = 0; j < lense_strengths.size(); j++) {
      // cout << lense_strengths[j].first << "\n";
      // cout << (i + 1) * (j + 1) * lense_strengths[j].second << "\n";
      ans += (i + 1) * (j + 1) * lense_strengths[j].second;
    }
  }

  // int test = 0;
  // for (char c : "rn") {
  //   if (c == '\0' || c == '\n') {
  //     continue;
  //   }
  //   test += int(c);
  //   test *= 17;
  //   test %= 256;
  // }
  // cout << test << "\n";

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
