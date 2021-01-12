#pragma once

#include <vector>
#include <string>

#include "individual.hpp"

namespace GA
{
    using std::ostream;
    constexpr std::pair<char, char> GENE_LIMIT('a', 'z');

    class Society
    {
    public:
        Society(const std::string &target, const long population = 10);
        Society(const std::vector<char> &target, const long population = 10);

        unsigned long generation() const;
        void evolve();
        bool converged() const;

        friend std::ostream &operator<<(std::ostream &ostr, const Society &society);

    private:
        unsigned long m_Generation = 0;
        std::vector<char> m_Target;
        std::vector<Individual> m_Population;

        template <typename T>
        void validate_target(const T &target);

        void init_population(const long population_size = 10);
        void sort_population();
    };
} // namespace GA