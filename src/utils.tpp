#pragma once

#include <utility>
#include <random>
#include "society.hpp"

namespace Utils
{
    namespace
    {
        static std::random_device rd;
        static std::mt19937 twister(rd());
    } // namespace

    template <typename T>
    T rand_within_bounds(T lower_bound, T upper_bound)
    {
        std::uniform_int_distribution<int> dist(lower_bound, upper_bound);
        return dist(twister);
    }

    static inline bool rand_bool(double probability = 1.0)
    {
        static std::uniform_int_distribution<int> dist(0, 100);
        return ((dist(twister)/100.0) <= probability);
    }

    template <typename T>
    T rand_within_gene_limit()
    {
        return rand_within_bounds<int>(GA::GENE_LIMIT.first, GA::GENE_LIMIT.second);
    }
} // namespace Utils
