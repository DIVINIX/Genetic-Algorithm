#include "stdafx.h"
#include "City.h"

City::City()
{
}

City::City(std::string name, int id, double latitude, double longitude)
{
	my_name = name;
	my_id = id;
	my_latitude = latitude;
	my_longitude = longitude;
}

City::~City()
{
}

std::string City::GetName()
{
	return my_name;
}

int City::GetId()
{
	return my_id;
}

double City::GetLatitude()
{
	return my_latitude;
}

double City::GetLongitude()
{
	return my_longitude;
}