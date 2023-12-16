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

  // Simply push all to a vector, take max.

  vector<tuple<int, int, int>> starting_positions;

  for (int direction : {0, 1, 2, 3}) {
    // Push top and bottom
    for (int j = 0; j < m; j++) {
      starting_positions.push_back({0, j, direction});
      starting_positions.push_back({n - 1, j, direction});
    }
    // Push left and right
    for (int i = 0; i < n; i++) {
      starting_positions.push_back({i, 0, direction});
      starting_positions.push_back({i, m - 1, direction});
    }
  }
  map<int, pair<int, int>> directions = {
      {0, {0, 1}}, {1, {0, -1}}, {2, {-1, 0}}, {3, {1, 0}}};
  map<int, int> right_mirror = {{0, 2}, {2, 0}, {1, 3}, {3, 1}};
  map<int, int> left_mirror = {{0, 3}, {3, 0}, {1, 2}, {2, 1}};
  vector<string> best_board;

  for (tuple<int, int, int> starting_position : starting_positions) {
    queue<tuple<int, int, int>> q;
    unordered_set<tuple<int, int, int>, hash_triplet> visited_squares;
    q.push(starting_position);
    visited_squares.insert(starting_position);

    unordered_set<pair<int, int>, hash_pair> visited;
    ll curr_ans = 0;

    while (!q.empty()) {
      tuple<int, int, int> curr = q.front();
      q.pop();

      pair<int, int> coord = {get<0>(curr), get<1>(curr)};

      if (visited.find(coord) == visited.end()) {
        visited.insert(coord);
        curr_ans++;
      }
      int direction = get<2>(curr);
      vector<tuple<int, int, int>> rays;

      // Lets first handle mirrors
      if (rows[coord.first][coord.second] == '/') {
        // 0: 2 right: up
        // 2: 0 up: right
        // 1: 3 left: down
        // 3: 1 down: left
        rays.push_back({coord.first, coord.second, right_mirror[direction]});
      } else if (rows[coord.first][coord.second] == '\\') {
        // 0: 3 right:down
        // 3: 0 down: right
        // 1: 2 left: up
        // 2: 1 up: left
        rays.push_back({coord.first, coord.second, left_mirror[direction]});
      } else if (rows[coord.first][coord.second] == '-') {
        // if direction == 2 or 3
        // Now direction = 0 and 1
        if (direction == 2 || direction == 3) {
          rays.push_back({coord.first, coord.second, 0});
          rays.push_back({coord.first, coord.second, 1});
        } else {
          rays.push_back(curr);
        }
      } else if (rows[coord.first][coord.second] == '|') {
        // if direction is 0 or 1
        // Now 2 and 3
        if (direction == 0 || direction == 1) {
          rays.push_back({coord.first, coord.second, 2});
          rays.push_back({coord.first, coord.second, 3});
        } else {
          rays.push_back(curr);
        }
      } else {
        rays.push_back(curr);
      }

      for (tuple<int, int, int> ray : rays) {
        pair<int, int> ray_coord = {get<0>(ray), get<1>(ray)};
        int ray_direction = get<2>(ray);
        pair<int, int> change = directions[ray_direction];
        pair<int, int> new_coord = {ray_coord.first + change.first,
                                    ray_coord.second + change.second};

        if (new_coord.first < n && new_coord.second < m &&
            new_coord.first >= 0 && new_coord.second >= 0) {
          if (visited_squares.find({new_coord.first, new_coord.second,
                                    ray_direction}) == visited_squares.end()) {
            q.push({new_coord.first, new_coord.second, ray_direction});
            visited_squares.insert(
                {new_coord.first, new_coord.second, ray_direction});
          }
        }
      }
    }
    if (curr_ans > ans) {
      ans = curr_ans;
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
