#ifndef _PID_SOURCE_
#define _PID_SOURCE_

#include <iostream>
#include <cmath>
#include "PIDController.h"

using namespace std;

class PIDClass {
    public:
        PIDClass(double dt, double max, double min, double Kp, double Kd, double Ki );
        ~PIDClass();
        double calculate(double setpoint, double pv );

    private:
        double _dt;
        double _max;
        double _min;
        double _Kp;
        double _Kd;
        double _Ki;
        double _pre_error;
        double _integral;
};

PIDController::PIDController(double dt, double max, double min, double Kp, double Kd, double Ki) {
    pidcl = new PIDClass(dt,max,min,Kp,Kd,Ki);
}

double PIDController::calculate(double setpoint, double pv) {
    return pidcl->calculate(setpoint,pv);
}

PIDController::~PIDController() {
    delete pidcl;
}

PIDClass::PIDClass(double dt, double max, double min, double Kp, double Kd, double Ki) :
    _dt(dt),
    _max(max),
    _min(min),
    _Kp(Kp),
    _Kd(Kd),
    _Ki(Ki),
    _pre_error(0),
    _integral(0) {
}

double PIDClass::calculate(double setpoint, double pv ) {
    
    // Calculate error
    double error = setpoint - pv;

    // Calculate proportional component based on error
    double Pout = _Kp * error;

    // Calculate integral component with a trapezoidal Riemann sum
    _integral += error * _dt;
    double Iout = _Ki * _integral;

    // Calculate derivative component based on the current error and last error
    double derivative = (error - _pre_error) / _dt;
    double Dout = _Kd * derivative;

    // Calculate total output
    double output = Pout + Iout + Dout;

    // Clamp the output
    if(output > _max)
        output = _max;
    else if(output < _min)
        output = _min;

    // Save error to previous error for the next frame
    _pre_error = error;

    return output;
}

#endif