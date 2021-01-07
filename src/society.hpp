#pragma once

#include <vector>
#include <string>

#include "individual.hpp"

namespace SocietyNS
{
    using std::ostream;
    constexpr std::pair<char, char> GENE_LIMIT('a', 'z');

    class Society
    {
    public:
        Society(const std::string &target, uint population = 10);
        Society(const std::vector<char> &target, uint population = 10);

        uint generation() const;
        void evolve();
        bool converged() const;

        friend std::ostream &operator<<(std::ostream &ostr, const Society &society);

    private:
        uint m_Generation = 0;
        std::vector<char> m_Target;
        std::vector<IndividualNS::Individual> m_Population;

        void init_population(const uint population_size = 10);
        void sort_population();

        int calculate_individual_fitness(IndividualNS::Individual &individual);
    };
} // namespace SocietyNS