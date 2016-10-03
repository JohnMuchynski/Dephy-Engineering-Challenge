#include "GaitDetector.h"
#include <cmath>
#include <iostream>
GaitDetector::GaitDetector() : lastZ(0), currentZ(0), lastAccMeasure(0), currentAccMeasure(0), max_recentZ(0), currentTimePositive(0), timePositiveStart(0), lastPrintedTime(-300)
{
	startTime = static_cast<std::chrono::milliseconds>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
}


GaitDetector::~GaitDetector()
{
}

void GaitDetector::updateSensors(const SensorData & gyro, const SensorData & acc)
{
	if (gyro.getZ() > max_recentZ && gyro.getZ() > currentZ) {
		max_recentZ = gyro.getZ();
	}
	lastZ = currentZ;
	currentZ = gyro.getZ();
	lastAccMeasure = currentAccMeasure;
	currentAccMeasure = static_cast<int>(sqrt(acc.getX()*acc.getX() + acc.getY()*acc.getY()));
	analyzeData();
}

void GaitDetector::analyzeData()
{
	if (currentZ > 0 && lastZ < 0) {
		timePositiveStart = static_cast<std::chrono::milliseconds>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
		currentTimePositive = timePositiveStart;
		max_recentZ = currentZ;
	}
	else if (currentZ > 0) {
		currentTimePositive = static_cast<std::chrono::milliseconds>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
	}
	else {
		timePositiveStart = currentTimePositive;
	}
	if (max_recentZ - 1500 > currentZ  && currentTimePositive.count() - timePositiveStart.count() > 150 && lastZ > currentZ) {
		std::chrono::milliseconds currentTime;
		currentTime = static_cast<std::chrono::milliseconds>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
		if (currentTime.count() - startTime.count() > lastPrintedTime + 300) {
			std::cout << "Gait Cycle started at " << currentTime.count() - startTime.count() << " ms" << std::endl;
			lastPrintedTime = currentTime.count() - startTime.count();
		}
	}
}
