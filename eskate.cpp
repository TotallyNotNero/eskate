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

int main() {

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

		PIDController PID = PIDController(0.1, 0.001, 0.01, 0.1, 0.01, 0.5);
		double output = PID.calculate(0, 0.2);

		// Continuously set the Falcon at 10% throtle output.
		falcon.Set(ControlMode::PercentOutput, output);
	}

	return 0;
}
