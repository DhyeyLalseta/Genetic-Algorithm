#pragma once
#include <vector>

constexpr unsigned CHROMOSOMESIZE = 10;

class Chromosome
{
private:
	int fitness;

public:
	std::vector<int> genes;

	Chromosome();

	void generateGenes(),
		calculateFitness(),
		mutate();

	int getFitness();
};

