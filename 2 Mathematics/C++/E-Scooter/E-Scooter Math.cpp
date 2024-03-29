// Electric-Scooter-Mathematics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <math.h>

int getInteger()
{
	while (true)
	{
		int x;
		std::cin >> x;
		std::cin.ignore(32767, '\n');

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
			return x;
	}
}

double getDouble()
{
	while (true)
	{
		double x;
		std::cin >> x;
		std::cin.ignore(32767, '\n');

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
			return x;
	}
}

int main()
{
	std::cout << "\n----------------------- Electric Scooter ----------------------\n" << std::endl;

	std::cout << "  Drive sprocket teeth: ";
	int driveTooth = getInteger();

	std::cout << "  Driven sprocket teeth: ";
	int followTooth = getInteger();

	float gearRatio = static_cast<float>(followTooth) / driveTooth;
	std::cout << std::setprecision(6);
	std::cout << "\n  Gear ratio = " << gearRatio << std::endl;
	std::cout << "  Motor RPM = " << motorRPM << std::endl;

	double wheelRPM = motorRPM / gearRatio;
	std::cout << "  Wheel RPM = " << wheelRPM << std::endl;

	std::cout << std::setprecision(4);

	double speedMS = (M_PI * wheelDia * wheelRPM) / 60;
	std::cout << "\n  Theoretical speed (excl. drag) = " << speedMS << " m/s" << std::endl;

	double speedKMH = speedMS * 3.6;
	std::cout << "  Theoretical speed (excl. drag) = " << speedKMH << " km/h" << "\t= " << speedKMH * kmh_mph_ratio << " mph" << std::endl;

	double motorTorque = motorWatt / ((2 * M_PI * motorRPM) / 60);
	std::cout << "\n  Motor torque (excl. losses) = " << motorTorque << " Nm" << std::endl;

	double wheelTorque = motorTorque * gearRatio;
	std::cout << "  Wheel torque (excl. losses) = " << wheelTorque << " Nm" << std::endl;

	std::cout << "\n-------------------------- Situation --------------------------\n" << std::endl;

	std::cout << std::resetiosflags(std::ios::fixed | std::ios::showpoint);

	{
		std::cout << "  Driving up hill with percentage (%): ";
		double percentage = getDouble();
		std::cout << "  At a constant speed of (km/h): ";
		double velocity = getDouble();
		std::cout << "  Persons weight (kg): ";
		double personWeight = getDouble();
		double mass = personWeight + scooterWeight;

		double necessaryWatt = mass * gravity * sin(atan(percentage / 100)) * (velocity / 3.6);
		std::cout << "\n  Necessary wattage to go up that hill = " << necessaryWatt << " W" << std::endl;

		double necessaryTorque = mass * gravity * sin(atan(percentage / 100)) * (wheelDia / 2);
		std::cout << "  Necessary torque to go up that hill = " << necessaryTorque << " Nm" << std::endl;

		if (wheelTorque > necessaryTorque)
			std::cout << "\n  We've got enough torque to go up that hill!\n" << std::endl;
		else {
			std::cout << "\n  Not enough torque to go up that hill..." << std::endl;
			std::cout << "  Possible solutions:" << std::endl;
			std::cout << "\t> Adjust the gear ratio" << std::endl;
			std::cout << "\t> Make the wheels diameter smaller" << std::endl;
			std::cout << "\t> Buy a bigger, much stronger, motor and battery" << std::endl;
			std::cout << "\t> Never try getting up that hill" << std::endl;
			std::cout << "\t> Go to a planet with less gravity" << std::endl;
			std::cout << "\t> Lose weight\n" << std::endl;
		}

		std::cout << "---------------------------------------------------------------\n" << std::endl;
	}

	system("pause");
	return 0;
}
