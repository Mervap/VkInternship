#include <iostream>
#include <fstream>
#include "counter.h"

void print_help() {
    std::cout << "-file <filename> — read arrays from file" << std::endl
              << "-help — help" << std::endl << std::endl
              << "The expected performance of the arrays:" << std::endl
              << "n m" << std::endl
              << "a_1 a_2 ... a_n" << std::endl
              << "b_1 b_2 ... b_n" << std::endl;
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
        std::cerr << "Wrong count of arguments, use help" << std::endl;
    }


    if (argc == 2) {
        if (std::string(argv[1]) == "-help") {
            print_help();
            return EXIT_SUCCESS;
        } else {
            std::cerr << "Wrong argument, use help" << std::endl;
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
            std::cerr << "Wrong argument, use help" << std::endl;
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

    int ans = Counter::solve(a, n, b, m);
    std::cout << "Number of equal elements: " << ans << std::endl;
    delete[] a;
    delete[] b;
    return 0;
}