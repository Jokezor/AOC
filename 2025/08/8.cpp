#include <algorithm>
#include <bit>
#include <bits/stdc++.h>
#include <string>

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

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

#if USE_TIMER
#define MEASURE_FUNCTION()                                                     \
  ScopedTimer timer { __func__ }
#else
#define MEASURE_FUNCTION()
#endif

class ScopedTimer {
public:
  using ClockType = std::chrono::steady_clock;
  ScopedTimer(const char *func)
      : function_name_{func}, start_{ClockType::now()} {}
  ScopedTimer(const ScopedTimer &) = delete;
  ScopedTimer(ScopedTimer &&) = delete;
  auto operator=(const ScopedTimer &) -> ScopedTimer & = delete;
  auto operator=(ScopedTimer &&) -> ScopedTimer & = delete;
  ~ScopedTimer() {
    using namespace std::chrono;
    auto stop = ClockType::now();
    auto duration = (stop - start_);
    auto ms = duration_cast<milliseconds>(duration).count();
    std::cout << ms << " ms " << function_name_ << '\n';
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
  vector<int> set_size;
  vector<int> rank;

  void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
    set_size[v] = 1;
  }

  int find_set(int v) {
    if (v == parent[v]) {
      return v;
    }
    return parent[v] = find_set(parent[v]);
  }

  void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);

    if (a != b) {
      if (rank[a] < rank[b]) {
        swap(a, b);
      }
      parent[b] = a;
      if (rank[a] == rank[b]) {
        rank[a]++;
      }
      set_size[a] += set_size[b];
      set_size[b] = 0;
    }
  }

  bool is_connected(int a, int b) { return parent[a] == parent[b]; }
};



int gcd(int x, int y) {
  if (y) {
    return gcd(y, x % y);
  } else {
    return x;
  }
}

int lcm(int x, int y) { return (x / gcd(x, y)) * y; }

vector<ll> trial_division1(ll n) {
  vector<ll> factorization;

  for (ll d = 2; d * d <= n; d++) {
    while (n % d == 0) {
      factorization.push_back(d);
      n /= d;
    }
  }
  if (n > 1) {
    factorization.push_back(n);
  }
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

ll num_divisors(ll num) {
  ll total = 1;
  for (int i = 2; (ll)i * i <= num; i++) {
    if (num % i == 0) {
      int e = 0;
      do {
        e++;
        num /= i;
      } while (num % i == 0);
      total *= e + 1;
    }
  }
  if (num > 1) {
    total *= 2;
  }
  return total;
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

const int maxN = 200013;
int n;

vector<ll> p;

void sieve_of_eratosthenes(ll n) {
  vector<ll> isPrime(n + 1, true);

  isPrime[0] = isPrime[1] = false;

  for (ll i = 2; i <= n; i++) {
    if (isPrime[i] && i * i <= n) {
      for (ll j = i * i; j <= n; j += i) {
        isPrime[j] = false;
      }
    }
  }

  for (ll i = 0; i < n + 1; i++) {
    if (isPrime[i]) {
      p.push_back(i);
    }
  }
}

void print(auto &&r) {
  std::ranges::for_each(r, [](auto &&i) { std::cout << i << ' '; });
  cout << "\n";
}

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
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

template <class Os, class K> Os &operator<<(Os &os, const std::multiset<K> &v) {
  os << '[' << v.size() << "] {";
  bool o{};
  for (const auto &e : v)
    os << (o ? ", " : (o = 1, " ")) << e;
  return os << " }\n";
}

vector<pair<ll, ll>> t(maxN * 4);
int a[maxN + 1];
// build
void build(int a[], ll v = 1, ll tl = 1, ll tr = n) {
  if (tl == tr) {
    t[v].first = tl;
    t[v].second = tl;
    return;
  }
  ll tm = (tl + tr) >> 1;

  build(a, v * 2, tl, tm);
  build(a, v * 2 + 1, tm + 1, tr);

  auto x = t[2 * v];
  auto y = t[2 * v + 1];

  if (a[x.first] <= a[y.first]) {
    t[v].first = x.first;
  } else {
    t[v].first = y.first;
  }

  if (a[x.second] >= a[y.second]) {
    t[v].second = x.second;
  } else {
    t[v].second = y.second;
  }
}

// update
// void update(ll l, ll r, ll pos, ll i, ll new_val, ll v = 1) {
//   if (l == r) {
//     t[v] = new_val;
//     return;
//   }
//   ll mid = (l + r) >> 1;
//   if (pos <= mid)
//     update(l, mid, pos, i + 1, new_val, 2 * v);
//   else
//     update(mid + 1, r, pos, i + 1, new_val, 2 * v + 1);
//
//   if (i % 2 == 0) {
//     if (N & 1) {
//       t[v] = t[2 * v] | t[2 * v + 1];
//     } else {
//       t[v] = t[2 * v] ^ t[2 * v + 1];
//     }
//   } else {
//     if (N & 1) {
//       t[v] = t[2 * v] ^ t[2 * v + 1];
//     } else {
//       t[v] = t[2 * v] | t[2 * v + 1];
//     }
//   }
// }
//
// // queries
pair<ll, ll> sum(ll l, ll r, ll v = 1, ll L = 1, ll R = n) {
  if (R < l || r < L) {
    return {maxN, 0};
  }
  if (l <= L && R <= r) {
    return t[v];
  }
  ll mid = (L + R) >> 1;

  // cout << "dammn \n";

  auto x = sum(l, r, v * 2, L, mid);

  auto y = sum(l, r, v * 2 + 1, mid + 1, R);

  pair<ll, ll> res{};

  // cout << x.first << " " << x.second << "\n";
  // cout << y.first << " " << y.second << "\n";

  if (a[x.first] <= a[y.first]) {
    res.first = x.first;
  } else {
    res.first = y.first;
  }

  if (a[x.second] >= a[y.second]) {
    res.second = x.second;
  } else {
    res.second = y.second;
  }
  return res;
}

struct pt {
    ll x, y;
    pt() {}
    pt(ll _x, ll _y) : x(_x), y(_y) {}
    pt operator-(const pt& p) const { return pt(x - p.x, y - p.y); }
    ll cross(const pt& p) const { return x * p.y - y * p.x; }
    ll cross(const pt& a, const pt& b) const { return (a - *this).cross(b - *this); }
};


int sgn(const ll& x) { return x >= 0 ? x ? 1 : 0 : -1; }

bool inter1(ll a, ll b, ll c, ll d) {
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d);
}

bool check_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0)
        return inter1(a.x, b.x, c.x, d.x) && inter1(a.y, b.y, c.y, d.y);
    return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) &&
           sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}


vector<string> split_by(string s, char delimiter) {
    vector<string> result;

    int start = 0;
    for (int i=0; i < s.length(); ++i) {
        if (s[i] == delimiter) {
            result.push_back(s.substr(start, i-start));
            start = i+1;
        }
    }
    if (start) result.push_back(s.substr(start, s.length() - start));


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

unsigned ll euclidian_norm(vector<ll> p1, vector<ll> p2) {
    unsigned ll dist = 0;

    assert(p1.size() == p2.size());
    int n = p1.size();

    for (int i=0; i < n; ++i) {
        dist += pow((p1[i] - p2[i]), 2);
    }
    return dist;
}

ll part_1(vector<string> rows, int iterations) {
    ll ans = 1;

    // Feels like union find?
    // We take each junction box
    //
    // But also focus on the actual problem.
    // If we were to take the boxes, compute the distance
    // from one box to everyother box,
    // then we need to compute the distance metric only once,
    // it does not change.
    //
    // Its still O(N^2).
    // Code it first, then look into how to make it with union find?
    int n = rows.size();

    vector<vector<ll>> junction_boxes(n, vector<ll>(3));

    for (int i=0; i < n; ++i) {
        string row = rows[i];
        vector<string> split_row = split_by(row, ',');

        for (int j=0; j < 3; ++j) {
            junction_boxes[i][j] = stoll(split_row[j]);
        }
    }

    // Compute the distance from each box to each other one.
    // N^2 = 1M comparisons.
    // vector<vector<pair<ll, ll>>> distances(n, vector<pair<ll,ll>>(n));

    vector<tuple<unsigned ll, ll, ll>> distances;

    // We could push this into a min heap.
    // Then keep popping?
    for (int i=0; i < n; ++i) {
        for (int j=0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            unsigned ll dist = euclidian_norm(junction_boxes[i], junction_boxes[j]);
            distances.push_back({dist, i, j});
        }
    }

    sort(distances.begin(), distances.end());

    // Use union find to handle merging of sets and seeing their sizes.
    // We can access UnionFind.set_size and check for the largest 3 values.
    UnionFind uf;
    uf.size = n;
    uf.parent = vector<int>(n);
    uf.rank = vector<int>(n);
    uf.set_size = vector<int>(n);

    for (int i=0; i < n; ++i) {
        uf.make_set(i);
    }

    int i=0;
    // Maybe they mean that we do not count if they are in the same circuit?
    for (tuple<ll, ll, ll> dist : distances) {
        int first = get<1>(dist);
        int second = get<2>(dist);

        if (!uf.is_connected(first, second)) {
            uf.union_sets(first, second);
            ++i;
        }

        if (i == iterations) {
            break;
        }
    }

    // Now simply take biggest sets from set_size
    sort(uf.set_size.begin(), uf.set_size.end(), greater<ll>());

    // print(uf.set_size);

    ans = 1;
    for (int i=0; i < 3; ++i) {
        cout << uf.set_size[i] << "\n";
        ans *= uf.set_size[i];
    }

    return ans;
}


unsigned ll part_2(vector<string> rows, int iterations) {
    ll ans = 1;



    return ans;
}



void solution() {
  ScopedTimer timer{"solution"};
  //
  // Solve it

  vector<string> example_input = read_input("example_input.txt");
  vector<string> problem_input = read_input("input.txt");

  cout << "ex 1: " << part_1(example_input, 10) << "\n";
  // cout << "ex 2: " << part_2(example_input) << "\n";

  // Still too high.
  cout << "part_1: " << part_1(problem_input, 1000) << "\n";
  // cout << "part_2: " << part_2(problem_input) << "\n";

}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t = 1;
  // cin >> t;

  while (t--)
    solution();
  return 0;
}

