#include <utility>
#include <random>

#include "society.hpp"

namespace Utils
{
    template <typename T>
    T rand_within_gene_limit(double probability = 0.0)
    {
        using SocietyNS::GENE_LIMIT;
        static std::random_device rd;
        static std::uniform_int_distribution<> index_dist(GENE_LIMIT.first, GENE_LIMIT.second);
        int rand = index_dist(rd);
        if (!std::is_same<T, bool>::value)
        {
            return rand;
        }
        probability = (probability <= 1.0 && probability > 0.0) ? probability : 1.0;
        const double min = GENE_LIMIT.second - ((double)(GENE_LIMIT.second - GENE_LIMIT.first) * probability);
        return rand > min;
    }
} // namespace Utils
