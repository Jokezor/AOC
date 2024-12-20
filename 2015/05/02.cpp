#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <regex>
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

struct Point {
  int x, y;
};

struct line {
  Point p1, p2;
};

bool onLine(line l1, Point p) {
  if ((p.x <= max(l1.p1.x, l1.p2.x) && p.x >= min(l1.p1.x, l1.p2.x)) &&
      (p.y <= max(l1.p1.y, l1.p2.y) && p.y >= min(l1.p1.y, l1.p2.y))) {
    return true;
  }
  cout << p.x << "\n";
  cout << max(l1.p1.x, l1.p2.x) << "\n";
  cout << min(l1.p1.x, l1.p2.x) << "\n";
  cout << "whoo\n";
  return false;
}

int direction(Point a, Point b, Point c) {
  int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

  // collinear
  if (val == 0) {
    return 0;
  }
  // anti clocwise
  else if (val < 0) {
    return 2;
  }

  // clockwise
  return 1;
}

bool isIntersect(line l1, line l2) {
  // Four direction for two lines and points of other line
  int dir1 = direction(l1.p1, l1.p2, l2.p1);
  int dir2 = direction(l1.p1, l1.p2, l2.p2);
  int dir3 = direction(l2.p1, l2.p2, l1.p1);
  int dir4 = direction(l2.p1, l2.p2, l1.p2);

  // When intersecting
  if (dir1 != dir2 && dir3 != dir4)
    return true;

  // When p2 of line2 are on the line1
  if (dir1 == 0 && onLine(l1, l2.p1))
    return true;

  // When p1 of line2 are on the line1
  if (dir2 == 0 && onLine(l1, l2.p2))
    return true;

  // When p2 of line1 are on the line2
  if (dir3 == 0 && onLine(l2, l1.p1))
    return true;

  // When p1 of line1 are on the line2
  if (dir4 == 0 && onLine(l2, l1.p2))
    return true;

  return false;
}

bool inside(vector<Point> poly, int n, Point p) {
  if (n < 3) {
    return false;
  }

  line exline = {p, {9999, p.y}};
  int count = 0;
  int i = 0;

  do {

    // Forming a line from two consecutive points of
    // poly
    line side = {poly[i], poly[(i + 1) % n]};
    cout << p.x << ":" << p.y << "; ";
    if (isIntersect(side, exline)) {
      cout << count << " ";

      // If side is intersects exline
      if (direction(side.p1, p, side.p2) == 0)
        return onLine(side, p);
      count++;
    }
    i = (i + 1) % n;
  } while (i != 0);

  cout << "nope\n";
  return count & 1;
}

struct Part {
  int x, m, a, s;
};

struct zCmp {
  bool operator()(
      const tuple<pair<int, int>, pair<int, int>, pair<int, int>> &brick_1,
      const tuple<pair<int, int>, pair<int, int>, pair<int, int>> &brick_2)
      const {

    if (get<2>(brick_1).second == get<2>(brick_2).second) {
      if (get<0>(brick_1).second == get<0>(brick_2).second) {
        return get<1>(brick_1).second < get<1>(brick_2).second;
      }
      return get<0>(brick_1).second < get<0>(brick_2).second;
    }

    return get<2>(brick_1).second < get<2>(brick_2).second;
  }
};

struct xCmp {
  bool operator()(
      const tuple<pair<int, int>, pair<int, int>, pair<int, int>> &brick_1,
      const tuple<pair<int, int>, pair<int, int>, pair<int, int>> &brick_2)
      const {

    return ((get<0>(brick_1).first <= get<0>(brick_2).first) &&
            (get<0>(brick_1).second >= get<0>(brick_2).first)) ||
           ((get<0>(brick_1).first <= get<0>(brick_2).second) &&
            (get<0>(brick_1).second >= get<0>(brick_2).second));
  }
};

bool isNiceString(string s) {
  bool repeated_letter = false;
  bool two_pair = false;

  for (int i =1; i < s.length()-1; ++i) {
    if (s[i-1] == s[i+1]) {
      repeated_letter = true;
      break;
    }
  }

  // Push each index of pairs.
  unordered_map<string, ll> pairs;

  // Instead push all letters.
  // Record positions in the string

  for (int i=0; i < s.length()-1; i++) {
    string candidate = s.substr(i, 2);
    auto rev_candidate = candidate | std::views::reverse;
    string reversed_string{begin(rev_candidate), end(rev_candidate)};

    if (pairs.find(candidate) != pairs.end()) {
      // Need to be non overlapping.
      if ((i - pairs[candidate]) >= 2) {
        two_pair = true;
        break;
      }
    }
    pairs[candidate] = i;
    pairs[reversed_string] = i;
  }

  cout << (two_pair && repeated_letter) << "\n";

  return (repeated_letter && two_pair);
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

  for (string row : rows) {
    cout << row << "\n";
    ans += isNiceString(row);
  }

  printf("%lld\n", ans);
}

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  int t = 1;

  while (t--)
    solution();

  return 0;
}
