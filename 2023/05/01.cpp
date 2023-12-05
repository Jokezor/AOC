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
  ll ans = 99999999999;

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

  // I feel tempted to use the same map.
  // And just process as we go.
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
  for (ll seed : seeds) {
    seed_maps[seed] = seed;
  }

  // Check all seeds.
  for (int i = 0; i < maps.size(); i++) {
    vector<vector<ll>> current_maps = maps[i];
    map<ll, ll> new_map(seed_maps);

    for (vector<ll> current_map : current_maps) {
      for (auto seed_map : seed_maps) {
        ll key = seed_map.first;
        ll value = seed_map.second;
        ll destination_start = current_map[0];
        ll source_start = current_map[1];
        ll range = current_map[2];

        // cout << destination_start << ", " << source_start << ", " << range
        //      << "\n";

        if (value >= source_start && value < (source_start + range)) {
          new_map[key] = destination_start + (value - source_start);
          // cout << key << ": " << destination_start + (value - source_start)
          //      << "\n";
        }
      }
    }
    // Add in new map
    seed_maps = new_map;
  }

  for (auto seed_map : seed_maps) {
    ans = min(ans, (ll)seed_map.second);
    // cout << seed_map.second << "\n";
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
