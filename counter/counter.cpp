//
// Created by dumpling on 25.05.19.
//

#include <cstdio>
#include <unordered_set>
#include "counter.h"

static const int NAIVE_CONST = 37;

int count(const int *a, int size, int b) {
    for (const int *i = a; i < a + size; ++i) {
        if (*i == b) {
            return 1;
        }
    }

    return 0;
}

int naive_solve(const int *a, size_t n, const int *b, size_t m) {
    int res = 0;
    for (int i = 0; i < m; ++i) {
        res += count(a, n, b[i]);
        if (res == n) {
            break;
        }
    }

    return res;
}

int set_solve(const int *a, size_t n, const int *b, size_t m) {
    std::unordered_set<int> ans;
    ans.reserve(n);
    for (int i = 0; i < n; ++i) {
        ans.insert(a[i]);
    }

    int res = 0;
    for (int i = 0; i < m; ++i) {
        res += ans.count(b[i]);
        if (res == n) {
            break;
        }
    }

    return res;
}

int Counter::solve(const int *a, size_t n, const int *b, size_t m) {
    int ans;

    if (m < n) {
        std::swap(n, m);
        std::swap(a, b);
    }

    if (n < NAIVE_CONST) {
        ans = naive_solve(a, n, b, m);
    } else {
        ans = set_solve(a, n, b, m);
    }

    return ans;
}