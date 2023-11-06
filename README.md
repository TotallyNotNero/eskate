# eskate
eskate is my project developed during my time with Minnetonka Research, aiming to create & develop an electric skateboard for use in urban and college campus transportation.
During my years in High School, I participated in the FIRST Robotics Competition, so when developing this project I wanted to use hardware that I was familiar with.
# Project Goals
My goals for this project are three-fold:
- Safety, without sacrificing speed
- Range, without sacrificing battery longevity
- Cost, without sacrificing build quality
# Hardware Components
This project uses two DeWalt 20V Cordless drill batteries, wired in parallel to two Step down DC converters.
One converter is 12V, while the other one is 5V power.
From there, three major hardware components are used:
- CTRE Falcon 500 brushless electric DC motor
- CTRE HERO Gadgeteer development board
- Raspberry Pi 4 8GB single-board computer

The three previously mentioned components make up the bulk of the project. The Falcon 500 motor communicates over the CAN network, and the HERO board serves as
a CAN to USB adapter, with the Falcon 500 plugging into the HERO's CAN ports, and the HERO plugging directly into the Raspberry Pi's USB port.
From there on, the Raspberry Pi serves as the brain of the operations, running the code required to control the motor.

# Software Components
This project also uses some software components:
- Visual Studio Code, or a comparable IDE for writing the code
- Phoenix Framework, including the Linux libraries requried to run CTRE devices in a Linux environment
- HERO LifeBoat, for flashing the firmware required to convert the HERO into a CAN to USB adapter.

# Code
The skateboard, for maximum ease-of-use, utilizes a PID controller for controlling motor output when the user
chooses to use "cruise control" when selecting the button mapped to the cruise control function.
For safety, the trigger must be held down when pressing the cruise control button. To disable,
press the button again and the board will coast down in speed. The code for all the math in this project is
located in the `math/` folder.

# Links / References
My final Minnetonka Research proposal is linked here.

My blogpost running through my processes & in-depth thinkings during the skateboard's creation is linked here.
