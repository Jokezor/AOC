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

  // Sounds like finite state machine
  // Push these elements into a vector if complete.
  // Then we can simply go through and sum them.

  bool is_part = false;
  vector<map<char, int>> parts;

  regex pattern(
      "([a-zA-Z]+)\\{(([x,m,a,s][<>][0-9]+:[a-zA-Z]+,?)+[a-zA-Z]+)\\}");

  map<string, string> rules;

  for (string row : rows) {
    smatch match;

    if (row == "") {
      continue;
    }

    if (regex_match(row, match, pattern)) {
      rules[match[1]] = match[2];
    } else {

      int x_pos = row.find("x=");
      int m_pos = row.find("m=");
      int a_pos = row.find("a=");
      int s_pos = row.find("s=");

      int x = stoi(row.substr(x_pos + 2, m_pos - x_pos - 1));
      int m = stoi(row.substr(m_pos + 2, a_pos - m_pos - 1));
      int a = stoi(row.substr(a_pos + 2, s_pos - a_pos - 1));
      int s = stoi(row.substr(s_pos + 2, s_pos - row.length()));

      parts.push_back({{'x', x}, {'m', m}, {'a', a}, {'s', s}});
    }
  }

  // cout << rules["qqz"].substr(rules["qqz"].rfind(',') + 1,
  //                             rules["qqz"].length() -
  //                             rules["qqz"].rfind(','));
  vector<int> good_parts;

  for (int i = 0; i < parts.size(); i++) {
    map<char, int> part = parts[i];

    string current = "in";

    while (true) {
      string start_workflow = current;
      string rule = rules[current];

      int start = 0;
      string fallback_rule =
          rule.substr(rule.rfind(',') + 1, rule.length() - rule.rfind(','));
      rule = rule.substr(0, rule.rfind(','));

      while (start < rule.length()) {
        string sub_rule = rule.substr(start, rule.length() - start);

        char rating = sub_rule[0];
        char comparitor = sub_rule[1];
        int check = stoi(sub_rule.substr(2, sub_rule.find(':') - 2));
        string next_rule =
            sub_rule.substr(sub_rule.find(':') + 1,
                            sub_rule.find(',') - sub_rule.find(':') - 1);

        start += (sub_rule.find(':') + 1) + next_rule.length() + 1;

        // cout << check << " "
        //      << " " << sub_rule << " " << next_rule << "\n";

        if (comparitor == '>') {
          if (part[rating] > check) {
            current = next_rule;
            break;
          }
        } else {
          if (part[rating] < check) {
            current = next_rule;
            break;
          }
        }
      }

      if (fallback_rule == "") {
        cout << fallback_rule << "\n";
        cout << rule << "\n";
        cout << start_workflow << "\n";
        return;
      }
      // cout << current << "\n";
      if (current == start_workflow) {
        current = fallback_rule;
      }

      if (current == "A") {
        int part_ans = part['x'] + part['m'] + part['a'] + part['s'];
        cout << part_ans << "\n";
        ans += part_ans;
        good_parts.push_back(i);
        break;
      } else if (current == "R") {
        break;
      }
    }
  }

  cout << good_parts.size() << "\n";

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
