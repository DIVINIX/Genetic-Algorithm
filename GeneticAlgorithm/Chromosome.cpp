#include "stdafx.h"
#include "Chromosome.h"

Chromosome::Chromosome()
{
	my_size = 0;
}

Chromosome::~Chromosome()
{
	if (my_genes.size() > 0)
	{
		for (auto gene : my_genes)
			delete gene;
	}
}

// Accesseur et mutateur pour la liste de gènes
std::vector<Gene*> Chromosome::GetGenes()
{
	return my_genes;
}

void Chromosome::AddGene(Gene *gene)
{
	my_genes.push_back(gene);
	my_size++;
}

Gene* Chromosome::GetGene(const int &index)
{
	return my_genes[index];
}

// Accesseur poure la taille du chromosome
int Chromosome::GetSize()
{
	return my_size;
}

// Accesseur et mutateur pour la valeur du chromosome
double Chromosome::GetValue()
{
	return my_value;
}

void Chromosome::SetValue(const double &value)
{
	my_value = value;
}
