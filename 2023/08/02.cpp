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
    }
  }
  ll final_nodes = 0;

  // Search until all nodes are final nodes
  while (final_nodes != search_nodes.size()) {
    for (char c : instructions) {
      ll current_final_nodes = 0;
      // Print out to see what cycles are being repeated.
      // There should be a solution, so should not see the same
      // nodes repeated over and over.
      for (int i = 0; i < search_nodes.size(); i++) {
        if (c == 'L') {
          search_nodes[i] = search_nodes_path[i].first;
        } else if (c == 'R') {
          search_nodes[i] = search_nodes_path[i].second;
        }
        search_nodes_path[i] = graph[search_nodes[i]];
        if (search_nodes[i][2] == 'Z') {
          current_final_nodes++;
        }
      }
      ans++;
      if (current_final_nodes == search_nodes.size()) {
        final_nodes = current_final_nodes;
        break;
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
