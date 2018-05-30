#include "stdafx.h"
#include "Gene.h"


Gene::Gene()
{
}

Gene::Gene(City gene)
{
	my_gene = gene;
}

Gene::~Gene()
{
}

City Gene::GetGene()
{
	return my_gene;
}

void Gene::SetGene(City gene)
{
	my_gene = gene;
}
