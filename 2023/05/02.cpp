#include <bits/stdc++.h>
#include <fstream>
#include <string>

#define ll long long

using namespace std;

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
  ll ans = 9999999999999;

  vector<string> rows;

  ifstream input("input.txt");

  if (input.is_open()) {
    while (getline(input, row)) {
      rows.push_back(row);
    }
    input.close();
  }

  int row_number = 0;

  vector<ll> seeds;

  // Instead of simply having seeds, make pairs
  map<ll, ll> seed_maps;

  string type = "seeds";
  vector<vector<vector<ll>>> maps(7);
  int map_index = -1;

  for (string row : rows) {
    // Get number positions
    int num_start = -1;
    int num_end = -1;
    string number = "";

    if (row.find("map:") != std::string::npos) {
      type = "map";
    };

    // Simply process directly.
    vector<ll> current_map;
    if (row.find("map:") != string::npos) {
      map_index++;
    }

    for (int col = 0; col < row.length(); ++col) {
      if (row[col] - '0' >= 0 && '9' - row[col] >= 0) {
        if (num_start == -1) {
          num_start = col;
          num_end = col;
        } else {
          num_end++;
        }
        number += row[col];
      } else {
        // Check if there was a num, add it.
        if (num_start != -1) {
          ll number_int = stoll(number);
          if (type == "seeds") {
            seeds.push_back(number_int);
          } else {
            current_map.push_back(number_int);
          }
        }
        num_start = -1;
        num_end = -1;
        number = "";
      }
    }
    if (num_start != -1) {
      ll number_int = stoll(number);
      if (type == "seeds") {
        seeds.push_back(number_int);
      } else {
        current_map.push_back(number_int);
      }
    }
    if (type != "seeds" && current_map.size() > 0) {
      maps[map_index].push_back(current_map);
    }

    row_number++;
  }

  // Add default
  for (int i = 0; i < seeds.size(); i += 2) {
    ll initial_seed = seeds[i];
    ll seed_range = seeds[i + 1];
    seed_maps[initial_seed] = seed_range;
  }

  // Check all seeds.
  for (int i = 0; i < 7; i++) {
    vector<vector<ll>> current_maps = maps[i];
    map<ll, ll> new_map;

    // What if we did a vector seed_maps? Its to allow
    // us to add skipped regions.
    // Second thinking is to have a vector of maps
    // To keep track of start and end of the range.
    // Now I only have start and range.
    // When I map only the middle: 1,2,[3,4],5,6
    // How can I update it?
    // One way is to push them to a temporary vector
    // Like so:
    // For count below: We push seed_start: count_below
    // For count above: We push seed_max - count_above: count_above
    // Resulting in:
    // [{0, 2}, {4, 2}]
    // Then we essentially do a while stack:
    // seed_map = stack.top()
    // stack.pop()
    // And then check the seeds for that popped seed_map etc.
    // Then I do not need to push them separately to the new_map.
    // It will be done if they found no mapping of their own.
    for (pair<ll, ll> source_seed_map : seed_maps) {

      stack<pair<ll, ll>> seed_stack;

      seed_stack.push(source_seed_map);
      ll source_seed_range = source_seed_map.second;
      set<pair<ll, ll>> unmatched_seeds;

      while (!seed_stack.empty()) {
        pair<ll, ll> seed_map = seed_stack.top();
        seed_stack.pop();
        ll seed_start = seed_map.first;
        ll seed_range = seed_map.second;
        ll seed_max = max(seed_start, seed_start + seed_range - 1);

        for (vector<ll> current_map : current_maps) {
          ll destination_start = current_map[0];
          ll source_start = current_map[1];
          ll source_range = current_map[2];
          ll source_max = max(source_start, source_start + source_range - 1LL);
          ll diff = destination_start - source_start;

          ll count_above = max(seed_max - source_max, 0LL);
          ll count_below = max(source_start - seed_start, 0LL);

          ll range_to_include = seed_range - (count_above + count_below);

          if (seed_max < source_start || seed_start > source_max) {
            continue;
          }

          // Remove the tops into a new seed range
          if (count_above > 0) {
            seed_stack.push({(seed_max - count_above) + 1LL, count_above});
          }
          // Remove the bottoms into a new seed range
          if (count_below > 0) {
            seed_stack.push({seed_start, count_below});
          }

          if (range_to_include > 0) {
            new_map[seed_start + diff + count_below] =
                max(new_map[seed_start + diff + count_below], range_to_include);
            source_seed_range -= range_to_include;
            seed_range -= range_to_include;
          }
        }
        if (seed_range > 0) {
          unmatched_seeds.insert({seed_start, seed_range});
        }
      }
      if (source_seed_range > 0) {
        for (pair<ll, ll> unmatched_seed : unmatched_seeds) {
          new_map[unmatched_seed.first] = unmatched_seed.second;
        }
      }
    }
    // Add in new map
    if (!new_map.empty()) {
      seed_maps = new_map;
    }
  }

  for (auto seed_map : seed_maps) {
    ans = min(ans, seed_map.first);
  }

  cout << ans << "\n";
}

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  int t = 1;

  while (t--)
    solution();

  return 0;
}
