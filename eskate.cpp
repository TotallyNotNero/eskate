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
// #include <math/RTime.h>
// #include <math/PIDController.h>

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;
using namespace std;

// CAN Bus
string interface = "can0";

/** simple wrapper for code cleanup */
void delay(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main() {

	printf("Initializing CAN Bus...");
	
	delay(5000);

	// Register the CAN Bus
	ctre::phoenix::platform::can::RegisterCANbus(interface.c_str());

	printf("Initializing Falcon 500...");

	delay(5000);

	// Initialize the Falcon 500 with CAN ID "0"
	TalonFX falcon(0, interface);

	// General configuraton.
	// Set inverted so green output = forward motion.
	// Set coast as neutral mode for 0 resistance.
	falcon.SetInverted(false);
	falcon.SetNeutralMode(NeutralMode::Brake);

	while (true) {

		printf("going");

		// Continuously set the Falcon at 20% throtle output.
		falcon.Set(ControlMode::PercentOutput, 0.9);
	}

	return 0;
}
