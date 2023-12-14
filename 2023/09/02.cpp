#include <bits/stdc++.h>
#include <fstream>
#include <string>

#define ll long long

using namespace std;

ll gcd(ll x, ll y) {
  if (y) {
    return gcd(y, x % y);
  } else {
    return x;
  }
}

ll lcm(ll x, ll y) { return (x / gcd(x, y)) * y; }

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

void solution() {
  string row;
  ll ans = 999999999999999;

  vector<string> rows;

  ifstream input("input.txt");

  if (input.is_open()) {
    while (getline(input, row)) {
      rows.push_back(row);
    }
    input.close();
  }

  // Start at nodes ending with A
  // End if all nodes end with A

  int row_number = 0;
  map<string, pair<string, string>> graph;

  string instructions = rows[0];

  for (int i = 2; i < rows.size(); i++) {
    string row = rows[i];
    string source_node;
    string left_node;
    string right_node;

    for (int col = 0; col < row.length(); ++col) {
      if (row[col] == '=') {
        source_node = row.substr(0, 3);
      }
      if (row[col] == ',') {
        left_node = row.substr(col - 3, 3);
        right_node = row.substr(col + 2, 3);
      }
    }
    graph[source_node] = {left_node, right_node};

    row_number++;
  }

  vector<string> search_nodes;
  vector<pair<string, string>> search_nodes_path;

  for (auto node : graph) {
    if (node.first[2] == 'A') {
      search_nodes.push_back(node.first);
      search_nodes_path.push_back(node.second);
    } else if (node.first[2] == 'Z') {
      cout << node.first << "\n";
    }
  }

  vector<set<ll>> cycles(search_nodes.size());

  ll n = search_nodes.size();

  // Find no Z in a whole cycle.
  // Which means that I probably end prematurely

  // Search until all nodes are final nodes
  for (int i = 0; i < n; i++) {
    // How to know if I have catched a cycle?
    // 1. We need to have passed all instructions
    // 2. The starting node is the same as the original starting node.
    //
    // So essentially check until we are back at start node
    // With a whole new instruction to parse.
    // Then we know we are at the end.
    // But it might be a cycle in the middle etc.
    //
    // So we should track all the start_nodes we have searched.
    set<string> searched_nodes;
    vector<string> tracked_nodes;
    string current_node = search_nodes[i];
    pair<string, string> search_node_path = search_nodes_path[i];
    ll steps = 0;

    while (searched_nodes.find(current_node) == searched_nodes.end()) {
      searched_nodes.insert(current_node);
      for (char c : instructions) {
        // We insert current here to mark this is being searched.
        if (c == 'L') {
          current_node = search_node_path.first;
        } else if (c == 'R') {
          current_node = search_node_path.second;
        }
        search_node_path = graph[current_node];
        steps++;
        if (current_node[2] == 'Z') {
          cycles[i].insert(steps);
        }
      }
    }
  }

  // Now take the smallest from each cycle
  // And take the lcm.
  for (int i = 0; i < cycles.size(); i++) {
    set<ll> cycle = cycles[i];
    ll steps = 0;
    for (ll ind : cycle) {
      steps = ind;
      // Should check how many we found.
      // We should not include none found.
      // Binary search for the next
      int j = 0;
      for (; j < cycles.size(); j++) {
        if (i != j) {
          set<ll>::iterator itlow = cycles[j].lower_bound(ind);
          if (itlow != cycles[j].end()) {
            steps = lcm(*itlow, steps);
          } else {
            break;
          }
        }
      }
      // Reached all
      if (j == cycles.size()) {
        ans = min(ans, steps);
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
