/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#define LED_GREEN 3 //  
#define LED_BLUE 5 //  
#define LED_RED 6 //  
#define POTENTIO 0 //

int i =0;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  analogWrite(LED_GREEN, 0); 
  analogWrite(LED_BLUE, 0);
  analogWrite(LED_RED, 0);
  pinMode(POTENTIO, OUTPUT);
  Serial.println("Initialisation");
}

// the loop function runs over and over again forever
void loop() {
  i = analogRead(POTENTIO);
  analogWrite(LED_GREEN, i / 4);   // turn the LED on (HIGH is the voltage level)
  analogWrite(LED_BLUE, i / 4);   // turn the LED on (HIGH is the voltage level)
  analogWrite(LED_RED, i / 4);   // turn the LED on (HIGH is the voltage level)

}
