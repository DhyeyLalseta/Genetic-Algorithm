#include "Chromosome.h"
#include <numeric>
#include <random>

using namespace std;

Chromosome::Chromosome()
{
	generateGenes();
	calculateFitness();
}

void Chromosome::generateGenes()
{
	random_device random;  // Will be used to obtain a seed for the random number engine
	mt19937 generate(random()); // Standard mersenne_twister_engine seeded with rd()
	uniform_int_distribution<int> distribute(0, 3);

	for (unsigned i = 0; i < CHROMOSOMESIZE; i++)
	{
		unsigned chance = distribute(generate);
		Chromosome::genes.push_back((!chance) ? 1 : 0);
	}
}

void Chromosome::calculateFitness()
{
	int sum = 0;
	for (unsigned i = 0; i < CHROMOSOMESIZE; i++)
	{
		sum += Chromosome::genes[i];
	}
	Chromosome::fitness=sum;
}

int Chromosome::getFitness()
{
	return Chromosome::fitness;
}

void Chromosome::mutate()
{
	random_device random;  // Will be used to obtain a seed for the random number engine
	mt19937 generate(random()); // Standard mersenne_twister_engine seeded with rd()
	uniform_int_distribution<> distribute(0, 20);
	for (unsigned i = 0; i < CHROMOSOMESIZE; i++)
	{
		unsigned chance = distribute(generate);
		if (chance==1)
		{
			switch (Chromosome::genes[i])
			{
			case 1:
				Chromosome::genes[i] = 0;
				break;
			case 0:
				Chromosome::genes[i] = 1;
				break;
			}
		}
	}
	Chromosome::calculateFitness();
}