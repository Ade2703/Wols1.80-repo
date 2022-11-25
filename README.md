# Wols1.80
Robot vacuum cleaner made with Arduino
#Description
Wols 1.80 is a robot vacuum cleaner made with Arduino that uses a SLAM algorithm to map the environment in which the device operates.
The code uses a multi tasking library to overcome the limits of the Arduino UNO board and some sensors to influence the device's behaviour.
#Dependencies
* Arduino UNO board
* [AceRoutine](https://github.com/bxparks/AceRoutine) library
* Motor Module: two [28BYJ-48](https://www.mouser.com/datasheet/2/758/stepd-01-data-sheet-1143075.pdf) that are manageable without any particular library; and we are also using a [ULN2003](https://www.hadex.cz/spec/m513.pdf)
* Ultrasonic Sensor Module: The utilized ultrasonic sensor is [HC-SR04](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf), manageable trough the NewPing library
* SLAM / Room-Mapping Algorithm Module:
* Power Supply Module: For this project we used a "power pack" composed by battery(3.7V, 10.000mAh, 37.4Wh) and by 4 more batteries(3.7V, 2700mAh, 10Wh) plasced in parallel in order to supply the right amount of ampere
* Step-up Module: The step-up module practically is a board that is able to the tension from 3.7V to 5V. In this case we used a board that is able to supply 5V1A / 5V2A in its output doors
* Aspiration Module:
* Bluetooth Module:
* SD Card Module:
 
