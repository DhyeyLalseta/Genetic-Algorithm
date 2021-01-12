#include <boost/range/combine.hpp>

#include <algorithm>
#include <vector>
#include <string>
#include <stdexcept>

#include "society.hpp"
#include "utils.tpp"

namespace GA
{

    Society::Society(const std::string &target, const long population /*= 10*/)
    {
        validate_target(std::move(target));
        m_Target = std::vector<char>(target.begin(), target.end());
        init_population(population);
    }

    Society::Society(const std::vector<char> &target, const long population /* = 10*/)
    {
        validate_target(std::move(target));
        m_Target = target;
        init_population(population);
    }

    unsigned long Society::generation() const
    {
        return m_Generation;
    }

    bool Society::converged() const
    {
        return m_Population[0].fitness() == 0;
    }

    void Society::evolve()
    {
        static const double mutation_prob = 0.3;

        const auto [first_offspring, second_offspring] = m_Population[0].crossover(m_Population[1]); // crossover fittest
        m_Population.end()[-1] = std::move(second_offspring);
        m_Population.end()[-2] = std::move(first_offspring);

        for (Individual &indv : m_Population)
        {
            if (Utils::rand_bool(mutation_prob))
            {
                indv.mutate();
            }
        }

        sort_population();
        m_Generation++;
    }

    template <typename T>
    void Society::validate_target(const T &target)
    {
        if (target.size() == 0)
        {
            throw std::length_error("Target is empty.");
        }

        std::for_each(target.begin(), target.end(), [](const char &letter) {
            if (letter < GENE_LIMIT.first || letter > GENE_LIMIT.second)
            {
                throw std::invalid_argument(std::string("Invalid target letter: \'") + (char)letter + "\'");
            }
        });
    }
    template void Society::validate_target<std::string>(const std::string &target);
    template void Society::validate_target<std::vector<char>>(const std::vector<char> &target);

    void Society::init_population(const long population_size /*= 10*/)
    {
        if (population_size < 4)
        {
            throw std::invalid_argument("Population size must be greater than 4");
        }
        m_Population.reserve(population_size);
        IndividualFactory individual_factory(m_Target);

        for (unsigned i = 0; i < population_size; i++)
        {
            m_Population.push_back(individual_factory.make_individual());
        }
        sort_population();
    }

    void Society::sort_population()
    {
        std::sort(m_Population.begin(), m_Population.end());
    }

    std::ostream &operator<<(std::ostream &ostr, const Society &society)
    {
        ostr << "Generation: " << society.m_Generation
             << "\n\tFittest Individual: {" << society.m_Population[0] << "}"
             << "\n\tTarget: " << std::string(society.m_Target.begin(), society.m_Target.end());
        return ostr;
    }
} // namespace GA