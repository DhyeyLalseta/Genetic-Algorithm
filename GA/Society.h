#pragma once
#include "Chromosome.h"

constexpr unsigned SOCIETYSIZE = 10;

class Society 
{
private:
	std::vector<Chromosome> society;

	int fittestChromosomeIndex,
		fittestChromosomeFitness,
		secondFittestChromosomeIndex,
		weakestChromosomeIndex;
public:
	Society();
	
	void determineChromosomes(),
		crossover(),
		mutation(),
		printFittest();

	int calculateFittestChromosome(),
		calculateSecondFittestChromosome(),
		calculateWeakestChromosome(),
		getFitness();
};

