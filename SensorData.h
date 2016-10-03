#pragma once
class SensorData
{
public:
	SensorData();
	~SensorData();
	int getX() const;
	int getY() const;
	int getZ() const;
	void setX(int x);
	void setY(int y);
	void setZ(int z);
private:
	int x;
	int y;
	int z;
};

