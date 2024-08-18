#include <gtest/gtest.h>

#include "utils/timestamp.h"

TEST(Timestamp, Profiling)
{
    int iterations = 100;

    // Profile original function
    auto start_original = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto ts = timestamp();
        (void)ts; // Prevent optimization from removing the call
    }
    auto end_original = std::chrono::high_resolution_clock::now();
    auto duration_original = std::chrono::duration_cast<std::chrono::microseconds>(end_original - start_original).count();

    // Profile improved function
    auto start_improved = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto ts = timestamp1();
        (void)ts; // Prevent optimization from removing the call
    }
    auto end_improved = std::chrono::high_resolution_clock::now();
    auto duration_improved = std::chrono::duration_cast<std::chrono::microseconds>(end_improved - start_improved).count();

    // Profile improved function
    auto start_improved1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto ts = timestamp2();
        (void)ts; // Prevent optimization from removing the call
    }
    auto end_improved1 = std::chrono::high_resolution_clock::now();
    auto duration_improved1 = std::chrono::duration_cast<std::chrono::microseconds>(end_improved1 - start_improved1).count();

    // Output the results
    std::cout << "Original function took " << duration_original << " microseconds for " << iterations << " iterations.\n";
    std::cout << "Improved function1 took " << duration_improved << " microseconds for " << iterations << " iterations.\n";
    std::cout << "Improved function2 took " << duration_improved1 << " microseconds for " << iterations << " iterations.\n";

}