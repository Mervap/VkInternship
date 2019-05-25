//
// Created by dumpling on 25.05.19.
//

#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <chrono>
#include "counter.h"

std::vector<int> gen_arr(size_t size, int st = 0) {
    std::vector<int> res(size);
    for (int i = 0; i < size; ++i) {
        res[i] = i + st;
    }

    return res;
}

int run_test(const std::vector<int> &a, const std::vector<int> &b) {
    return Counter::solve(a.data(), a.size(), b.data(), b.size());
}

int get_time(const std::chrono::steady_clock::time_point &st, const std::chrono::steady_clock::time_point &end) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - st).count();
}

TEST(NaiveTests, zero_coincidences3x3) {
    std::vector<int> a, b;
    a = {1, 2, 3};
    b = {4, 5, 7};
    ASSERT_EQ(0, run_test(a, b));
    ASSERT_EQ(0, run_test(b, a));
}

TEST(NaiveTests, zero_coincidences6x5) {
    std::vector<int> a, b;
    a = {10, 42, 98, 109, -193, -200};
    b = {43, 183, 90, -201, 15};
    ASSERT_EQ(0, run_test(a, b));
    ASSERT_EQ(0, run_test(b, a));
}

TEST(NaiveTests, zero_coincidences0x5) {
    std::vector<int> a, b;
    a = {};
    b = {43, 183, 90, -201, 15};
    ASSERT_EQ(0, run_test(a, b));
    ASSERT_EQ(0, run_test(b, a));
}

TEST(NaiveTests, zero_coincidences10x0) {
    std::vector<int> a, b;
    a = {435, 183, 90, -201, 15, 57, 2, -1, 842, 21};
    b = {};
    ASSERT_EQ(0, run_test(a, b));
    ASSERT_EQ(0, run_test(b, a));
}

TEST(NaiveTests, coincidences3x3) {
    std::vector<int> a, b;
    a = {1, 2, 3};
    b = {3, 2, 1};
    ASSERT_EQ(3, run_test(a, b));
    ASSERT_EQ(3, run_test(b, a));
}

TEST(NaiveTests, coincidences5x3) {
    std::vector<int> a, b;
    a = {1, 2, 3, 4, 5};
    b = {-3, 2, 1};
    ASSERT_EQ(2, run_test(a, b));
    ASSERT_EQ(2, run_test(b, a));
}

TEST(NaiveTests, coincidences8x15) {
    std::vector<int> a, b;
    a = {1, 2, 3, 4, 5, 8, 7, 6};
    b = {-1, -2, -3, 10, 8, 2, 7, -100, -200, -3000, 30000, 1, -10, -11, -19};
    ASSERT_EQ(4, run_test(a, b));
    ASSERT_EQ(4, run_test(b, a));
}

TEST(NaiveTests, big_array) {
    std::vector<int> a, b;
    a = {1, 2, 3, 4, 5, 8, 7, 6};
    b = gen_arr(100'000);
    ASSERT_EQ(8, run_test(a, b));
    ASSERT_EQ(8, run_test(b, a));
}

TEST(NaiveTests, big_array_rev) {
    std::vector<int> a, b;
    a = {1, 2, 3, 4, 5, 6, 7, 8};
    b = gen_arr(1'000'000);
    std::reverse(b.begin(), b.end());
    ASSERT_EQ(8, run_test(a, b));
    ASSERT_EQ(8, run_test(b, a));
}

TEST(SetTests, zero_coincidences) {
    std::vector<int> a, b;
    a = gen_arr(1000);
    b = gen_arr(1'000'000, 1000);
    ASSERT_EQ(0, run_test(a, b));
    ASSERT_EQ(0, run_test(b, a));
}

TEST(SetTests, zero_coincidences_big) {
    std::vector<int> a, b;
    a = gen_arr(1'000'000);
    b = gen_arr(1'000'000, 1'000'000);
    ASSERT_EQ(0, run_test(a, b));
    ASSERT_EQ(0, run_test(b, a));
}

TEST(SetTests, coincidences_half) {
    std::vector<int> a, b;
    a = gen_arr(1'000'000);
    b = gen_arr(1'000'000, 500'000);
    ASSERT_EQ(500'000, run_test(a, b));
    ASSERT_EQ(500'000, run_test(b, a));
}

TEST(SetTests, coincidences_half_reverse) {
    std::vector<int> a, b;
    a = gen_arr(1'000'000);
    b = gen_arr(1'000'000, 500'000);
    std::reverse(b.begin(), b.end());
    ASSERT_EQ(500'000, run_test(a, b));
    ASSERT_EQ(500'000, run_test(b, a));
}


TEST(SetTests, coincidences_all) {
    std::vector<int> a;
    a = gen_arr(1'000'000);
    ASSERT_EQ(1'000'000, run_test(a, a));
}

TEST(SetTests, coincidences_all_reversed) {
    std::vector<int> a, b;
    a = gen_arr(1'000'000);
    b = a;
    std::reverse(b.begin(), b.end());
    ASSERT_EQ(1'000'000, run_test(a, b));
    ASSERT_EQ(1'000'000, run_test(b, a));
}

TEST(Performance, one_small) {
    std::vector<int> a, b;
    a = {-1};
    b = gen_arr(100'000'000);

    auto st = std::chrono::steady_clock::now();
    ASSERT_EQ(0, run_test(a, b));
    ASSERT_EQ(0, run_test(b, a));
    auto end = std::chrono::steady_clock::now();
    ASSERT_LE(get_time(st, end), 3000); // very roughly
}

TEST(Performance, one_small_FAST) {
    std::vector<int> a, b;
    a = {200};
    b = gen_arr(100'000'000);

    auto st = std::chrono::steady_clock::now();
    ASSERT_EQ(1, run_test(a, b));
    ASSERT_EQ(1, run_test(b, a));
    auto end = std::chrono::steady_clock::now();
    ASSERT_LE(get_time(st, end), 1);
}

TEST(Performance, all_big_FAST) {
    std::vector<int> a, b;
    a = gen_arr(100'000);
    b = gen_arr(100'000'000);

    auto st = std::chrono::steady_clock::now();
    ASSERT_EQ(100'000, run_test(a, b));
    ASSERT_EQ(100'000, run_test(b, a));
    auto end = std::chrono::steady_clock::now();
    ASSERT_LE(get_time(st, end), 500);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}