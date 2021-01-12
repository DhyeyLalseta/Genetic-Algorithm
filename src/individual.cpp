#include <boost/range/combine.hpp>

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

#include "individual.hpp"
#include "utils.tpp"

namespace GA
{
    Individual::Individual(const std::vector<char> &genes, const std::shared_ptr<std::vector<char>> target)
    {
        m_Genes = genes;
        m_Target = target;
        calc_fitness();
    }

    Individual::Individual(const std::shared_ptr<std::vector<char>> target)
    {
        m_Target = target;
        init_genes();
        calc_fitness();
    }

    void Individual::calc_fitness()
    {
        int fitness = 0;
        char indv_gene, targ_gene;

        for (auto const &var : boost::combine(m_Genes, *m_Target))
        {
            boost::tie(indv_gene, targ_gene) = var;
            if (indv_gene != targ_gene)
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
        static const double prob = 0.1; // probability of mutation
        for (char &gene : m_Genes)
        {
            bool mutate = Utils::rand_within_gene_limit<bool>(false, prob);
            if (mutate)
            {
                gene = Utils::rand_within_gene_limit<char>();
            }
        }

        calc_fitness();
    }

    std::pair<Individual, Individual> Individual::crossover(const Individual &other) const
    {
        std::vector<char> first_offspring, second_offspring, mate = other.m_Genes;
        unsigned crossover_point = Utils::rand_within_gene_limit<unsigned>(false) % m_Genes.size();
        for (unsigned i = 0; i < m_Genes.size(); i++)
        {
            if (i < crossover_point)
            {
                first_offspring.push_back(m_Genes[i]);
                second_offspring.push_back(mate[i]);
            }
            else
            {
                first_offspring.push_back(mate[i]);
                second_offspring.push_back(m_Genes[i]);
            }
        }
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