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

vector<ll> diff_array(vector<ll> arr) {
  vector<ll> diff;

  for (int i = 0; i < arr.size() - 1; i++) {
    diff.push_back(arr[i + 1] - arr[i]);
  }

  return diff;
}

// Essentially, recursively call diff until 0.
ll get_next(vector<ll> arr, ll prev) {
  if (arr.size() <= 1) {
    return 0;
  }
  ll result = prev;
  vector<ll> new_arr = diff_array(arr);

  int i = 0;
  for (; i < new_arr.size(); i++) {
    if (new_arr[i] != 0) {
      break;
    }
  }
  if (i < new_arr.size()) {
    result += get_next(new_arr, new_arr[new_arr.size() - 1]);
  }
  return result;
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

  map<char, vector<pair<int, int>>> pipes = {
      {'|', {{1, 0}, {-1, 0}}}, {'-', {{0, 1}, {0, -1}}},
      {'L', {{-1, 0}, {0, 1}}}, {'J', {{-1, 0}, {0, -1}}},
      {'7', {{1, 0}, {0, -1}}}, {'F', {{1, 0}, {0, 1}}},
  };

  // If we see a | then connect the grid.
  // So lets do a map from coordinate to connections
  unordered_map<pair<int, int>, set<pair<int, int>>, hash_pair> graph;

  // Stores the potential paths
  map<pair<int, int>, vector<pair<int, int>>> candidates;
  pair<int, int> start;

  for (int i = 0; i < rows.size(); i++) {
    string row = rows[i];
    for (int j = 0; j < row.length(); j++) {
      if (row[j] == 'S') {
        start = {i, j};
      }
      // cout << "On: " << i << " " << j << "\n";
      for (pair<int, int> pipe : pipes[row[j]]) {
        if (i + pipe.first < rows.size() &&
            j + pipe.second < rows[i].length()) {
          pair<int, int> potential_candidate = {i + pipe.first,
                                                j + pipe.second};
          candidates[potential_candidate].push_back({i, j});

          for (pair<int, int> candidate : candidates[{i, j}]) {
            // cout << candidate.first << ": " << candidate.second << "\n";
            // cout << "Potential candidate: " << potential_candidate.first << "
            // "
            //      << potential_candidate.second << "\n";
            if (candidate == potential_candidate) {
              // cout << "wooh";
              graph[{i, j}].insert(potential_candidate);
              graph[potential_candidate].insert({i, j});
            }
          }
        }
      }
    }
  }

  // Example 1 should return 1.
  // Find enclosed tiles.
  // Scan from [0,0] to [n-1, m-1]
  // Check if the position is visited.
  // If not, then check that all 8 corners
  // Are either visited or if to the left:
  // The left one needs its NW, W, SW protected.
  // So for each node that we find, store that they
  // Check out. Then essentially queue up their neighbours for checking.
  // So I would queue up all nodes inside.
  // So from [0, 0] to [n-1, m-1] queue up all non visited neighbours
  //

  bool found = false;
  char loop_pipe = '.';
  for (char start_pipe : "F|-LJ7") {
    // Add both pipes, then traverse only in one direction.
    auto graph_copy = graph;
    for (pair<int, int> pipe : pipes[start_pipe]) {
      if (start.first + pipe.first < rows.size() &&
          start.second + pipe.second < rows[0].length()) {
        pair<int, int> potential_candidate = {start.first + pipe.first,
                                              start.second + pipe.second};
        for (pair<int, int> candidate :
             candidates[{start.first, start.second}]) {
          // cout << candidate.first << ": " << candidate.second << "\n";
          // cout << "Potential candidate: " << potential_candidate.first << "
          // "
          //      << potential_candidate.second << "\n";
          if (candidate == potential_candidate) {
            // cout << "wooh";
            graph_copy[{start.first, start.second}].insert(potential_candidate);
            // Might need to add all pipes, then search
            graph_copy[potential_candidate].insert({start.first, start.second});
          }
        }
      }
    }
    for (pair<int, int> pipe : pipes[start_pipe]) {
      if (start.first + pipe.first < rows.size() &&
          start.second + pipe.second < rows[0].length()) {

        auto local_graph_copy = graph_copy;
        queue<tuple<int, int, int>> q;
        unordered_set<pair<int, int>, hash_pair> visited;

        pair<int, int> potential_candidate = {start.first + pipe.first,
                                              start.second + pipe.second};
        q.push({potential_candidate.first, potential_candidate.second, 0LL});
        visited.insert(potential_candidate);
        // cout << potential_candidate.first << ";" <<
        // potential_candidate.second
        //      << "\n";

        // Remove the start from neighbours
        local_graph_copy[potential_candidate].erase(start);

        while (!q.empty()) {
          tuple<int, int, ll> current_node = q.front();
          q.pop();
          ll distance = get<2>(current_node);

          pair<int, int> current = {get<0>(current_node), get<1>(current_node)};

          for (pair<int, int> neighbour : local_graph_copy[current]) {
            if (neighbour == start) {
              cout << current.first << " - " << current.second << "\n";
              found = true;
            }
            if (visited.find(neighbour) == visited.end()) {
              visited.insert(neighbour);
              q.push({neighbour.first, neighbour.second, distance + 1LL});
            }
          }
        }
        if (found) {
          loop_pipe = start_pipe;
          cout << loop_pipe << "\n";
          break;
        }
      }
      if (found) {
        break;
      }
    }
    if (found) {
      break;
    }
  }

  queue<tuple<int, int, int>> q;
  auto graph_copy = graph;

  for (pair<int, int> pipe : pipes[loop_pipe]) {
    if (start.first + pipe.first < rows.size() &&
        start.second + pipe.second < rows[0].length()) {
      pair<int, int> potential_candidate = {start.first + pipe.first,
                                            start.second + pipe.second};
      graph_copy[start].insert(potential_candidate);
      graph_copy[potential_candidate].insert(start);
    }
  }
  q.push({start.first, start.second, 0LL});
  unordered_set<pair<int, int>, hash_pair> visited;
  visited.insert(start);

  while (!q.empty()) {
    tuple<int, int, ll> current_node = q.front();
    q.pop();
    ll distance = get<2>(current_node);

    ans = max(ans, distance);

    pair<int, int> current = {get<0>(current_node), get<1>(current_node)};
    // cout << "{" << current.first << ", " << current.second << "}: " <<
    // distance
    //      << "\n";

    for (pair<int, int> neighbour : graph_copy[current]) {
      if (visited.find(neighbour) == visited.end()) {
        visited.insert(neighbour);
        q.push({neighbour.first, neighbour.second, distance + 1LL});
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
