#include <utility>
#include <random>

#include "society.hpp"

namespace Utils
{
    template <typename T>
    T rand_within_gene_limit(const bool normalize = true, double probability = -1.0)
    {
        using GA::GENE_LIMIT;
        static std::random_device rd;
        static std::uniform_int_distribution<> index_dist(0, 100);
        double rand = index_dist(rd);
        if (normalize)
        {
            rand = (rand / 100.0 * (GENE_LIMIT.second - GENE_LIMIT.first)) + GENE_LIMIT.first;
        }
        else if (std::is_same<T, bool>::value && probability != -1.0) // T == bool
        {
            probability = (probability > 0.0 && probability < 1.0) ? probability : 1.0;
            rand = (rand / 100.0) <= probability;
        }
        return rand;
    }
} // namespace Utils
