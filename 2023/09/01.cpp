#include <bits/stdc++.h>
#include <fstream>
#include <string>

#define ll long long

using namespace std;

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

vector<int> diff_array(vector<int> arr) {
  vector<int> diff;

  for (int i = 0; i < arr.size() - 1; i++) {
    diff.push_back(arr[i + 1] - arr[i]);
  }

  return diff;
}

// Essentially, recursively call diff until 0.
int get_next(vector<int> arr, int prev) {
  vector<int> new_arr;
  for (int i = 0; i < arr.size() - 1; i++) {
    if (arr[i] != arr[i + 1]) {
      new_arr = get_next(arr, arr[arr.size() - 1]);
    }
  }
  return prev + if () {}
}

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

  // Essentially build a graph with left and right.
  // Easiest is to have a map to a pair.

  int row_number = 0;

  for (int i = 0; i < rows.size(); i++) {
    string num = "";

    string row = rows[i];
    vector<int> num_row;

    for (char c : row) {
      if (c != ' ') {
        num += c;
      } else {
        num_row.push_back(stoi(num));
        num = "";
      }
    }
    num_row.push_back(stoi(num));

    int diff = num_row[1] - num_row[0];
    cout << diff << "\n";
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
