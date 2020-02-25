#include <iostream>
#include "Society.h"

#define BREAK "------------------------------------------------------------"

using namespace std;

int main()
{
	int generationNumber = 0;
	Society demo = Society();

	while (demo.getFitness() < 10)
	{
		cout << "Generation: " << generationNumber++ << "\n";
		cout << "Fitness: " << demo.getFitness() << "\n";
		demo.printFittest();
		cout << BREAK << "\n";
		demo.crossover();
		demo.mutation();
	}
	cout << "Peak fitness found at generation: " << generationNumber << endl;
}