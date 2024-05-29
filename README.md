Project Name: Arduino-Based Automated Bus Control System

Description:
The Arduino-Based Automated Bus Control System is a sophisticated project that simulates the operations of a bus using two Arduino microcontrollers. This project incorporates multiple hardware components, such as motors, LEDs, buttons, an ultrasonic sensor, and a display screen, to create an interactive and automated bus system prototype. Below is a detailed explanation of the project's features and functionality:

Key Features:
LCD Display:

A 16x2 LiquidCrystal display is used to show the names of bus stops and indicate the bus's direction. It provides passengers with real-time information about the current and next stops.
Motor-Controlled Doors:

Two servo motors control the opening and closing of the front and back doors. The motors are programmed to open the doors fully and close them based on button presses and sensor inputs.
LED Indicators:

Green and red LEDs are used to indicate the status of the doors. Green LEDs glow when the doors are fully open, signaling safe entry and exit, while red LEDs illuminate when the doors are closing, ensuring passenger safety.
Buttons with Different Functionalities:

Normal Open/Close Button: Opens or closes the doors normally and updates the bus stop information.
Emergency Open/Close Button: Opens or closes the doors in an emergency without updating the bus stop.
Stop Request Button: Activates a buzzer to request a stop, indicating a passenger's request to the driver.
Direction Change Button: Changes the direction of the bus and updates the bus stops displayed on the screen accordingly.
Ultrasonic Sensor:

An ultrasonic sensor measures the distance to an object in front of the bus. If the distance is less than or equal to 4 cm and the door is opening, it triggers the back door to open automatically.
Buzzer:

A buzzer sounds when a stop is requested, providing an audible alert to the driver. The buzzer is deactivated once the doors open at the next stop.
How It Works:
Arduino 1 (Main Controller):
Setup:

Initialize the pins for the buttons, ultrasonic sensor, and I2C communication.
Configure the pins for input or output as needed.
Loop:

Continuously measure the distance using the ultrasonic sensor and print the value to the Serial Monitor.
Check the status of each button:
Normal Open/Close Button: Toggles the door state and transmits the appropriate command to the second Arduino. If the door is opening and the distance is less than or equal to 4 cm, it also triggers the back door.
Emergency Open/Close Button: Toggles the door state and sends the corresponding command for emergency operations.
Stop Requested Button: Sends a command to activate the buzzer and indicate a stop request on the LCD.
Direction Change Button: Toggles the direction of the bus and updates the LCD to show the new direction and next stop.

Arduino 2 (Slave Controller):
Setup:

Initialize the LCD, servo motors, LEDs, and buzzer.
Register the receiveEvent function for I2C communication to handle commands from the main controller.
Loop:

The loop function remains empty as actions are performed based on received commands.
receiveEvent:

Handle various commands received from the main controller:
Open/Close Doors: Control the servo motors to open or close the doors.
Emergency Operations: Open both doors simultaneously in case of emergency.
Stop Request: Display "Stop Requested" on the LCD and activate the buzzer.
Direction Change: Update the LCD to show the direction and next stop based on the bus's current route.
