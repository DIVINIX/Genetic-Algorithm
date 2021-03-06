// GeneticAlgorithm.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>      /* printf */
#include <math.h>       /* sin */
#include <iostream>
#include <vector>
#include <string>

#include "City.h"
#include "Utilities.h"


using namespace std;

int main()
{
	srand(time(nullptr));

	std::vector<City> cities;

	City Bordeaux("Bordeaux", 1, 44.847807, -0.579472);
	City Pau("Pau", 2, 43.293295, -0.363570);
	City Nantes("Nantes", 3, 47.215585, -1.554908);
	City Paris("Paris", 4, 48.854885, -2.338646);
	City Lille("Lille", 5, 50.608719, -3.063295);
	City Marseille("Marseille", 6, 43.293551, -5.377397);
	City Nice("Nice", 7, 43.701680, -7.260711);
	City Lyon("Lyon", 8, 45.759132, -4.834604);
	City Montpellier("Montpellier", 9, 43.586120, -3.896094);
	City Toulouse("Toulouse", 10, 43.533513, -1.411209);
	City Brest("Brest", 11, 48.389353, -4.488616);
	City Limoges("Limoges", 12, 45.838771, -1.262108);
	City ClermontFerrand("Clermont-Ferrand", 13, 45.780535, -3.093242);
	City Tours("Tours",14, 47.404355, -0.688930);
	City Strasbourg("Strasbourg", 15, 48.540395, -7.727753);

	cities.push_back(Bordeaux);
	cities.push_back(Pau);
	cities.push_back(Nantes);
	cities.push_back(Paris);
	cities.push_back(Lille);
	cities.push_back(Marseille);
	cities.push_back(Nice);
	cities.push_back(Lyon);
	cities.push_back(Montpellier);
	cities.push_back(Toulouse);
	cities.push_back(Brest);
	cities.push_back(Limoges);
	cities.push_back(ClermontFerrand);
	cities.push_back(Tours);
	cities.push_back(Strasbourg);

	double best_value = 99999999999999999999999.99;
	std::vector<Chromosome*> Population = GeneratePopulation(cities);

	for (int i = 0; i < GENERATION_NUMBER; i++)
	{
		std::vector<Chromosome*> SelectedPopulation = Fitting(Population);
		if (SelectedPopulation.size() < 2)
		{
			printf("Population trop petite pour continuer l'evolution. \n");
			system("pause");
			return 0;
		}

		printf("Generation : %i | Meilleure distance de la generation : %f. Taille de la generation : %i \n", i + 1, GetBestValue(SelectedPopulation), SelectedPopulation.size());
		if (GetBestValue(SelectedPopulation) < best_value)
			best_value = GetBestValue(SelectedPopulation);

		Population = Evolution(SelectedPopulation); // Next Generation
 	}

	printf("Meilleure distance toute generation confondue : %f \n", best_value);

	system("pause");
	return 0;
}

