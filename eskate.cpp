#define Phoenix_No_WPI // remove WPI dependencies
#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.hpp"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include "ctre/phoenix/cci/Unmanaged_CCI.h"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
// #include <SDL2/SDL.h>
#include <math/PIDController.h>
#include <cmath>

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;
using namespace std;

// CAN Bus
string interface = "can0";

// Initialize the Falcon 500 with CAN ID "0"
TalonFX falcon(0, interface);

/** simple wrapper for code cleanup */
void delay(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

/** Instruct the skateboard to move forward. Speed unit is in miles per hour. */
void move(int speed) {

	// Convert desired speed in miles per hour to the Falcon's
	// native sensor units.
	double coefficient = 2048.0 * 10.0 / 2048.0 * (4.0 * M_PI) * 63360.0 / 3600.0;
	falcon.Set(ControlMode::Velocity, speed * coefficient);
}

int main(int argc, char *argv[]) {

	cout << "Initializing CAN Bus..." << endl << endl;
	
	delay(5000);

	// Register the CAN Bus
	ctre::phoenix::platform::can::RegisterCANbus(interface.c_str());

	delay(5000);

	cout << "Configuring Falcon 500..." << endl << endl;

	// General configuraton.
	// Set inverted so green output = forward motion.
	// Set coast as neutral mode for 0 resistance.
	falcon.SetInverted(false);
	falcon.SetNeutralMode(NeutralMode::Brake);

	// Configure motor-based PID values.
	// Ensures that if we don't hit the desired output,
	// the motor will try to make up for that error.
	falcon.Config_kP(0, 0.25);
	falcon.Config_kI(0, 0.0025);
	falcon.Config_kD(0, 0.1);

	while (true) {

		// Enable the devices present on the CTRE CAN Bus.
		ctre::phoenix::unmanaged::Unmanaged::FeedEnable(1000);

		double output = stod(argv[0]);

		// Continuously set the Falcon at 10% throtle output.
		falcon.Set(ControlMode::PercentOutput, output);
		
		// We must convert the Falcon's internal encoder resolution to inches travelled.
		// This rough, hacky formula is based on the circumference of the board's wheels.
		// For simplicity's sake, the belt ratio is not taken into account.
		// (10) / (falcon_sensor_units_per_rotation) * (wheel_diameter * PI)
		// double ticksToInches = 10.0 / 2048.0 * (4.0 * M_PI);

		// Convert our velocity from inches per second to miles per hour.
		// (falcon_sensor_units_per_100ms) * (ticksToInches) / (inches_per_mile) / (seconds_per_hour)
		// double vel = falcon.GetSelectedSensorVelocity(0) * ticksToInches / 63360.0 / 3600.0;
	}

	return 0;
}
