#include <SoftwareSerial.h>
#include "HX711.h";
#include <stdlib.h>
SoftwareSerial nodemcu(7, 8); // nodemcu module connected here

#define DOUT 3
#define CLK 2
HX711 scale(DOUT, CLK);

int rbutton = 6; // this button will be used to reset the scale to 0.
String myString;
String cmessage; // complete message
char buff[10];
float weight;
float calibration_factor = 92280;

void setup() 
{
  Serial.begin(9600);
  nodemcu.begin(9600);
  pinMode(rbutton, INPUT_PULLUP);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
}

void loop() 
{
  scale.set_scale(calibration_factor); //Calibration factor
  
  weight = scale.get_units(5); 
  myString = dtostrf(weight, 3, 2, buff);
  
  cmessage = cmessage + &quot;Weight&quot; + &quot;:&quot; + myString + &quot;Kg&quot;+&quot;,&quot;;
  
  nodemcu.println(cmessage);
  Serial.println(cmessage);
  cmessage = &quot;&quot;;
  
  Serial.println();
  
  if ( digitalRead(rbutton) == LOW)
  {
    scale.set_scale();
    scale.tare(); //Reset the scale to 0
  }
  
}
