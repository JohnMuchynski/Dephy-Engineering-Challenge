#pragma once
#include "GyroData.h"
#include "SensorData.h"
#include <fstream>
#include <chrono>
#include <time.h>
class CLVFile
{
public:
	CLVFile(const char* filename);
	~CLVFile();
	bool isNewData();
	bool isEOF();
	SensorData getGyroData();
	SensorData getAccData();
private:
	std::chrono::milliseconds startTime;
	time_t nextTimestamp;
	SensorData gyro;
	SensorData acc; 
	SensorData nextGyro;
	SensorData nextAcc;
	void getNextLine(bool init);
	void readSensorData(SensorData & sensorData);
	std::fstream file;
	bool isNew;
	
};

