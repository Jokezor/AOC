#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <chrono>       // For high_resolution_clock
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

using namespace std;
using ll = long long;

// --- Compile-Time Precomputations ---

constexpr int MAX_DIGITS = 11;

// 1. Powers of 10 Table
constexpr array<ll, MAX_DIGITS + 1> POW10 = []() {
    array<ll, MAX_DIGITS + 1> arr{};
    arr[0] = 1;
    for (int i = 1; i <= MAX_DIGITS; ++i) arr[i] = arr[i - 1] * 10;
    return arr;
}();

// 2. Structure to hold precomputed pattern info
struct PeriodInfo {
    int d;              // repeating unit length
    ll multiplier;      // repeating pattern multiplier
    ll seed_min;        // Min seed
    ll seed_max;        // Max seed
};

// 3. Precompute Multipliers and Divisors for every Length L
using DivisorTable = array<PeriodInfo, 8>; 
using LengthTable = array<pair<int, DivisorTable>, MAX_DIGITS + 1>;

constexpr LengthTable LUT = []() {
    LengthTable table{};
    for (int L = 1; L <= MAX_DIGITS; ++L) {
        int count = 0;
        for (int d = 1; d <= L / 2; ++d) {
            if (L % d == 0) {
                ll multiplier = 0;
                ll cur = 1;
                for (int k = 0; k < L/d; ++k) {
                    multiplier += cur;
                    if (k < L/d - 1) cur *= POW10[d]; 
                }
                
                table[L].second[count++] = {
                    d, multiplier, POW10[d-1], POW10[d] - 1
                };
            }
        }
        table[L].first = count;
    }
    return table;
}();

// --- Fast Math & Logic ---

// Fast integer log10 (Binary Search approach)
inline int get_digit_len(ll n) {
    if (n >= 10000000000ull) {
        if (n >= 100000000000000ull) {
            if (n >= 10000000000000000ull) {
                if (n >= 1000000000000000000ull) return 19;
                if (n >= 100000000000000000ull) return 18;
                return 17;
            }
            if (n >= 1000000000000000ull) return 16;
            return 15;
        }
        if (n >= 1000000000000ull) {
            if (n >= 10000000000000ull) return 14;
            return 13;
        }
        if (n >= 100000000000ull) return 12;
        return 11;
    }
    if (n >= 100000) {
        if (n >= 100000000) {
            if (n >= 1000000000) return 10;
            return 9;
        }
        if (n >= 10000000) return 8;
        if (n >= 1000000) return 7;
        return 6;
    }
    if (n >= 100) {
        if (n >= 10000) return 5;
        if (n >= 1000) return 4;
        return 3;
    }
    if (n >= 10) return 2;
    return 1;
}

inline ll sum_integers(ll start, ll end) {
    if (start > end) return 0;
    unsigned __int128 n = (unsigned __int128)(end - start + 1);
    return (ll)(n * ((unsigned __int128)start + end) / 2);
}

// Logic function
inline ll solve_range_fast(ll range_start, ll range_end) {
    int min_len = get_digit_len(range_start);
    int max_len = get_digit_len(range_end);
    ll total_ans = 0;

    pair<int, ll> net_cache[8]; 

    for (int L = min_len; L <= max_len; ++L) {
        const auto& entry = LUT[L];
        int count = entry.first;
        const auto& periods = entry.second;

        int cache_size = 0;

        for (int i = 0; i < count; ++i) {
            const auto& p = periods[i];
            
            // Fast ceil/floor logic with precomputed multiplier
            ll seed_min_req = (range_start + p.multiplier - 1) / p.multiplier;
            ll seed_max_req = range_end / p.multiplier;

            ll start = max(p.seed_min, seed_min_req);
            ll end = min(p.seed_max, seed_max_req);

            ll gross = 0;
            if (start <= end) {
                gross = p.multiplier * sum_integers(start, end);
            }

            ll subtract = 0;
            for (int k = 0; k < cache_size; ++k) {
                if (p.d % net_cache[k].first == 0) {
                    subtract += net_cache[k].second;
                }
            }

            ll net = gross - subtract;
            net_cache[cache_size++] = {p.d, net};
            total_ans += net;
        }
    }
    return total_ans;
}

void solution_fast() {
    // 1. Setup Input (Memory Map)
    int fd = open("input.txt", O_RDONLY);
    if (fd == -1) {
        cout << "Could not open input.txt" << endl;
        return;
    }

    struct stat sb;
    fstat(fd, &sb);
    char* data = (char*)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    char* end = data + sb.st_size;

    // 2. Start Timer
    auto start_time = std::chrono::high_resolution_clock::now();

    ll ans = 0;
    char* curr = data;

    // 3. Hot Loop (Parsing + Logic)
    while (curr < end) {
        ll left = 0;
        // Parse Left
        while (curr < end && *curr >= '0' && *curr <= '9') {
            left = left * 10 + (*curr - '0');
            curr++;
        }
        
        // Skip '-'
        if (curr < end) curr++; 

        ll right = 0;
        // Parse Right
        while (curr < end && *curr >= '0' && *curr <= '9') {
            right = right * 10 + (*curr - '0');
            curr++;
        }

        ans += solve_range_fast(left, right);

        // Skip ',' or newline
        if (curr < end) curr++;
    }

    // 4. Stop Timer
    auto end_time = std::chrono::high_resolution_clock::now();
    
    // 5. Cleanup
    munmap(data, sb.st_size);
    close(fd);

    // 6. Report
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();

    cout << "Part 2 Answer: " << ans << "\n";
    cout << "Time: " << duration_us << " µs (" << duration_ns << " ns)\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solution_fast();
    return 0;
}
