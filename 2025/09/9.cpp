#include <algorithm>
#include <bit>
#include <bits/stdc++.h>
#include <string>

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;

#define ll long long
#define all(x) x.begin(), x.end()
//#define MIN(v) *min_element(all(v))
//#define MAX(v) *max_element(all(v))
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
  vector<int> rank;

  void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
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

// Ray-casting algorithm
const double epsilon = numeric_limits<float>().epsilon();
const numeric_limits<double> DOUBLE;
const double MIN = DOUBLE.min();
const double MAX = DOUBLE.max();

struct Point { 
    const double x, y; 

    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
    }
    bool operator!=(const Point &p) const {
        return !operator==(p);
    }
};

struct Edge {
    const Point a, b;

    bool operator()(const Point& p) const
    {
        if (a.y > b.y) return Edge{ b, a }(p);
        if (p.y == a.y || p.y == b.y) return operator()({ p.x, p.y + epsilon });
        if (p.y > b.y || p.y < a.y || p.x > max(a.x, b.x)) return false;
        if (p.x < min(a.x, b.x)) return true;
        auto blue = abs(a.x - p.x) > MIN ? (p.y - a.y) / (p.x - a.x) : MAX;
        auto red = abs(a.x - b.x) > MIN ? (b.y - a.y) / (b.x - a.x) : MAX;
        return blue >= red;
    }
    bool on_segment(const Point& p) const {
        double cross = (p.x - a.x) * (b.y - a.y) - (p.y - a.y) * (b.x - a.x);
        if (abs(cross) > epsilon) return false;

        if (p.x < min(a.x, b.x) - epsilon || p.x > max(a.x, b.x) + epsilon) return false;
        if (p.y < min(a.y, b.y) - epsilon || p.y > max(a.y, b.y) + epsilon) return false;
        return true;
    }

    bool operator==(const Edge &rhs) const {
        return (a == rhs.a && b == rhs.b) || (a == rhs.b && b == rhs.a);
    }
    bool operator!=(const Edge &rhs) const {
        return !operator==(rhs);
    }
};

struct Figure {
    string  name;
    vector<Edge> edges;

    bool contains(const Point& p) const
    {
        auto c = 0;
        for (auto e : edges) if (e(p)) c++;
        return c % 2 != 0;
    }

    template<unsigned char W = 3>
    void check(vector<Point>& points, ostream& os) const
    {
        os << "Is point inside figure " << name <<  '?' << endl;
        for (auto p : points)
            os << "  (" << setw(W) << p.x << ',' << setw(W) << p.y << "): " << boolalpha << contains(p) << endl;
        os << endl;
    }
};


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

ll part_1(vector<string> rows) {
    ll ans = 0;
    vector<pair<ll, ll>> tiles;
    for (string row : rows) {
        vector<string> tile = split_by(row, ',');
        ll x = stoll(tile[0]);
        ll y = stoll(tile[1]);
        tiles.push_back({x, y});
    }
    
    int n = rows.size();
    for (int i=0; i < n; ++i) {
        for (int j=0; j < n; ++j) {
            ans = max(ans, abs(tiles[i].first - tiles[j].first + 1)
            *abs(tiles[i].second - tiles[j].second +1));
        }
    }


    return ans;
}

bool is_valid_tile(char tile) {
    return (tile == 'O' || tile == '#');
}

bool in_range(ll val, ll min_val, ll max_val) {
    return val > min_val && val < max_val;
}

bool strict_intersection(Point a, Point b, Point c, Point d) {
    bool intersects = false;

    return intersects;
}

unsigned ll part_2(vector<string> rows) {
    ll ans = 0;

    vector<pair<ll, ll>> tiles;
    for (string row : rows) {
        vector<string> tile = split_by(row, ',');
        ll x = stoll(tile[0]);
        ll y = stoll(tile[1]);
        tiles.push_back({x, y});
    }
    Figure grid;

    for (int i=1; i < tiles.size(); ++i) {
        Point p1 = {(double)tiles[i-1].second, (double)tiles[i-1].first};
        Point p2 = {(double)tiles[i].second, (double)tiles[i].first};
        grid.edges.push_back(Edge{p1, p2});
    }
    // Last to first
    Point p1 = {(double)tiles[tiles.size()-1].second, (double)tiles[tiles.size()-1].first};
    Point p2 = {(double)tiles[0].second, (double)tiles[0].first};
    grid.edges.push_back(Edge{p1, p2});

    for (int i=0; i < tiles.size(); ++i) {
        for (int j=i+1; j < tiles.size(); ++j) {
            Point p1 = {(double)tiles[i].second, (double)tiles[j].first};
            Point p2 = {(double)tiles[j].second, (double)tiles[i].first};
            Point tile_1 = {(double)tiles[i].second, (double)tiles[i].first};
            Point tile_2 = {(double)tiles[j].second, (double)tiles[j].first};
            
            vector<Point> points = {tile_1, p1, tile_2, p2, tile_1};

            bool p1_valid = grid.contains(p1);
            if (!p1_valid) {
                for (const auto& edge : grid.edges) {
                    if (edge.on_segment(p1)) {
                        p1_valid = true;
                        break;
                    }
                }
            }

            bool p2_valid = grid.contains(p2);
            if (!p2_valid) {
                for (const auto& edge : grid.edges) {
                    if (edge.on_segment(p2)) {
                        p2_valid = true;
                        break;
                    }
                }
            }
            
            if (p1_valid && p2_valid) {
                bool none_inside = true;
                ll min_x = min(tile_1.x, tile_2.x);
                ll max_x = max(tile_1.x, tile_2.x);
                ll min_y = min(tile_1.y, tile_2.y);
                ll max_y = max(tile_1.y, tile_2.y);
                
                for (const auto tile : tiles) {
                    ll t_x = tile.second;
                    ll t_y = tile.first;
                    if (in_range(t_x, min_x, max_x) && in_range(t_y, min_y, max_y)) {
                        none_inside = false;
                        break;
                    }
                }
                
                bool does_not_cross = true;
                for (auto edge : grid.edges) {
                    Point a = edge.a;
                    Point b = edge.b;

                    double target_xs[] = {(double)min_x, (double)max_x};
                    for (double x : target_xs) {
                        if (in_range(x, min(a.x, b.x), max(a.x, b.x))) {
                            double t = (x - a.x) / (b.x - a.x);
                            double y_hit = a.y + t * (b.y - a.y);

                            if (in_range(y_hit, (double)min_y, (double)max_y)) {
                                does_not_cross = false;
                                break;
                            }
                        }
                    }
                    if (!does_not_cross) {
                        break;
                    }

                    double target_ys[] = {(double)min_y, (double)max_y};
                    for (double y : target_ys) {
                        if (in_range(y, min(a.y, b.y), max(a.y, b.y))) {
                            double t = (y - a.y) / (b.y - a.y);
                            double x_hit = a.x + t * (b.x - a.x);

                            if (in_range(x_hit, (double)min_x, (double)max_x)) {
                                does_not_cross = false;
                                break;
                            }
                        }
                    }
                    if (!does_not_cross) {
                        break;
                    }
                }
                ll side = abs(tile_2.x - tile_1.x) + 1ll;
                ll height = abs(tile_2.y - tile_1.y) + 1ll;
                ll area = side * height;
                
                if (does_not_cross && none_inside && area > ans) {
                    ans = area;
                }
            }
        }
    }

    return ans;
}



void solution() {
  ScopedTimer timer{"solution"};
  //
  // Solve it

  vector<string> example_input = read_input("example_input.txt");
  vector<string> problem_input = read_input("input.txt");

  cout << "ex 1: " << part_1(example_input) << "\n";
  cout << "ex 2: " << part_2(example_input) << "\n";

  cout << "part_1: " << part_1(problem_input) << "\n";
  cout << "part_2: " << part_2(problem_input) << "\n";

}

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);

  int t = 1;
  // cin >> t;

  while (t--)
    solution();
  return 0;
}
