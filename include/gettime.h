#pragma once
#include <functional>
#include <chrono>
long long getTime(std::function<void()> f)
{
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return elapsed.count();
}