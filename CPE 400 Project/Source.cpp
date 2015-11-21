/////////////////////////////////////////////////////////////////////
// Nicholas Smith
// Project Transmission power/sleep control in sensor networks for extended
//		lifetime
// CPE 400
/////////////////////////////////////////////////////////////////////

//Headers
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include "Header.h"
#include <time.h>
#include <string>


using namespace std;

//Sensors
struct Sensor_Base
{
	int battery;
	bool ON;
	queue<int> data;
} Sensor;

//Classes
//Function Headers
int generateData();

//Global
int Battery_Life = 1000;

int main()
{
	//Variables
	vector<Sensor_Base> Sensors;
	Sensor_Base Temp_Sensor;
	int Random;
	int dataTemp;
	int counter1 = 0, counter2 = 0;
	bool cont = true;

	srand(time(NULL));

	//Temp struct to Initalize
	Temp_Sensor.battery = Battery_Life;
	Temp_Sensor.ON = true;

	//Initilzing Vector
	for (int i = 0; i < 10; i++)
	{
		Sensors.push_back(Temp_Sensor);
	}
	

	//////////////////////////////////////////////////////////////////////////////
	//Part 1
	//////////////////////////////////////////////////////////////////////////////
	
	
	while(cont)
	{
		//See how long it's been running
		counter1 += 1;

		//Generate random data and add it to the sensor queue
		Random = rand();
		Sensors[0].data.push(Random);

		//Transmit data if sensor is on
		for (int i = 0; i < 9; i++)
		{
			if (Sensors[i].ON == true)
			{
				if (!Sensors[i].data.empty())
				{
					Sensors[i + 1].data.push(Sensors[i].data.front());
					Sensors[i].data.pop();
					Sensors[i].battery = Sensors[i].battery -  5;
				}
			}
		}
		
		//Battery
		for (int i = 0; i < 10; i++)
		{
			if (Sensors[i].ON == false)
			{
				Sensors[i].battery = Sensors[i].battery - 1;
			}
			else if (Sensors[i].ON == true)
			{
				Sensors[i].battery = Sensors[i].battery - 2;
			}
		}

		//Check battery condition
		for (int i = 0; i < 10; i++)
		{
			if (Sensors[i].battery <= 0)
			{
				cont = false;
			}
		}
	}


	//////////////////////////////////////////////////////////////////////////////
	//Part  2
	//////////////////////////////////////////////////////////////////////////////
	
	//Reset Everything
	cont = true;
	for (int i = 0; i <10 ; i++)
	{
		while (!Sensors[i].data.empty())
		{
			Sensors[i].data.pop();
		}
		Sensors[i].battery = Battery_Life;
	}

	while (cont)
	{
		//See how long it's been running
		counter2 += 1;

		//Generate random data and add it to the sensor queue
		Random = rand();
		Sensors[0].data.push(Random);

		//Transmit data if sensor is has data
		for (int i = 0; i < 9; i++)
		{
			if (Sensors[i].data.size() >= 10)
			{
				Sensors[i].ON = true;
				while (!Sensors[i].data.empty())
				{
					Sensors[i + 1].data.push(Sensors[i].data.front());
					Sensors[i].data.pop();
					Sensors[i].battery = Sensors[i].battery - 5;
				}
				Sensors[i].ON = false;
			}
		}


		//Battery
		for (int i = 0; i < 10; i++)
		{
			if (Sensors[i].ON == false)
			{
				Sensors[i].battery = Sensors[i].battery - 1;
			}
			else if (Sensors[i].ON == true)
			{
				Sensors[i].battery = Sensors[i].battery - 2;
			}
		}

		//Check battery condition
		for (int i = 0; i < 10; i++)
		{
			if (Sensors[i].battery <= 0)
			{
				cont = false;
			}
		}
	}


	cout << "Cycles before Batteries need to be replaced for way 1: " << counter1 << endl << endl;
	cout << "Cycles before Batteries need to be replaced for way 2: " << counter2 << endl << endl;


	return 0;
}