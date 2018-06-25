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
* Fonction de calcul de la distance entre deux villes.
*
* Cette fonction permet de calculer la distance entre deux gènes, c'est à dire entre deux villes.
* Ce calcul est effectué par rapport aux coordonnées GPS des villes.
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
* Fonction de calcul de la distance d'un chromosome.
*
* Cette fonction permet de calculer la distance total d'un chromosome, c'est à dire d'un chemin. 
* On additione la distance entre toutes les villes du chemin.
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
* Fonction pour récupérer le meilleur chromosome.
*
* Cette fonction permet de trouver le meilleur chemin, c'est à dire le chemin le plus court.
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
* Fonction de remplissage.
*
* Cette fonction permet de remplir un vector de City à partir d'un autre vector de City.
*/
std::vector<City> FillCityList(std::vector<City> cities)
{
	std::vector<City> city_list;
	for (auto city : cities)
		city_list.push_back(city);
	return city_list;
}

/*
* Fonction de génération de la population.
*
* Cette fonction permet de générer une population aléatoire d'une taille donnée.
* Une population est composée de chromosomes et chaque chromosome est composé d'une liste de villes, les gènes. 
* Pour créer un chromosome on commence par faire un tableau qui contient la liste de toutes les villes. 
* Ensuite on sort une ville de ce tableau pour l'ajoter au chromosome. On continue jusqu'à ce qu'il n'y ai plus de villes dans le tableau. 
* On recommence l'opération de création d'un chromosome jusqu'à atteindre la taille de la population désirée.
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
* Cette fonction permet d'effectuer une mutation sur un chromosome.
* On prend un chromosome de départ et on intervertit deux gènes.
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

/*
* Fonction de test pour savoir si un gène existe.
*
* Cette fonction permet de tester la présence ou non d'un gène dans un chromosome. 
* Cette fonction sert essentiellement pour le croisement.
*/
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
* Cette fonction permet de croiser deux chromosomes. C'est à dire de créer un chromosome enfant à partir de deux chromosomes parents.
* Le croisement fonctionne de la facon suivante. On prend le premier gène des deux parents.
* Si les gènes sont différents et qu'ils ne sont pas déjà présent dans le chromosome enfant alors on les ajoute à l'enfant.
* Si les gènes sont identiques et que ce gène n'est pas présent dans l'enfant on l'ajoute. On recommence pour tous les gènes des parents.
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
* Cette fonction permet d'évoluer une population. C'est à dire qu'à partir d'une population on en créer une nouvelle.
* Cette nouvelle population contient la population source et tous les enfants créés suite aux croisements.
*/
std::vector<Chromosome *> Evolution(std::vector<Chromosome*> Population)
{
	std::vector<Chromosome *> NextGeneration;

	// On sauvegarde les parents, on ne garde que les meilleurs pour ne pas avoir une population trop importante
	std::vector<Chromosome *> BestParents = Fitting(Population);
	for (auto c : BestParents)
	NextGeneration.push_back(c);

	while (NextGeneration.size() < POPULATION_SIZE + Population.size())
	{
		const int index_parent_1 = rand() % Population.size();
		const int index_parent_2 = rand() % Population.size();

		if (index_parent_1 != index_parent_2)
		{
			NextGeneration.push_back(Crossing(Population[index_parent_1], Population[index_parent_2]));

			// Le pourcentage d'évolution
			const int mutation_percentage{ rand() % 100 };

			// Ici on a un pourcentage d'évolution de 1%
			if (mutation_percentage == 1)
				Mutation(NextGeneration.back());
		}
	}

	return NextGeneration;
}
