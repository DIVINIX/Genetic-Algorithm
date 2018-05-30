#pragma once

#include <stdlib.h>
#include <math.h>
#include <vector>
#include <random>
#include <algorithm>

#include "City.h"
#include "Chromosome.h"
#include "stdafx.h"

#define M_PI 3.14159265358979323846
#define EARTH_RADIUS 6367445
#define GENERATION_NUMBER 20
#define POPULATION_SIZE 100
#define FITING_RATE 15

/*
* Fonction d.
*
* Cette fonction permet d'évaluer une population. C'est à dire qu'à partir d'une population
* donnée, la fonction retourne une nouvelle population seletionnée à partir de la population
* d'origine. Cette nouvelle population sera ensuite utilisée pour l'évolution.
*/
double DistanceCalculation(Gene *gene1, Gene *gene2)
{
	const double lat_radian_gene1 = gene1->GetGene().GetLatitude()*M_PI / 180;
	const double lng_radian_gene1 = gene1->GetGene().GetLongitude()*M_PI / 180;

	const double lat_radian_gene2 = gene2->GetGene().GetLatitude()*M_PI / 180;
	const double lng_radian_gene2 = gene2->GetGene().GetLongitude()*M_PI / 180;

	const double sin_lat = sin(lat_radian_gene1) * sin(lat_radian_gene2);
	const double cos_lat = cos(lat_radian_gene1) * cos(lat_radian_gene2);
	const double cos_lng = cos(lng_radian_gene2 - lng_radian_gene1);

	return EARTH_RADIUS * acos(sin_lat + (cos_lat * cos_lng)) / 1000;
}

/*
* Fonction d'évaluation.
*
* Cette fonction permet d'évaluer une population. C'est à dire qu'à partir d'une population
* donnée, la fonction retourne une nouvelle population seletionnée à partir de la population
* d'origine. Cette nouvelle population sera ensuite utilisée pour l'évolution.
*/
void ChromosomeDistanceCalculation(Chromosome *chromosome)
{
	double distance{ 0 };

	for (int i = 0; i < chromosome->GetSize() - 1; i++)
	{
		distance = distance + DistanceCalculation(chromosome->GetGene(i), chromosome->GetGene(i + 1));
	}
	chromosome->SetValue(distance);
}

/*
* Fonction d'évaluation.
*
* Cette fonction permet d'évaluer une population. C'est à dire qu'à partir d'une population
* donnée, la fonction retourne une nouvelle population seletionnée à partir de la population
* d'origine. Cette nouvelle population sera ensuite utilisée pour l'évolution.
*/
double GetBestValue(std::vector<Chromosome *> Population)
{
	double min_distance = Population[0]->GetValue(); // On prend comme valeur de référence la première distance

	for (auto chromosome : Population)
	{
		if (chromosome->GetValue() < min_distance)
			min_distance = chromosome->GetValue();
	}

	return min_distance;
}

/*
* Fonction d'évaluation.
*
* Cette fonction permet d'évaluer une population. C'est à dire qu'à partir d'une population
* donnée, la fonction retourne une nouvelle population seletionnée à partir de la population
* d'origine. Cette nouvelle population sera ensuite utilisée pour l'évolution.
*/
std::vector<City> FillCityList(std::vector<City> cities)
{
	std::vector<City> city_list;
	for (auto city : cities)
		city_list.push_back(city);
	return city_list;
}

/*
* Fonction d'évaluation.
*
* Cette fonction permet d'évaluer une population. C'est à dire qu'à partir d'une population
* donnée, la fonction retourne une nouvelle population seletionnée à partir de la population
* d'origine. Cette nouvelle population sera ensuite utilisée pour l'évolution.
*/
std::vector<Chromosome*> GeneratePopulation(std::vector<City> cities)
{
	std::vector<Chromosome*> Population = std::vector<Chromosome*>();

	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		std::vector<City> city_list = FillCityList(cities);
		Chromosome *chromosome = new Chromosome();

		while (city_list.size() > 0)
		{
			const int index = rand() % city_list.size();
			chromosome->AddGene(new Gene(city_list[index]));
			city_list.erase(city_list.begin() + index);
		}
		Population.push_back(chromosome);
	}

	return Population;
}

/*
* Fonction d'évaluation.
*
* Cette fonction permet d'évaluer une population. C'est à dire qu'à partir d'une population
* donnée, la fonction retourne une nouvelle population seletionnée à partir de la population
* d'origine. Cette nouvelle population sera ensuite utilisée pour l'évolution.
*/
std::vector<Chromosome *> Fitting(std::vector<Chromosome*> Population)
{
	std::vector<Chromosome*> SelectedPopulation;

	//----------------------------------------------------
	// Calcul de la valeur de chaque chromosome
	//----------------------------------------------------

	for (auto chromosome : Population)
		ChromosomeDistanceCalculation(chromosome);

	//----------------------------------------------------
	// Récupération de la meilleure valeur
	//----------------------------------------------------
	const double min_distance = GetBestValue(Population);

	//----------------------------------------------------
	// Sélection de la nouvelle population
	//----------------------------------------------------
	const double rate = min_distance * FITING_RATE / 100;
	const double threshold = min_distance + rate;
	for (auto chromosome : Population)
	{
		if (chromosome->GetValue() < threshold)
			SelectedPopulation.push_back(chromosome);
	}

	return SelectedPopulation;
}

/*
* Fonction de mutation.
*
* Cette fonction permet d'évaluer une population. C'est à dire qu'à partir d'une population
* donnée, la fonction retourne une nouvelle population seletionnée à partir de la population
* d'origine. Cette nouvelle population sera ensuite utilisée pour l'évolution.
*/
void Mutation(Chromosome *chromosome)
{
	Chromosome *my_chromosome = new Chromosome();

	const int index_gene_1 = rand() % chromosome->GetSize();
	const int index_gene_2 = rand() % chromosome->GetSize();

	Gene *gene_1 = chromosome->GetGenes()[index_gene_1];
	Gene *gene_2 = chromosome->GetGenes()[index_gene_2];

	for (int i = 0; i < index_gene_1; i++)
		my_chromosome->AddGene(chromosome->GetGene(i));

	my_chromosome->AddGene(gene_2);

	for (int i = index_gene_1 + 1; i < index_gene_2; i++)
		my_chromosome->AddGene(chromosome->GetGene(i));

	my_chromosome->AddGene(gene_1);

	for (int i = index_gene_2 + 1; i < chromosome->GetGenes().size(); i++)
		my_chromosome->AddGene(chromosome->GetGene(i));

	chromosome = my_chromosome;
}

bool CheckGenePresent(Chromosome *chromosome, Gene *gene)
{
	bool present = false;

	for (auto g : chromosome->GetGenes())
	{
		int id_2 = gene->GetGene().GetId();
		int id_1 = g->GetGene().GetId();
		
		if (id_1 == id_2)
			return true;
	}

	return present;
}

/*
* Fonction de croisement.
*
* Cette fonction permet d'évaluer une population. C'est à dire qu'à partir d'une population
* donnée, la fonction retourne une nouvelle population seletionnée à partir de la population
* d'origine. Cette nouvelle population sera ensuite utilisée pour l'évolution.
*/
Chromosome* Crossing(Chromosome *parent1, Chromosome *parent2)
{
	Chromosome *child = new Chromosome();

	for (int i = 0; i < parent1->GetSize(); i++)
	{
		if (parent1->GetGene(i)->GetGene().GetId() != parent2->GetGene(i)->GetGene().GetId())
		{
			if (!CheckGenePresent(child, parent1->GetGene(i)) && child->GetSize() < parent1->GetSize())
				child->AddGene(parent1->GetGene(i));

			if (!CheckGenePresent(child, parent2->GetGene(i)) && child->GetSize() < parent1->GetSize())
				child->AddGene(parent2->GetGene(i));
		}
		else
		{
			if (!CheckGenePresent(child, parent1->GetGene(i)) && child->GetSize() < parent1->GetSize())
				child->AddGene(parent1->GetGene(i));
		}

	}

	return child;
}

/*
* Fonction d'évolution.
*
* Cette fonction permet d'évaluer une population. C'est à dire qu'à partir d'une population
* donnée, la fonction retourne une nouvelle population seletionnée à partir de la population
* d'origine. Cette nouvelle population sera ensuite utilisée pour l'évolution.
*/
std::vector<Chromosome *> Evolution(std::vector<Chromosome*> Population)
{
	std::vector<Chromosome *> NextGeneration;

	// On sauvegarde les parents
	for (auto c : Population)
		NextGeneration.push_back(c);

	while (NextGeneration.size() < POPULATION_SIZE + Population.size())
	{
		const int index_parent_1 = rand() % Population.size();
		const int index_parent_2 = rand() % Population.size();

		if (index_parent_1 != index_parent_2)
		{
			NextGeneration.push_back(Crossing(Population[index_parent_1], Population[index_parent_2]));

			const int mutation_percentage{ rand() % 100 };

			if (mutation_percentage == 1)
				Mutation(NextGeneration.back());
		}
	}

	return NextGeneration;
}
