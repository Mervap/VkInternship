#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <math.h>
#include <unordered_set>
#include <chrono>
#include <cassert>
#include <random>
#include <fstream>

static const int NAIVE_CONST = 43;

void print_help() {
    std::cout << "-file <filename> — read arrays from file" << std::endl
              << "-help — help" << std::endl
              << "The expected performance of the arrays:" << std::endl
              << "n m" << std::endl
              << "a_1 a_2 ... a_n" << std::endl
              << "b_1 b_2 ... b_n" << std::endl;
}

int find(int *a, int size, int b) {
    for (int *i = a; i < a + size; ++i) {
        if (*i == b) {
            return 1;
        }
    }

    return 0;
}

int naive_solve(int *a, size_t n, int *b, size_t m) {
    int res = 0;
    for (int i = 0; i < m; ++i) {
        res += find(a, n, b[i]);
        if (res == n) {
            break;
        }
    }

    return res;
}

int set_solve(int *a, size_t n, int *b, size_t m) {
    std::unordered_set<int> ans;
    for (int i = 0; i < n; ++i) {
        ans.insert(a[i]);
    }

    int res = 0;
    for (int i = 0; i < m; ++i) {
        res += ans.count(b[i]);
        if (res == m) {
            break;
        }
    }

    return res;
}

int solve(int *a, size_t n, int *b, size_t m) {
    int ans;
    if (m < NAIVE_CONST) {
        ans = naive_solve(a, n, b, m);
    } else {
        ans = set_solve(a, n, b, m);
    }

    return ans;
}

int *read_array(int n) {
    int *a = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    return a;
}

int *read_array_from_file(int n, std::ifstream &in) {
    int *a = new int[n];
    for (int i = 0; i < n; ++i) {
        in >> a[i];
    }

    return a;
}

int main(int argc, char **argv) {

    if (argc > 3) {
        std::cerr << "Wrong count of arguments, use help";
    }


    if (argc == 2) {
        if (std::string(argv[1]) == "-help") {
            print_help();
            return EXIT_SUCCESS;
        } else {
            std::cerr << "Wrong argument, use help";
            return EXIT_FAILURE;
        }
    }

    size_t n, m;
    int *a = nullptr;
    int *b = nullptr;
    if (argc == 3) {
        if (std::string(argv[1]) == "-file") {
            std::ifstream in(argv[2]);
            std::ifstream::sync_with_stdio(false);
            in.tie(nullptr);

            in >> n >> m;
            a = read_array_from_file(n, in);
            b = read_array_from_file(m, in);
        } else {
            std::cerr << "Wrong argument, use help";
            return EXIT_FAILURE;
        }
    } else {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);

        std::cin >> n >> m;
        a = read_array(n);
        b = read_array(m);
    }
    std::cout.tie(nullptr);

    std::cout << "Read finished" << std::endl;
    if (m < n) {
        std::swap(n, m);
        std::swap(a, b);
    }

    std::cout << solve(a, n, b, m) << std::endl;
    delete[] a;
    delete[] b;
    return 0;
}