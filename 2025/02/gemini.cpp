#include <algorithm>
#include <bit>
#include <bits/stdc++.h>
#include <string>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define ll long long
#define all(x) x.begin(), x.end()
#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))

typedef __gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>,
                         __gnu_pbds::rb_tree_tag,
                         __gnu_pbds::tree_order_statistics_node_update>
    ordered_set;

ll MAX_VAL = (ll)(1e9 + 7);
bool USE_TIMER = true;

class ScopedTimer {
public:
  using ClockType = std::chrono::steady_clock;
  ScopedTimer(const char *func)
      : function_name_{func}, start_{ClockType::now()} {}
  ~ScopedTimer() {
    using namespace std::chrono;
    auto stop = ClockType::now();
    auto duration = (stop - start_);
    auto ms = duration_cast<microseconds>(duration).count();
    if (USE_TIMER) std::cout << ms << " microseconds " << function_name_ << '\n';
  }
private:
  const char *function_name_{};
  const ClockType::time_point start_{};
};

struct SafeHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        x = x ^ (x >> 31);
        return x;
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


// usage:
//unordered_map<long long, long long, SafeHash> mp;
//mp.reserve(2 * n);
//mp.max_load_factor(0.7);

class UnionFind {
public:
  int size;
  vector<int> parent;
  vector<int> rank;

  UnionFind(int n) : size(n), parent(n), rank(n, 0) {
      iota(parent.begin(), parent.end(), 0);
  }
  // Added constructor for convenience inside template
  
  void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
  }

  int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
  }

  void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (rank[a] < rank[b]) swap(a, b);
      parent[b] = a;
      if (rank[a] == rank[b]) rank[a]++;
    }
  }
  bool is_connected(int a, int b) { return parent[a] == parent[b]; }
};

// --- Math Utils ---

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
int lcm(int x, int y) { return (x / gcd(x, y)) * y; }

// Binary Exponentiation (Added to template)
ll power(ll base, ll exp) {
    ll res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) res *= base;
        base *= base;
        exp /= 2;
    }
    return res;
}

// Sum of Arithmetic Progression (Added to template)
// Calculates sum of integers in range [start, end] inclusive
// Uses __int128 to prevent overflow during intermediate mult
ll sum_integers(ll start, ll end) {
    if (start > end) return 0;
    unsigned __int128 count = (unsigned __int128)(end - start + 1);
    unsigned __int128 s = (unsigned __int128)start;
    unsigned __int128 e = (unsigned __int128)end;
    unsigned __int128 total = count * (s + e) / 2;
    return (ll)total;
}

vector<ll> trial_division1(ll n) {
  vector<ll> factorization;
  for (ll d = 2; d * d <= n; d++) {
    while (n % d == 0) {
      factorization.push_back(d);
      n /= d;
    }
  }
  if (n > 1) factorization.push_back(n);
  return factorization;
}

unordered_set<ll> divisors(ll n) {
  unordered_set<ll> divisors;
  for (int i = 1; i <= sqrt(n); i++) {
    if (n % i == 0) {
      divisors.insert(i);
      divisors.insert(n / i);
    }
  }
  return divisors;
}

// --- Geometry / Segment Tree / etc (Preserved) ---
const int maxN = 200013;
int n;
vector<ll> p;
vector<pair<ll, ll>> t(maxN * 4);
int a[maxN + 1];

// --- Input Helpers ---

// Robust split_by using stringstream
vector<string> split_by(string s, char delimiter) {
    vector<string> result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    return result;
}

vector<string> read_input(string file_name) {
  vector<string> rows;
  ifstream input(file_name);
  if (input.is_open()) {
    string row;
    while (getline(input, row)) {
      rows.push_back(row);
    }
    input.close();
  }
  return rows;
}

// --- Part 1 (Simulation) ---

ll part_1(vector<string> rows) {
    if (rows.empty()) return 0;
    ll ans = 0;
    vector<string> id_ranges = split_by(rows[0], ',');

    for (string row : id_ranges) {
        vector<string> id_range = split_by(row, '-');
        ll left = stoll(id_range[0]);
        ll right = stoll(id_range[1]);

        for (ll cur = left; cur <= right; ++cur) {
            string candidate = to_string(cur);
            int n_len = candidate.length();
            if (n_len % 2 == 0) {
                if (candidate.substr(0, n_len/2) == candidate.substr(n_len/2, n_len/2)) {
                    ans += cur;
                }
            }
        }
    }
    return ans;
}

// --- Part 2 (Mathematical / Inclusion-Exclusion) ---

// Calculates the sum of invalid numbers of Length L, with repeating period d,
// that fall within [min_val, max_val]. This is the "Gross" sum.
ll get_gross_sum(int L, int d, ll min_val, ll max_val) {
    // 1. Calculate Multiplier (e.g., L=4, d=2 -> 101)
    ll multiplier = 0;
    ll ten_d = power(10, d);
    ll current_p = 1;
    for (int k = 0; k < L/d; ++k) {
        multiplier += current_p;
        current_p *= ten_d;
    }

    // 2. Define valid seed range for period d (e.g., 10 to 99)
    ll seed_min_natural = power(10, d - 1);
    ll seed_max_natural = power(10, d) - 1;

    // 3. Constrain seeds based on requested value range
    // ceil(min / mul) <= seed <= floor(max / mul)
    ll seed_min_req = (min_val + multiplier - 1) / multiplier; 
    ll seed_max_req = max_val / multiplier;                    

    ll start = max(seed_min_natural, seed_min_req);
    ll end = min(seed_max_natural, seed_max_req);

    if (start > end) return 0;

    return multiplier * sum_integers(start, end);
}

ll solve_range_math(ll range_start, ll range_end) {
    string s_start = to_string(range_start);
    string s_end = to_string(range_end);
    int min_len = s_start.length();
    int max_len = s_end.length();

    ll total_ans = 0;

    // Iterate through length L involved in the range
    for (int L = min_len; L <= max_len; ++L) {
        // Find strict divisors of L (periods)
        vector<int> periods;
        for (int d = 1; d <= L / 2; ++d) {
            if (L % d == 0) periods.push_back(d);
        }
        
        // Memoization for inclusion-exclusion (Möbius Inversion logic)
        // Stores {period, unique_sum}
        vector<pair<int, ll>> net_sums; 

        for (int d : periods) {
            ll gross = get_gross_sum(L, d, range_start, range_end);
            
            // Subtract overlaps from smaller divisors
            ll subtract = 0;
            for (auto& p : net_sums) {
                int prev_d = p.first;
                ll prev_net = p.second;
                if (d % prev_d == 0) {
                    subtract += prev_net;
                }
            }
            
            ll net = gross - subtract;
            net_sums.push_back({d, net});
            total_ans += net;
        }
    }
    return total_ans;
}

ll part_2(vector<string> rows) {
    if (rows.empty()) return 0;
    ll ans = 0;
    vector<string> id_ranges = split_by(rows[0], ',');

    for (string row : id_ranges) {
        vector<string> range_parts = split_by(row, '-');
        ll left = stoll(range_parts[0]);
        ll right = stoll(range_parts[1]);

        ans += solve_range_math(left, right);
    }
    return ans;
}

void solution() {
  ScopedTimer timer{"solution"};
  
  // vector<string> example_input = read_input("example_input.txt");
  vector<string> problem_input = read_input("input.txt");

  // cout << "ex 1: " << part_1(example_input) << "\n";
  // cout << "ex 2: " << part_2(example_input) << "\n";
  
  // cout << "part_1: " << part_1(problem_input) << "\n";
  
  ll ans_2 = part_2(problem_input);
  cout << "part_2: " << ans_2 << "\n";
  
  // assert (ans_2 == 28915664389);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  while (t--) solution();
  return 0;
}
