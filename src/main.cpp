#include <iostream>
#include <string>

#include "society.hpp"

int main(int argc, char *argv[])
{
    std::string target("test");
    unsigned population_size = 250;
    switch (argc)
    {
    case 2:
        target = std::string(argv[1]);
        break;
    case 3:
        target = std::string(argv[1]);
        population_size = std::atoi(argv[2]);
        break;
    default:
        break;
    }
    GA::Society society(target, population_size);
    std::cout << society << std::endl;
    while (!society.converged())
    {
        society.evolve();
        std::cout << society << std::endl;
    }
}