#include <bits/stdc++.h>
#include <fstream>
#include <queue>
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

struct hash_4_tuple {
  template <class T1, class T2, class T3, class T4>
  size_t operator()(const tuple<T1, T2, T3, T4> &p) const {
    auto hash1 = hash<T1>{}(get<0>(p));
    auto hash2 = hash<T2>{}(get<1>(p));
    auto hash3 = hash<T3>{}(get<2>(p));
    auto hash4 = hash<T4>{}(get<3>(p));

    size_t seed = 0;
    seed ^= hash1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash4 + 0x9e3779b9 + (seed << 6) + (seed >> 2);

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
  ll ans = 9999999;

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

  ll dp[n][m];
  unordered_map<tuple<ll, ll, ll, ll>, ll, hash_4_tuple> positions;

  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      dp[i][j] = rows[i][j] - '0';
    }
  }

  int directions[4] = {0, 1, 2, 3};
  map<ll, vector<ll>> direction_map = {
      {0, {0, 2, 3}}, {1, {1, 2, 3}}, {2, {0, 1, 2}}, {3, {0, 1, 3}}};
  map<ll, pair<ll, ll>> direction_walk = {
      {0, {0, 1}}, {1, {0, -1}}, {2, {-1, 0}}, {3, {1, 0}}};

  // Exhaustive search
  for (ll direction : directions) {
    priority_queue<tuple<ll, ll, ll, ll, ll>, deque<tuple<ll, ll, ll, ll, ll>>,
                   greater<tuple<ll, ll, ll, ll, ll>>>
        q;

    unordered_set<tuple<ll, ll, ll, ll>, hash_4_tuple> visited;

    // 3 moves left in the direction, 0 heat loss
    q.push({0LL, 0, 0, direction, 3});
    visited.insert({0, 0, direction, 3});

    while (!q.empty()) {
      tuple<ll, ll, ll, ll, ll> curr = q.top();
      q.pop();

      ll curr_length = get<0>(curr);
      ll x = get<1>(curr);
      ll y = get<2>(curr);
      ll direction = get<3>(curr);
      ll direction_moves = get<4>(curr);

      if (x == n - 1 && y == m - 1) {
        cout << curr_length << "\n";
        break;
      }

      // cout << x << ":" << y << "\n";
      // cout << direction << "\n";

      // Take each possible direction from current
      for (ll possible_direction : direction_map[direction]) {
        ll possible_direction_moves = 3;
        if (direction == possible_direction) {
          possible_direction_moves = direction_moves - 1;
        }
        pair<ll, ll> walk = direction_walk[possible_direction];

        if ((x + walk.first < 0 || x + walk.first >= n) ||
            (y + walk.second < 0 || y + walk.second >= m)) {
          continue;
        }
        tuple<ll, ll, ll, ll, ll> pos = {
            curr_length + dp[x + walk.first][y + walk.second], x + walk.first,
            y + walk.second, possible_direction, possible_direction_moves};

        if (possible_direction_moves > 0LL) {
          tuple<ll, ll, ll, ll> pos_map = {get<1>(pos), get<2>(pos),
                                           get<3>(pos), get<4>(pos)};
          if (positions[pos_map] == 0LL || positions[pos_map] > get<0>(pos)) {
            q.push(pos);
            positions[pos_map] = (ll)get<0>(pos);
            // cout << get<4>(pos) << "\n";
          }
        }
      }
    }
  }

  for (int direction : directions) {
    for (int i = 0; i < 4; i++) {
      if (positions[{n - 1, m - 1, direction, i}] > 0) {
        ans = min(ans, positions[{n - 1, m - 1, direction, i}]);
      }
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
