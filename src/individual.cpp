#include <boost/range/combine.hpp>

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

#include "individual.hpp"
#include "utils.tpp"

namespace GA
{
    Individual::Individual(const std::vector<char> &genes,
                           const std::shared_ptr<std::vector<char>> &target) : m_Genes(std::move(genes)),
                                                                               m_Target(std::move(target))
    {
        calc_fitness();
    }

    Individual::Individual(const std::shared_ptr<std::vector<char>> &target) : m_Target(std::move(target))
    {
        init_genes();
        calc_fitness();
    }

    void Individual::calc_fitness()
    {
        int fitness = 0;

        for (auto const &[individual_gene, target_gene] : boost::combine(m_Genes, *m_Target))
        {
            if (individual_gene != target_gene)
            {
                fitness += 1;
            }
        }
        m_Fitness = fitness;
    }

    void Individual::init_genes()
    {
        for (unsigned i = 0; i < m_Target->size(); i++)
        {
            m_Genes.push_back(Utils::rand_within_gene_limit<char>());
        }
    }

    bool Individual::operator<(const Individual &other) const
    {
        return m_Fitness < other.m_Fitness;
    }

    int Individual::fitness() const
    {
        return m_Fitness;
    }

    void Individual::mutate()
    {
        static const double prob = 0.15; // probability of mutation
        for (char &gene : m_Genes)
        {
            int mutate = Utils::rand_bool(prob);
            if (mutate)
            {
                gene = Utils::rand_within_gene_limit<char>();
            }
        }
        calc_fitness();
    }

    std::pair<Individual, Individual> Individual::crossover(const Individual &other) const
    {
        const std::vector<char> mate = other.m_Genes;
        const size_t crossover_point = Utils::rand_within_bounds<size_t>(0, m_Genes.size() - 1);

        std::vector<char> first_offspring(m_Genes.begin(), m_Genes.begin() + crossover_point);
        first_offspring.insert(first_offspring.end(), mate.begin() + crossover_point, mate.end());

        std::vector<char> second_offspring(mate.begin(), mate.begin() + crossover_point);
        second_offspring.insert(second_offspring.end(), m_Genes.begin() + crossover_point, m_Genes.end());

        return {Individual(first_offspring, m_Target), Individual(second_offspring, m_Target)};
    }

    std::ostream &operator<<(std::ostream &ostr, const Individual &individual)
    {
        std::string genes(individual.m_Genes.begin(), individual.m_Genes.end());
        ostr << "\"" + genes + "\", fitness:" + std::to_string(individual.m_Fitness);
        return ostr;
    }

    IndividualFactory::IndividualFactory(std::vector<char> &target)
    {
        m_Target = std::make_shared<std::vector<char>>(target);
    }

    Individual IndividualFactory::make_individual() const
    {
        return Individual(m_Target);
    }
} // namespace GA