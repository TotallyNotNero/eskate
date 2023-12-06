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
#include <SDL2/SDL.h>

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;
using namespace std;


string interface = "can0";
TalonFX falcon(0, interface);

void initialize() {
	// Set the Falcon to inverted
	// so forward is green light.
	falcon.SetInverted(true);

	// Set neutral mode to coast initially
	// should it be brake? hmm
	falcon.SetNeutralMode(NeutralMode::Coast);

	cout << "Initialization Complete." << endl;
}

void drive(double power) {
	falcon.Set(ControlMode::PercentOutput, power);
}

/** simple wrapper for code cleanup */
void sleepApp(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main() {	
	// Comment out the call if you would rather use the automatically running diag-server, note this requires uninstalling diagnostics from Tuner. 
	// c_SetPhoenixDiagnosticsStartTime(-1); // disable diag server, instead we will use the diag server stand alone application that Tuner installs

	// setup Falcon
	initialize();

	while (true) {
		drive(0.2);
	}

	return 0;
}
