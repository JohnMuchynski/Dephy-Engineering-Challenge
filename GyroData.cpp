#include "GyroData.h"


GyroData::GyroData() :x(0), y(0), z(0)
{
}

GyroData::~GyroData()
{
}

int GyroData::getX()
{
	return x;
}

int GyroData::getY()
{
	return y;
}

int GyroData::getZ()
{
	return z;
}

void GyroData::setX(int x)
{
	this->x = x;
}

void GyroData::setY(int y)
{
	this->y = y;
}

void GyroData::setZ(int z)
{
	this->z = z;
}
