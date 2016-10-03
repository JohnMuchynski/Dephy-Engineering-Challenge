#include "SensorData.h"


SensorData::SensorData() : x(0), y(0), z(0)
{
}


SensorData::~SensorData()
{
}

int SensorData::getX() const
{
	return x;
}

int SensorData::getY() const
{
	return y;
}

int SensorData::getZ() const
{
	return z;
}

void SensorData::setX(int x)
{
	this->x = x;
}

void SensorData::setY(int y)
{
	this->y = y;
}

void SensorData::setZ(int z)
{
	this->z = z;
}