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

  sort(counter.begin() + 1, counter.end(), greater<>());

  if (counter[1] + counter[0] == 5) {
    return 7;
  }

  if (counter[1] + counter[0] == 4) {
    return 6;
  }

  if ((counter[1] + counter[0] == 3 && counter[2] == 2) ||
      (counter[1] == 3 && counter[2] + counter[0] == 2)) {
    return 5;
  }

  if (counter[1] + counter[0] == 3) {
    return 4;
  }

  if ((counter[1] + counter[0] == 2 && counter[2] == 2) ||
      (counter[1] == 2 && counter[2] + counter[0] == 2)) {
    return 3;
  }

  if (counter[1] + counter[0] == 2) {
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

  ifstream input("input.txt");

  if (input.is_open()) {
    while (getline(input, row)) {
      rows.push_back(row);
    }
    input.close();
  }

  int row_number = 0;
  vector<vector<ll>> hands(rows.size());
  vector<ll> bids;

  // To map the values
  map<char, ll> card_map = {
      {'A', 14}, {'K', 13}, {'Q', 12}, {'J', 0}, {'T', 10}};

  for (string row : rows) {
    // Get number positions
    int num_start = -1;
    int num_end = -1;
    string number = "";
    bool bid = false;

    for (int col = 0; col < row.length(); ++col) {
      if (row[col] == ' ') {
        string hand = row.substr(0, col);
        for (int i = 0; i < hand.length(); i++) {
          ll current_card = 0;
          if (card_map.find(hand[i]) != card_map.end()) {
            current_card = card_map[hand[i]];
          } else {
            current_card = (ll)(hand[i] - '0');
          }
          hands[row_number].push_back(current_card);
        }
        bid = true;
      } else if (bid) {
        if (num_start == -1) {
          num_start = col;
          num_end = col;
        } else {
          num_end++;
        }
        number += row[col];
      }
    }
    if (num_start != -1) {
      ll number_int = stoll(number);
      bids.push_back(number_int);
    }

    row_number++;
  }

  // Keep a map for the bids
  vector<int> pa(bids.size());
  iota(pa.begin(), pa.end(), 0);
  sort(pa.begin(), pa.end(),
       [&](int i, int j) { return rankSorter(hands[i], hands[j]); });

  // Sort the hands
  sort(hands.begin(), hands.end(), rankSorter);

  // Add the score for the hands.
  for (ll i = 1; i <= hands.size(); i++) {
    ans += bids[pa[i - 1]] * i;
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
