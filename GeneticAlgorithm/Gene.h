#pragma once

#include "City.h"

class Gene
{
private:
	City my_gene;
public:
	Gene();
	Gene(City gene);
	~Gene();

	City GetGene();
	void SetGene(City gene);
};

