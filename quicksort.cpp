#include <vector>    // ISO C++98
#include <print>     // ISO C++23
#include <ranges>    // ISO C++20
#include <algorithm> // ISO C++98/C++20
#include <random>    // ISO C++11
#include <span>      // ISO C++20
#include <iostream>

using namespace std;

template <typename Item>
size_t partition(std::span<Item> data, size_t l, size_t r)
{
    size_t p = r, firsthigh = l;

    for (size_t i = l; i < r; i++)
    {
        if (data[i] < data[p])
        {
            std::swap(data[i], data[firsthigh]);
            firsthigh++;
        }
    }
    std::swap(data[p], data[firsthigh]);
    return firsthigh;
}

template <typename Item>
void quickSort(std::span<Item> data, size_t l, size_t r)
{
    while (l < r)
    {
        size_t p = partition(data, l, r);
        size_t left = p - l;
        size_t right = r - p;


        if (left < right)
        {
            if (left > 0)
                quickSort(data, l, p - 1);
            l = p + 1;
        }
        else
        {
            if (right > 0)
                quickSort(data, p + 1, r);
            r = p - 1;
        }
    }
}


void demo2()
{
    println("\nDemo\n");

    auto randomSeed = random_device{}();
    default_random_engine rng(randomSeed);

    uniform_real_distribution<double> distr(-100., +100.);

    // Создадим вектор из 12 псевдослучайных чисел:
    vector<double> randoms(12);
    for (size_t i = 0; i < size(randoms); ++i)
        randoms[i] = distr(rng);

    println("randoms:\n{}", randoms);

    quickSort(span(randoms), 0, randoms.size() - 1);
    println("sorted randoms:\n{}, is sorted == {}", randoms, ranges::is_sorted(randoms));
}
