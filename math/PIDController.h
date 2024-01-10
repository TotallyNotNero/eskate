#ifndef _PID_H_
#define _PID_H_

class PIDClass;

class PIDController {
    public:
        // Kp -  proportional gain
        // Ki -  Integral gain
        // Kd -  derivative gain
        // dt -  loop interval time
        // max - maximum value of manipulated variable
        // min - minimum value of manipulated variable
        PIDController(double dt, double max, double min, double Kp, double Kd, double Ki);

        // Returns the manipulated variable given a setpoint and current process value
        double calculate(double setpoint, double pv);
        ~PIDController();

    private:
        PIDClass *pidcl;
};

#endif