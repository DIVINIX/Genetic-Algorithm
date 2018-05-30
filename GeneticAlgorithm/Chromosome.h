#pragma once

#include <vector>

#include "Gene.h"

class Chromosome
{
private:
	std::vector<Gene*> my_genes;
	int my_size;
	double my_value;
public:
	Chromosome();
	~Chromosome();

	// Accesseur et mutateur pour la liste de gènes
	std::vector<Gene*> GetGenes();
	void AddGene(Gene *gene);
	Gene* GetGene(const int &index);

	// Accesseur poure la taille du chromosome
	int GetSize();

	// Accesseur et mutateur pour la valeur du chromosome
	double GetValue();
	void SetValue(const double &value);
};

