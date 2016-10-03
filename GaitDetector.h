#pragma once
#include "SensorData.h"
#include <chrono> 
class GaitDetector
{
public:
	GaitDetector();
	~GaitDetector();
	void updateSensors(const SensorData & newGyro, const SensorData & newAcc);
private:
	void analyzeData();
	int max_recentZ;
	int lastZ;
	std::chrono::milliseconds currentTimePositive;
	std::chrono::milliseconds timePositiveStart;
	std::chrono::milliseconds startTime;
	int lastPrintedTime;
	int lastAccMeasure;
	int currentZ;
	int currentAccMeasure;
};

