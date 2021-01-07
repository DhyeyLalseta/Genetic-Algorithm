# genetic algorithm

this is a re-do of one of my first ever programming projects, a genetic algorithm in C++, which i initially made around a year ago. the genetic algorithm is a machine learning optimization algorithm which mimics natural selection. 

it was interesting to compare my previous implementation to this, and see how my thought process and coding practices have changed (like learning how git works, plus actually using .gitignore). my biggest regret is the way i implemented `calculate_individual_fitness`, as it's part of the `Society` class rather than a static method in `Individual` but it should be fine. 

`make run` for the default args, if you want to test using your own `target` and `population size`, `make` then `./bin/main <target> <population_size>`.
