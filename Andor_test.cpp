// Andor_test.cpp : Defines the entry point for the console application.
//

#include <direct.h>
#include <errno.h>
#include "stdafx.h"
extern "C" {
	#include "common.h"             // definitions of application name etc
	#include "atmcd32d.h"        		// Andor functions
}
#include <stdio.h>
#include <iostream>




#include <Windows.h>
#include <string>


#include <windows.h>

#include <stdio.h>

#define BUFFER_SIZE 200



int main1(void)

{

	TCHAR infoBuf[BUFFER_SIZE];

	LPCWSTR lpPathName = L"C:\\Program Files";

	// Get the current working directory

	if (!GetCurrentDirectory(BUFFER_SIZE, infoBuf))

		printf("GetCurrentDirectory() failed!\n");

	printf("Your current directory is: %S\n", infoBuf);

	printf("Changing directory...\n");

	// Set to current working directory

	if (!SetCurrentDirectory(lpPathName))

		printf("SetCurrentDirectory() failed!\n");



	// Do some verification...

	if (!GetCurrentDirectory(BUFFER_SIZE, infoBuf))

		printf("GetCurrentDirectory() failed!\n");

	printf("Your current directory is: %S\n", infoBuf);



	// Get and display the Windows directory.

	if (!GetWindowsDirectory(infoBuf, BUFFER_SIZE))

		printf("GetWindowsDirectory() failed!\n");

	printf("Your Windows directory is: %S\n", infoBuf);



	// Get and display the system directory.

	if (!GetSystemDirectory(infoBuf, BUFFER_SIZE))

		printf("GetSystemDirectory() failed!\n");

	printf("Your system directory is: %S\n", infoBuf);

	return 0;

}

int main()
{

	char 				aBuffer[MAX_PATH+1];
	int					errorValue;
	BOOL				errorFlag;

	GetCurrentDirectoryA(sizeof(aBuffer), aBuffer); // **** win32 specific ****
	std::cout << aBuffer << "\n";

	SetCurrentDirectory(L"C:\\Users\\mathi\\Documents\\Lamda Cubed\\andor\\Drivers");

	GetCurrentDirectoryA(sizeof(aBuffer), aBuffer); // **** win32 specific ****
	std::cout << aBuffer << "\n";


	errorValue = Initialize(aBuffer);  // Initialize driver in current directory
	std::cout << "\nInitialization errors:\n";
	
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Initialize Error\n" << errorValue << "\n";
//		errorFlag = TRUE;
	}
	
	/*
	// Get camera capabilities
	errorValue = GetCapabilities(&caps);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Get Andor Capabilities information Error\n";
	errorFlag = TRUE;
	}
	*/
	/*
	char              model[32];                // headmodel
	// Get Head Model
	errorValue = GetHeadModel(model);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Get Head Model information Error\n";
		errorFlag = TRUE;
	}


	int 							gblXPixels;       				// dims of
	int								gblYPixels;       				// CCD chip


																	// Get detector information
	errorValue = GetDetector(&gblXPixels, &gblYPixels);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Get Detector information Error\n";
		errorFlag = TRUE;
	}


	float       speed;
	int               VSnumber;                 // Vertical Speed Index

												// Set Vertical speed to recommended
	GetFastestRecommendedVSSpeed(&VSnumber, &speed);
	errorValue = SetVSSpeed(VSnumber);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Set Vertical Speed Error\n";
		errorFlag = TRUE;
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
		errorFlag = TRUE;
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
		errorFlag = TRUE;
	}

	errorValue = SetHSSpeed(0, HSnumber);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Set Horizontal Speed Error\n";
		errorFlag = TRUE;
	}

	int mintemp, maxtemp;

	errorValue = GetTemperatureRange(&mintemp, &maxtemp);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Get temperature range Error\n";
		errorFlag = TRUE;
	}

	errorValue = CoolerON();
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Turning cooler on Error\n";
		errorFlag = TRUE;
	}

	int temperature;

	errorValue = GetTemperature(&temperature);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Get temperature Error\n";
		errorFlag = TRUE;
	}

	while (temperature > maxtemp || temperature < mintemp) {
		errorValue = GetTemperature(&temperature);
		if (errorValue != DRV_SUCCESS) {
			std::cout << "Get temperature Error\n";
			errorFlag = TRUE;
		}
	}





	int 	readMode = 4; // 0 Full Vertical Binning   1 Multi-Track   2 Random-Track   3 Single-Track   4 Image

	// Set read mode to required setting specified in xxxxWndw.c
	errorValue = SetReadMode(readMode);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Set Read Mode Error\n";
		errorFlag = TRUE;
	}

	int 	acquisitionMode = 1; // 1 - single scan; 2 - accumulate; 3 - kinetics; 4 - fast kinetics; 5 - run till abort;

	errorValue = SetAcquisitionMode(acquisitionMode);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Set Acquisition Mode Error\n";
		errorFlag = TRUE;
	}


	int typ = 0; // 0 - output ttl low to open shutter; 1 - output ttl high to open shutter;
	int mode = 0; // 0 - auto; 1 - open; 2 - close;
	int closingtime = 10;	// milliseconds
	int openingtime = 10;	// milliseconds

	errorValue = SetShutter(typ, mode, closingtime, openingtime);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Set shutter Error\n";
		errorFlag = TRUE;
	}

	float exposure_time = 0.1; //seconds

	errorValue = SetExposureTime(exposure_time);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Set exposure time Error\n";
		errorFlag = TRUE;
	}

	int trigger_mode = 1; // 0 - internal; 1 - external; 6 - external start; 7 - external exposure (bulb); 9 - external FVB EM; 10 - software trigger; 12 - external charge shifting;
	errorValue = SetTriggerMode(trigger_mode);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Set trigger mode Error\n";
		errorFlag = TRUE;
	}

	float accumulation_cycle_time = .1; // seconds
	errorValue = SetAccumulationCycleTime(accumulation_cycle_time);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Set accumulation cycle time Error\n";
		errorFlag = TRUE;
	}


	// SetNumberAccumulations(),
	//		SetNumberKinetics(), SetKineticCycletime(), 
	*/
	/* Only needed for kinetic capture
	errorValue = SetBaselineClamp(1);
	if (errorValue != DRV_SUCCESS) {
	std::cout << "Set Baseline Clamp Error\n";
	errorFlag = TRUE;
	}
	*/
	/*


	float exposure, accumulate, kinetic;
	errorValue = GetAcquisitionTimings(&exposure, &accumulate, &kinetic);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Get acquisition timings Error\n";
		errorFlag = TRUE;
	}


	int status;
	errorValue = GetStatus(&status);
	if (errorValue != DRV_SUCCESS) {
		std::cout << "Get acquisition timings Error\n";
		errorFlag = TRUE;
	}
	while (status != DRV_IDLE) {
		errorValue = GetStatus(&status);
		if (errorValue != DRV_SUCCESS) {
			std::cout << "Get acquisition timings Error\n";
			errorFlag = TRUE;
		}
	}

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
		std::cout << "Get acquisition timings Error\n";
		errorFlag = TRUE;
	}
	while (status != DRV_IDLE) {
		errorValue = GetStatus(&status);
		if (errorValue != DRV_SUCCESS) {
			std::cout << "Get acquisition timings Error\n";
			errorFlag = TRUE;
		}
	}



	long 				*pImageArray = NULL;    // main image buffer read from card
	int 		size;
	size = gblXPixels * gblYPixels;  // Needs to hold full image

	errorValue = GetAcquiredData(pImageArray, size);
	if (errorValue != DRV_SUCCESS) {
		wsprintf((LPWSTR)aBuffer, (LPWSTR)"Acquisition error!");
		return FALSE;
	}
	*/
    return 0;
}

