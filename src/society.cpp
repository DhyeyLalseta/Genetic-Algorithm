#include <boost/range/combine.hpp>

#include <algorithm>
#include <vector>
#include <string>

#include "society.hpp"
#include "utils.hpp"

namespace SocietyNS
{

    Society::Society(const std::string &target, uint population /*= 10*/)
    {
        m_Target = std::vector<char>(target.begin(), target.end());
        init_population(population);
    }

    Society::Society(const std::vector<char> &target, uint population /* = 10*/)
    {
        m_Target = target;
        init_population(population);
    }
    uint Society::generation() const
    {
        return m_Generation;
    }

    bool Society::converged() const
    {
        return m_Population[0].fitness() == 0;
    }

    void Society::evolve()
    {
        using IndividualNS::Individual;
        Individual offspring = m_Population[0].mate(m_Population[1]); // mate fittest
        offspring.m_Fitness = calculate_individual_fitness(offspring);
        m_Population.back() = offspring;

        for (Individual &indv : m_Population)
        {
            indv.mutate();

            indv.m_Fitness = calculate_individual_fitness(indv);
        }

        sort_population();
        m_Generation++;
    }

    void Society::init_population(const uint population_size /*= 10*/)
    {
        m_Population.reserve(population_size);
        for (uint i = 0; i < population_size; i++)
        {
            std::string genes;
            for (uint i = 0; i < m_Target.size(); i++)
            {
                genes += Utils::rand_within_gene_limit<char>();
            }
            IndividualNS::Individual new_individual(genes);
            new_individual.m_Fitness = calculate_individual_fitness(new_individual);
            m_Population.push_back(new_individual);
        }

        sort_population();
    }

    void Society::sort_population()
    {
        std::sort(m_Population.begin(), m_Population.end());
    }

    int Society::calculate_individual_fitness(IndividualNS::Individual &individual)
    {
        int fitness = 0;
        char indv_gene, targ_gene;

        for (auto const &var : boost::combine(individual.m_Genes, m_Target))
        {
            boost::tie(indv_gene, targ_gene) = var;
            if (indv_gene != targ_gene)
            {
                fitness += 1;
            }
        }
        return fitness;
    }

    std::ostream &operator<<(std::ostream &ostr, const Society &society)
    {
        ostr << "Generation: " << society.m_Generation
             << "\n\tFittest Individual: {" << society.m_Population[0] << "}"
             << "\n\tTarget: " << std::string(society.m_Target.begin(), society.m_Target.end());
        return ostr;
    }
} // namespace SocietyNS