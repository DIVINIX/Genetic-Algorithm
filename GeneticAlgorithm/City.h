#pragma once

#include <iostream>
#include <stdlib.h>

class City
{
private:
	std::string my_name;
	int my_id;
	double my_latitude;
	double my_longitude;

public:
	City();
	City(std::string name, int id, double latitude, double longitude);
	~City();

	std::string GetName();
	int GetId();
	double GetLatitude();
	double GetLongitude();
};

