// Andor_test.cpp : Defines the entry point for the console application.
//

#include <direct.h>
#include <errno.h>
#include "stdafx.h"
extern "C" {
	#include "atmcd32d.h"        		// Andor functions
}
#include <stdio.h>
#include <iostream>


#include <Windows.h>
#include <string>



int main()
{

	char 				aBuffer[MAX_PATH + 1];
	int					errorValue;
	BOOL				errorFlag;

	GetCurrentDirectoryA(sizeof(aBuffer), aBuffer); // **** win32 specific ****
	std::cout << aBuffer << "\n";

	//SetCurrentDirectory(L"C:\\Users\\mathi\\Documents\\Lamda Cubed\\andor\\Drivers");

	SetCurrentDirectory(L"C:\\Users\\lambdacubed\\source\\repos\\Andor_test\\Andor_test\\Drivers");

	GetCurrentDirectoryA(sizeof(aBuffer), aBuffer); // **** win32 specific ****
	std::cout << aBuffer << "\n";


	errorValue = Initialize(aBuffer);  // Initialize driver in current directory
	std::cout << "\nInitialization errors:\n";

	std::cout << errorValue << " Initialize \n";

	if (errorValue != DRV_SUCCESS) {
		std::cout << "Initialize Error\n" << errorValue << "\n";
		//		std::cout << "Error: " << errorValue << "\n";
	}

	/*
	// Get camera capabilities
	errorValue = GetCapabilities(&caps);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Get Andor Capabilities information Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	*/
	
	char              model[32];                // headmodel
	// Get Head Model
	errorValue = GetHeadModel(model);
	std::cout << errorValue << " head model \n";

	std::cout << "Head Model: \t" << model << "\n";

	if (errorValue != DRV_SUCCESS) {
	std::cout << "Get Head Model information Error\n";
	}
	
	int 							gblXPixels;       				// dims of
	int								gblYPixels;       				// CCD chip
	// Get detector information
	errorValue = GetDetector(&gblXPixels, &gblYPixels);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Get Detector information Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	
	float       speed;
	int               VSnumber;                 // Vertical Speed Index
	// Set Vertical speed to recommended
	GetFastestRecommendedVSSpeed(&VSnumber, &speed);
	errorValue = SetVSSpeed(VSnumber);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Set Vertical Speed Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	float STemp;
	int               HSnumber;                 // Horizontal Speed Index
	int               ADnumber;                 // AD Index
	int         iSpeed, iAD, nAD, index;

	// Set Horizontal Speed to max
	STemp = 0;
	HSnumber = 0;
	ADnumber = 0;
	errorValue = GetNumberADChannels(&nAD);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Get number AD Channel Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	else {
	for (iAD = 0; iAD < nAD; iAD++) {
	GetNumberHSSpeeds(iAD, 0, &index);
	for (iSpeed = 0; iSpeed < index; iSpeed++) {
	GetHSSpeed(iAD, 0, iSpeed, &speed);
	if (speed > STemp) {
	STemp = speed;
	HSnumber = iSpeed;
	ADnumber = iAD;
	}
	}
	}
	}
	errorValue = SetADChannel(ADnumber);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Set AD Channel Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	errorValue = SetHSSpeed(0, HSnumber);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Set Horizontal Speed Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	
	int mintemp, maxtemp;
	errorValue = GetTemperatureRange(&mintemp, &maxtemp);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Get temperature range Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	errorValue = CoolerON();
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Turning cooler on Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}

	int cooler_on;
	errorValue = IsCoolerOn(&cooler_on);
	if (cooler_on != 1) {
		std::cout << "Cooler not on\n";
		std::cout << "Error: " << errorValue << "\n";
	}
	else {
		std::cout << "Cooler is on\n";
	}

	//Temperature control not supported

	//int temperature;
	//errorValue = GetTemperature(&temperature);
	//if (errorValue != DRV_SUCCESS) {
	//std::cout << "Get temperature Error\n";
	//std::cout << "Error: " << errorValue << "\n";
	//}
	//while (temperature > maxtemp || temperature < mintemp) {
	//errorValue = GetTemperature(&temperature);
	//std::cout << temperature << "\n";
	//if (errorValue != DRV_SUCCESS) {
	//std::cout << "Get temperature Error\n";
	//std::cout << "Error: " << errorValue << "\n";
	//}
	//}

	//
	
	int 	readMode = 4; // 0 Full Vertical Binning   1 Multi-Track   2 Random-Track   3 Single-Track   4 Image
	// Set read mode to required setting specified in xxxxWndw.c
	errorValue = SetReadMode(readMode);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Set Read Mode Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	
	int 	acquisitionMode = 1; // 1 - single scan; 2 - accumulate; 3 - kinetics; 4 - fast kinetics; 5 - run till abort;
	errorValue = SetAcquisitionMode(acquisitionMode);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Set Acquisition Mode Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	
	//Shutter control not supported

	//int typ = 0; // 0 - output ttl low to open shutter; 1 - output ttl high to open shutter;
	//int mode = 0; // 0 - auto; 1 - open; 2 - close;
	//int closingtime = 10;	// milliseconds
	//int openingtime = 10;	// milliseconds
	//errorValue = SetShutter(typ, mode, closingtime, openingtime);
	//if (errorValue != DRV_SUCCESS) {
	//std::cout << "Set shutter Error\n";
	//std::cout << "Error: " << errorValue << "\n";
	//}
	//

	float exposure_time = 0.1; //seconds
	errorValue = SetExposureTime(exposure_time);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Set exposure time Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	int trigger_mode = 0; // 0 - internal; 1 - external; 6 - external start; 7 - external exposure (bulb); 9 - external FVB EM; 10 - software trigger; 12 - external charge shifting;
	errorValue = SetTriggerMode(trigger_mode);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Set trigger mode Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}


	// only needed for accumulation acquisition 

	//float accumulation_cycle_time = .1; // seconds
	//errorValue = SetAccumulationCycleTime(accumulation_cycle_time);
	//if (errorValue != DRV_SUCCESS) {
	//std::cout << "Set accumulation cycle time Error\n";
	//std::cout << "Error: " << errorValue << "\n";
	//}
	
	//Only needed for kinetic capture

	//errorValue = SetBaselineClamp(1);
	//if (errorValue != DRV_SUCCESS) {
	//std::cout << "Set Baseline Clamp Error\n";
	//std::cout << "Error: " << errorValue << "\n";
	//}
	
	
	float exposure, accumulate, kinetic;
	errorValue = GetAcquisitionTimings(&exposure, &accumulate, &kinetic);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Get acquisition timings Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}

	// Wait for 2 seconds to allow MCD to calibrate fully before allowing an
	// acquisition to begin
	int 				test, test2;

	test = GetTickCount();
	do {
		test2 = GetTickCount() - test;
	} while (test2<2000);

	// make sure camera is in idle state
	int status;
	errorValue = GetStatus(&status);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Get acquisition timings Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	while (status != DRV_IDLE) {
	errorValue = GetStatus(&status);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Get acquisition timings Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	else {
		std::cout << "Camera not yet idle1\n";
	}
	}

	// start acquiring images
	errorValue = StartAcquisition();
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Start acquisition error\n";
	AbortAcquisition();
	}
	else {
	std::cout << "Starting acquisition........\n";
	}
	errorValue = GetStatus(&status);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Get acquisition status Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	while (status != DRV_IDLE) {
	errorValue = GetStatus(&status);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Get acquisition timings Error\n";
	std::cout << "Error: " << errorValue << "\n";
	}
	else {
		std::cout << "Camera status is " << status << "\n";
	}
	}

	unsigned long 		size = gblXPixels*gblYPixels;
	long				*pImageArray = NULL;    // main image buffer read from card
	if (!pImageArray) {
		pImageArray = (long*) malloc(size*sizeof(long));
	}
	errorValue = GetAcquiredData(pImageArray, size);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Get acquisition data Error\n";
		std::cout << "Error: " << errorValue << "\n";
	}
	free(pImageArray);
	pImageArray = NULL;


	errorValue = CoolerOFF();        // Switch off cooler (if used)
	if (errorValue != DRV_SUCCESS)
		std::cout << "Error switching cooler off" << "Error: " << errorValue << "\n";

	errorValue = ShutDown();
	if (errorValue != DRV_SUCCESS)
		std::cout << "Error shutting down" << "Error" << "\n";
	
	return 0;
}