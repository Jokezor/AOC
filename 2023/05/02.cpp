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

    if (row.find("seed-to-soil") != std::string::npos) {
      type = "seed-to-soil";
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
  // cout << "original:"
  //      << "\n";
  for (int i = 0; i < seeds.size(); i += 2) {
    ll initial_seed = seeds[i];
    ll seed_range = seeds[i + 1];
    seed_maps[initial_seed] = seed_range;
    // cout << initial_seed << ":" << seed_range << "\n";
  }
  // cout << "\n\n";

  // Check all seeds.
  for (int i = 0; i < 7; i++) {
    vector<vector<ll>> current_maps = maps[i];
    map<ll, ll> new_map;

    // cout << i << "\n\n\n";
    for (auto seed_map : seed_maps) {
      ll seed_start = seed_map.first;
      ll seed_range = seed_map.second;
      ll seed_max = seed_start + seed_range - 1;
      set<ll> matched_seeds;

      // cout << seed_map.first << ":" << seed_map.second << "\n";

      for (vector<ll> current_map : current_maps) {
        ll destination_start = current_map[0];
        ll source_start = current_map[1];
        ll source_range = current_map[2];
        ll source_max = source_start + source_range - 1LL;
        ll diff = destination_start - source_start;

        ll count_above = max(seed_max - source_max, 0LL);
        ll count_below = max(source_start - seed_start, 0LL);

        ll range_to_include = seed_range;

        if (seed_max < source_start || seed_start > source_max) {
          continue;
        }

        // Remove the tops into a new seed range
        if (count_above > 0) {
          range_to_include -= count_above;
          new_map[(seed_max - count_above) + 1] =
              max(new_map[(seed_max - count_above) + 1], count_above);
          matched_seeds.insert(seed_start);
        }
        // Remove the bottoms into a new seed range
        if (count_below > 0) {
          range_to_include -= count_below;
          new_map[seed_start] = max(new_map[seed_start], count_below);
          matched_seeds.insert(seed_start);
        }

        if (range_to_include > 0) {
          new_map[seed_start + diff + count_below] =
              max(new_map[seed_start + diff + count_below], range_to_include);
          matched_seeds.insert(seed_start);
        }
      }
      if (matched_seeds.find(seed_start) == matched_seeds.end()) {
        new_map[seed_start] = max(new_map[seed_start], seed_range);
      }
    }
    // Add in new map
    seed_maps = new_map;
  }

  cout << "final: \n\n";
  for (auto seed_map : seed_maps) {
    ans = min(ans, seed_map.first);
    cout << seed_map.first << ":" << seed_map.second << "\n";
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
