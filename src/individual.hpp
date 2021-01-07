#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace SocietyNS
{
    class Society;
}

namespace IndividualNS
{
    using std::ostream;

    class Individual
    {
    public:
        Individual(): m_Genes({}), m_Fitness(0) {};
        Individual(const std::vector<char> genes);
        Individual(const std::string genes) : Individual(std::vector<char>(genes.begin(), genes.end())){};
        bool operator<(const Individual &other) const;

        int fitness() const;
        void mutate();

        std::vector<char> mate(const Individual &other) const;

        friend class SocietyNS::Society;
        friend std::ostream &operator<<(std::ostream &ostr, const Individual &individual);

    private:
        std::vector<char> m_Genes;
        int m_Fitness;
    };
} // namespace IndividualNS