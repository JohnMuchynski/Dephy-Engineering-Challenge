#include <iostream>
#include <string>
#include <stdlib.h>
#include "CLVFile.h"
#include "GaitDetector.h"
#include <conio.h>
int main() {
	std::cout << "Please enter the path for the CLV file you wish to read data from:";
	std::string fileName;
	std::cin >> fileName;
	CLVFile file(fileName.c_str());
	GaitDetector gaitDetector;
	while (!file.isEOF()) 
	{
		if (file.isNewData()) {
			gaitDetector.updateSensors(file.getGyroData(), file.getAccData());
		}
	}
	std::cout << "Done. Press enter to exit." << std::endl;
	_getch();
	return 0;
}