#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <memory>

namespace GA
{
    class Individual
    {
    public:
        Individual() : m_Genes{}, m_Target(nullptr), m_Fitness(0){};
        Individual(const std::vector<char> &genes) : m_Genes(std::move(genes)), m_Target(nullptr), m_Fitness(0){};
        Individual(const std::vector<char> &genes, const std::shared_ptr<std::vector<char>> &target);
        Individual(const std::shared_ptr<std::vector<char>> &target);

        bool operator<(const Individual &other) const;

        int fitness() const;
        void mutate();

        std::pair<Individual, Individual> crossover(const Individual &other) const;
        friend std::ostream &operator<<(std::ostream &ostr, const Individual &individual);

    private:
        std::vector<char> m_Genes;
        std::shared_ptr<std::vector<char>> m_Target;
        int m_Fitness;

        void calc_fitness();
        void init_genes();
    };

    class IndividualFactory
    {
    public:
        IndividualFactory(std::vector<char> &target);

        Individual make_individual() const;

    private:
        std::shared_ptr<std::vector<char>> m_Target;
    };
} // namespace GA