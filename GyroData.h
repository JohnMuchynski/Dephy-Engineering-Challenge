#pragma once
class GyroData
{
public:
	GyroData();
	~GyroData();
	int getX();
	int getY();
	int getZ();
	void setX(int x);
	void setY(int y);
	void setZ(int z);
private:
	int x;
	int y;
	int z;
};

