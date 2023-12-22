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

  // Check in each layer from z=0.
  // Which brick is supporting it
  // And if there are more than one,
  // add support_count - 1 to ans.

  set<tuple<pair<int, int>, pair<int, int>, pair<int, int>>, zCmp> bricks;
  set<tuple<pair<int, int>, pair<int, int>, pair<int, int>>, xCmp> x_bricks;
  // Ignore lower bound of z.
  for (string row : rows) {
    string number = "";

    pair<int, int> x;
    pair<int, int> y;
    pair<int, int> z;

    int i = 0;
    bool second = false;

    vector<pair<int, int>> pos = {x, y, z};

    for (char c : row) {
      if (c == ',' || c == '~') {
        if (second) {
          pos[i % 3].second = stoi(number);
        } else {
          pos[i % 3].first = stoi(number);
        }
        number = "";
        if (c == '~') {
          second = true;
        }
        i++;
      } else {
        number += c;
      }
    }
    pos[i % 3].second = stoi(number);
    bricks.insert({pos[0], pos[1], pos[2]});
    x_bricks.insert({pos[0], pos[1], pos[2]});
  }

  // Ok, great.
  // Now we have found points less than.
  // But how can we ignore if no intersecting x or y?
  // We could move this to the sorting.
  // So, first we sort by z.
  // Then I check if

  set<tuple<pair<int, int>, pair<int, int>, pair<int, int>>>::iterator z_itlow =
      bricks.lower_bound({{1, 1}, {1, 1}, {8, 9}});

  set<tuple<pair<int, int>, pair<int, int>, pair<int, int>>>::iterator x_itlow =
      x_bricks.lower_bound({{1, 1}, {1, 1}, {8, 9}});

  set<tuple<pair<int, int>, pair<int, int>, pair<int, int>>> supporting_bricks;

  while (z_itlow != bricks.begin()) {
    tuple<pair<int, int>, pair<int, int>, pair<int, int>> brick = *z_itlow;
    supporting_bricks.insert(brick);
    --z_itlow;
  }

  cout << supporting_bricks.size() << "\n";

  int count = 0;
  while (x_itlow != x_bricks.begin()) {
    tuple<pair<int, int>, pair<int, int>, pair<int, int>> brick = *x_itlow;

    cout << get<0>(brick).first << "," << get<1>(brick).first << ","
         << get<2>(brick).first << "~";
    cout << get<0>(brick).second << "," << get<1>(brick).second << ","
         << get<2>(brick).second << "\n";

    if (supporting_bricks.find(brick) != supporting_bricks.end()) {
      count++;
    }
    --x_itlow;
  }
  cout << count << "\n";
  // if (z_itlow != bricks.end()) {
  //   cout << get<0>(brick).first << "," << get<1>(brick).first << ","
  //        << get<2>(brick).first << "~";
  //   cout << get<0>(brick).second << "," << get<1>(brick).second << ","
  //        << get<2>(brick).second << "\n";
  //   cout << distance(bricks.begin(), z_itlow) << "\n";
  // }
  //
  // for (tuple<pair<int, int>, pair<int, int>, pair<int, int>> brick : bricks)
  // {
  //   cout << get<0>(brick).first << "," << get<1>(brick).first << ","
  //        << get<2>(brick).first << "~";
  //   cout << get<0>(brick).second << "," << get<1>(brick).second << ","
  //        << get<2>(brick).second << "\n";
  // }

  // Now how to store and process?
  // We want to always order by z.
  // And then by x or y.
  // So we can keep a set of supported for each brick
  // Then take that size -1 to ans instead.
  // So sort by z, binary search among smaller z values,
  // Then binary search among the smaller z values for some brick
  // in same (x,y) range.
  // So if we have first one binary search for z values.
  // Then we binary search on x values to get the ones in range
  // Then finally binary search on y values
  // The result is the count of bricks in the index we find.
  // Since both x and y need to intersect.
  //
  // So what if we then simply sort by z, followed by x and then y?
  // Does it matter if we sort by x and then y and not y and then x?
  // It should not since both need to match anyway.
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
