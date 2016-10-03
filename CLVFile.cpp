#include "CLVFile.h"
#include <string>
#include <sstream>
CLVFile::CLVFile(const char * filename) : file(filename)
{
	if (!file.is_open()) throw "Bad file given";
	std::string temp;
	std::getline(file, temp); //remove the first two lines of the file as they are not needed
	std::getline(file, temp);
	startTime = static_cast<std::chrono::milliseconds>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
	getNextLine(true);
}


CLVFile::~CLVFile()
{
}

int convertStringToInt(std::string intStr)
{
	std::stringstream stream;
	int returnVal = -1;
	stream << intStr;
	stream >> returnVal;
	return returnVal;
}
time_t convertStringToTime(std::string intStr)
{
	std::stringstream stream;
	time_t returnVal = 0;
	stream << intStr;
	stream >> returnVal;
	return returnVal;
}
void CLVFile::readSensorData(SensorData & sensorData)
{
	std::string temp;
	std::getline(file, temp, ',');
	sensorData.setX(convertStringToInt(temp));
	std::getline(file, temp, ',');
	sensorData.setY(convertStringToInt(temp));
	std::getline(file, temp, ',');
	sensorData.setZ(convertStringToInt(temp));
}
void CLVFile::getNextLine(bool init) 
{
	std::chrono::milliseconds currentTime;
	currentTime = static_cast<std::chrono::milliseconds>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
	time_t temp = currentTime.count() - startTime.count();
	if (init) {
		std::string temp;
		std::getline(file, temp, ',');
		std::getline(file, temp, ',');
		readSensorData(acc);
		readSensorData(gyro);
		std::getline(file, temp); //rest of the line not needed
		std::getline(file, temp, ',');
		std::getline(file, temp, ',');
		nextTimestamp = convertStringToTime(temp);
		readSensorData(nextAcc);
		readSensorData(nextGyro);
		std::getline(file, temp); //rest of the line not needed
		isNew = true;
	}
	else if (nextTimestamp <= currentTime.count() - startTime.count()) {
		std::string temp;
		gyro = nextGyro;
		acc = nextAcc;
		std::getline(file, temp, ',');
		std::getline(file, temp, ',');
		nextTimestamp = convertStringToTime(temp);
		readSensorData(nextAcc);
		readSensorData(nextGyro);
		std::getline(file, temp); //rest of the line not needed
		isNew = true;
	}
	else {
		isNew = false;
	}
}

bool CLVFile::isNewData()
{
	getNextLine(false);
	return isNew;
}

bool CLVFile::isEOF()
{
	return file.eof();
}

SensorData CLVFile::getGyroData()
{
	return gyro;
}
SensorData CLVFile::getAccData()
{
	return acc;
}

