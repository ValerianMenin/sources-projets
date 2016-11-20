#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;


#include <DHT.h>
#include <ChainableLED.h>

// Pin positions
#define LED_GREEN 3 //  
#define LED_BLUE 5 //  
#define LED_RED 6 //  
#define POTENTIO 0 // Potentiomètre
#define PUSH 2 // Boutton
#define PHOTO 1 // Photocell
#define DHTPIN A2 // Capteur Humidité
#define DHTTYPE DHT22

#define NUM_LEDS 1
ChainableLED leds(8, 9, NUM_LEDS); // Led RGB

DHT dht(DHTPIN, DHTTYPE);

int i =0;
int button = 0;
int selected_led = -1;
int pressCount = 0;
int photoRead = 0;
float humi = 0.0;
float temp = 0.0;

const int colorR = 0;
const int colorG = 255;
const int colorB = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  leds.init();
  
  dht.begin();
  
  lcd.begin(16, 2);  
  lcd.setRGB(colorR, colorG, colorB);
  lcd.print("hello, world!");
  
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  analogWrite(LED_GREEN, 0); 
  analogWrite(LED_BLUE, 0);
  analogWrite(LED_RED, 0);
  pinMode(POTENTIO, OUTPUT);
  pinMode(PUSH, INPUT);
  pinMode(PHOTO, OUTPUT);
  pinMode(DHTPIN, OUTPUT);
  Serial.println("Initialisation");
}

// the loop function runs over and over again forever
void loop() {
  // read the state of the pushbutton value:
  button = digitalRead(PUSH);
  photoRead = analogRead(PHOTO);  
  humi = dht.readHumidity();
  temp = dht.readTemperature();  
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (button == HIGH) {
    pressCount++;
    delay(300);
  }
  
  if(pressCount%3 == 0){
    selected_led = 3;
    lcd.setRGB(0, 255, 0);
  }
  
  if(pressCount%3 == 1){
    selected_led = 5;
    lcd.setRGB(0, 0, 255);
  }
  
  if(pressCount%3 == 2){
    selected_led = 6;
    lcd.setRGB(255, 0, 0);
  }
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  lcd.print("Humi: "); 
  lcd.print(humi);
  lcd.print(" %   ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: "); 
  lcd.print(temp);
  lcd.println(" *C  ");
  
  /*
  Serial.print("Humidity: "); 
  Serial.print(humi);
  Serial.print(" % \t");
  Serial.print("Temp: "); 
  Serial.print(temp);
  Serial.println(" *C");
  */
  
  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
  photoRead = (1023 - photoRead)/4;
  i = analogRead(POTENTIO);
  
  //leds.setColorHSB(0, photoRead, 1.0, 0.5);
  leds.setColorRGB(0, 255-photoRead, 255-photoRead, 255-photoRead); 
  
  analogWrite(selected_led, i / 4);   // turn the LED on (HIGH is the voltage level)


}
