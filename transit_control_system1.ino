#include <Wire.h>
//Button to normally open close the gate and 
//autoomatically showing next stop.
int openCloseNrmlButton = 5;

//Button to open close the gate in emergency 
//doesn't change next stop
int openCloseEmergencyButton = 3;

//Requesting stop
int stopRequestedButton = 2;

//change the way bus is going
int directionChangeButton = 6;

//bool that turns true when button is pressed once and false when it is pressed again
bool isOpening = false;
bool wayChange = false;

// Ultrasonic sensor pins
int echoPin=4;//It receives the reflected ultrasonic pulse after it has bounced off an object.
int triggerPin=7;//It sends out a short pulse to initiate the ultrasonic ranging.
int distance;
int time;

int i=0;
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  // Set button pins as inputs
  pinMode(openCloseNrmlButton, INPUT);
  pinMode(openCloseEmergencyButton, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(triggerPin,OUTPUT);
}

void loop()
{
  // Ultrasonic sensor measurements
  //This line sets the triggerPin to a LOW state.
  digitalWrite(triggerPin,LOW);
  //short delay to ensure that the trigger pin stays LOW for a brief moment before sending a HIGH pulse. Ultrasonic sensors typically require a short LOW state before triggering a HIGH state.
  delay (2);
  //This line sets the triggerPin to a HIGH state. 
  digitalWrite(triggerPin,HIGH);
  delay (10);
  digitalWrite(triggerPin,LOW);
  //This line uses the pulseIn function to measure the duration of the pulse that is received by the echo pin
  time=pulseIn(echoPin,HIGH);
  //Using the time duration of the received pulse, this line calculates the distance to the object in front of the ultrasonic sensor. 
  distance=(time/20)*0.0343;
  //the calculated distance is printed to the Serial Monitor. 
  Serial.println(distance);
  
  
  // Check if the normal open/close button is pressed
  if (digitalRead(openCloseNrmlButton) == HIGH) 
  {

    isOpening = !isOpening; // Toggle between opening and closing
    if (isOpening)
    {
      // Transmit command for normal opening
      Wire.beginTransmission(4);
      Wire.write(1);
      Wire.endTransmission(); // stop transmitting
      delay(1000);            // debounce delay
    }
    else 
    {
      // Transmit command for normal closing
      Wire.beginTransmission(4);
      Wire.write(3);
      Wire.endTransmission(); // stop transmitting
      delay(1000);            // debounce delay
      
      Wire.beginTransmission(4);
      Wire.write(4);
      Wire.endTransmission(); // stop transmitting
      delay(1000);            // debounce delay
  
    }
    if(distance<=4 && isOpening){//if measured distance is less then 4 by a ultrasonic sensor then it transmits 2.
      	Wire.beginTransmission(4);
      	Wire.write(2);
      	Wire.endTransmission(); // stop transmitting
      	delay(1000);            // debounce delay
      }
  }
  else if (digitalRead(openCloseEmergencyButton) == HIGH) // openCloseEmergencyButton button pressed
  {

    isOpening = !isOpening; // Toggle between opening and closing
    if (isOpening)
    {
      Wire.beginTransmission(4);
      //Transmit some messange to slave arduino for the action to take place
      Wire.write(9);
      Wire.endTransmission(); // stop transmitting
      delay(1000);            // debounce delay
    }
    else
    {
      Wire.beginTransmission(4);
      Wire.write(5);
      Wire.endTransmission(); // stop transmitting
      delay(1000);            // debounce delay
    }
  }else if (digitalRead(stopRequestedButton) == HIGH)//Stop requested button pressed
  {
  	  Wire.beginTransmission(4);
      Wire.write(6);
      Wire.endTransmission(); // stop transmitting
      delay(1000);            // debounce delay
  
  }else if (digitalRead(directionChangeButton) == HIGH)// direction change button pressed
  {
    wayChange=!wayChange;//toggle between two ways each time it is pressed
    if(wayChange){
  	  Wire.beginTransmission(4);
      Wire.write(7);
      Wire.endTransmission(); // stop transmitting
      delay(1000);            // debounce delay
    }else{
      Wire.beginTransmission(4);
      Wire.write(8);
      Wire.endTransmission(); // stop transmitting
      delay(1000);            // debounce delay
    }
  }
}

