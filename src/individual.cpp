#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

#include "individual.hpp"
#include "utils.hpp"

namespace IndividualNS
{
    Individual::Individual(const std::vector<char> genes)
    {
        m_Genes = genes;
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
        static const double prob = 0.3; // probability of mutation
        for (char &gene : m_Genes)
        {
            bool mutate = Utils::rand_within_gene_limit<bool>(prob);
            if (mutate)
            {
                gene = Utils::rand_within_gene_limit<char>();
            }
        }
    }

    std::vector<char> Individual::mate(const Individual &other) const
    {
        std::vector<char> new_genes;
        std::vector<char> mate_genes = other.m_Genes;
        unsigned int midway = m_Genes.size() / 2;

        for (uint i = 0; i < m_Genes.size(); i++)
        {
            if (i < midway)
            {
                new_genes.push_back(m_Genes[i]);
            }
            else
            {
                new_genes.push_back(mate_genes[i]);
            }
        }
        return new_genes;
    }

    std::ostream &operator<<(std::ostream &ostr, const Individual &individual)
    {
        std::string genes(individual.m_Genes.begin(), individual.m_Genes.end());
        ostr << "Genes: " << genes << ", fitness: " << individual.m_Fitness;
        return ostr;
    }
} // namespace IndividualNS