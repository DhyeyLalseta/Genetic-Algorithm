#include "Society.h"
#include <iostream>
#include <numeric>
#include <random>

using namespace std;

Society::Society()
{
	Society::society = {};
	for (unsigned i = 0; i < SOCIETYSIZE; i++)
	{
		Chromosome add = Chromosome();
		Society::society.push_back(add);
	}
	determineChromosomes();
}

void Society::determineChromosomes()
{
	Society::fittestChromosomeIndex = Society::calculateFittestChromosome();
	Society::secondFittestChromosomeIndex = Society::calculateSecondFittestChromosome();
	Society::weakestChromosomeIndex = Society::calculateWeakestChromosome();
	Society::fittestChromosomeFitness = Society::society[Society::fittestChromosomeIndex].getFitness();
}

int Society::calculateFittestChromosome()
{
	int fittestIndex = -1,
		maxFitness = -1;

	for (unsigned i = 0; i < SOCIETYSIZE; i++)
	{
		if (Society::society[i].getFitness() > maxFitness)
		{
			maxFitness = Society::society[i].getFitness();
			fittestIndex = i;
		}
	}

	return fittestIndex;
}

int Society::calculateSecondFittestChromosome()
{
	int secondFittestIndex = -1,
		secondMaxFitness = -1;

	for (unsigned i = 0; i < SOCIETYSIZE; i++)
	{
		if (Society::society[i].getFitness() > secondMaxFitness && i != Society::fittestChromosomeIndex)
		{
			secondMaxFitness = Society::society[i].getFitness();
			secondFittestIndex = i;
		}
	}
	return secondFittestIndex;
}

int Society::calculateWeakestChromosome()
{
	int weakestIndex = 11,
		weakestFitness = 11;

	for (unsigned i = 0; i < SOCIETYSIZE; i++)
	{
		if (Society::society[i].getFitness() < weakestFitness)
		{
			weakestFitness = Society::society[i].getFitness();
			weakestIndex = i;
		}
	}
	return weakestIndex;
}

void Society::crossover()
{
	random_device random;
	mt19937 generate(random()); 
	uniform_int_distribution<> distribute(0, 10);
	unsigned crossPoint = distribute(generate);

	for (unsigned i = 0; i < 10; i++)
	{
		Society::society[Society::weakestChromosomeIndex].genes[i] = (i < crossPoint) ? Society::society[Society::fittestChromosomeIndex].genes[i] : Society::society[Society::secondFittestChromosomeIndex].genes[i];
	}
	Society::society[Society::weakestChromosomeIndex].calculateFitness();
	Society::determineChromosomes();
}


void Society::mutation()
{
	for (unsigned i = 0; i < SOCIETYSIZE; i++)
	{
		Society::society[i].mutate();
		Society::society[i].calculateFitness();
	}
	Society::determineChromosomes();
}


int Society::getFitness()
{
	return Society::fittestChromosomeFitness;
}

void Society::printFittest()
{
	cout << "Fittest gene: " << "\n";
	for (unsigned i = 0; i < CHROMOSOMESIZE; i++)
	{
		cout << Society::society[fittestChromosomeIndex].genes[i] << " ";
	}
	cout << endl;
}

