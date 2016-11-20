
//zoomkat 10-6-13
//simple button GET with iframe code
//open serial monitor to see what the arduino receives
//use the ' instead of " in html ilnes
//address will look like http://192.168.1.102:84/ when submited
//for use with W5100 based ethernet shields

#include <SPI.h>
#include <Ethernet2.h>


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

#define A5_SCL 5
#define A4_SDA 4

DHT dht(DHTPIN, DHTTYPE);

#define NUM_LEDS 1
ChainableLED leds(8, 9, NUM_LEDS); // Led RGB


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //ethernet shield mac address
byte ip[] = { 192, 168, 1, 177 }; // arduino IP in lan
EthernetServer server(80); //server port

String readString;


const int colorR = 0;
const int colorG = 255;
const int colorB = 0;

int button = 0;
int pressCount = 0;

//////////////////////

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  leds.init();

  pinMode(4, OUTPUT);       // LED on pin 4
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop(){
  button = digitalRead(PUSH);
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string
          readString += c;
          //Serial.print(c);
        }

        //if HTTP request has ended
        if (c == '\n') {

          ///////////////
          Serial.println(readString); //print to serial monitor for debuging

          //now output HTML data header
             if(readString.indexOf('?') >=0) { //don't send new page
               client.println("HTTP/1.1 204 OK");
               client.println();
               client.println(); 
             }
             else {
          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println("Refresh: 2");  // refresh the page automatically every 2 sec
          client.println();

          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<TITLE>Arduino GET test page</TITLE>");
          client.println("<meta charset=\"utf-8\" />");
          client.println("</HEAD>");
          client.println("<BODY>");

          client.println("<H1>Contrôle LED verte pin 3</H1>");
         
          client.println("<a href='/?on3' target='inlineframe'>ON</a>");
          client.println("<a href='/?off3' target='inlineframe'>OFF</a>");
          
          client.println("<H1>Contrôle LED rouge pin 4</H1>");
         
          client.println("<a href='/?on4' target='inlineframe'>ON</a>");
          client.println("<a href='/?off4' target='inlineframe'>OFF</a>");
          
          client.println("<H1>Contrôle LED bleu pin 5</H1>");
         
          client.println("<a href='/?on5' target='inlineframe'>ON</a>");
          client.println("<a href='/?off5' target='inlineframe'>OFF</a>");
          
          client.println("<H1>Contrôle LED RGB pin 2</H1>");
          
          client.println("<a href='/?BLUE' target='inlineframe'>BLUE</a>");
          client.println("<a href='/?RED' target='inlineframe'>RED</a>");

          client.println("<IFRAME name=inlineframe style='display:none'>");         
          client.println("</IFRAME>");
          
          client.println("<H1>Potentiomètre sur A0</H1>");
          
          client.println("Valeur = ");
          client.println(analogRead(POTENTIO));
          client.println("<br />");
          
          client.println("<H1>Photocell sur A1</H1>");
          
          client.println("Valeur = ");
          client.println(analogRead(PHOTO));
          client.println("<br />");
          
          client.println("<H1>Humidité sur A3</H1>");
          
          client.println("Valeur = ");
          client.println(dht.readHumidity());
          client.println("<br />");
          
          client.println("<H1>Compte bouton</H1>");
          
          for(int pa = 0; pa < pressCount; pa++){
            client.println("啪");
            client.println("<br />");
          }




          client.println("</BODY>");
          client.println("</HTML>");
             }

          delay(1);
          //stopping client
          client.stop();

          ProcessCheckbox(client);
          ProcessCheckboxRGB(client);
          
          if (button == HIGH) {
            pressCount++;
          }
          
          //clearing string for next read
          readString="";

        }
      }
    }
  }
}

void ProcessCheckbox(EthernetClient cl)
{
  ///////////////////// control arduino pin
  if(readString.indexOf("on4") >0)//checks for on
  {
    digitalWrite(4, HIGH);    // set pin 4 high
    Serial.println("Led On");
  }
  if(readString.indexOf("off4") >0)//checks for off
  {
    digitalWrite(4, LOW);    // set pin 4 low
    Serial.println("Led Off");
  }
  
  if(readString.indexOf("on3") >0)//checks for on
  {
    digitalWrite(3, HIGH);    // set pin 4 high
    Serial.println("Led On");
  }
  if(readString.indexOf("off3") >0)//checks for off
  {
    digitalWrite(3, LOW);    // set pin 4 low
    Serial.println("Led Off");
  }
  
  if(readString.indexOf("on5") >0)//checks for on
  {
    digitalWrite(5, HIGH);    // set pin 4 high
    Serial.println("Led On");
  }
  if(readString.indexOf("off5") >0)//checks for off
  {
    digitalWrite(5, LOW);    // set pin 4 low
    Serial.println("Led Off");
  }
  
}

void ProcessCheckboxRGB(EthernetClient cl)
{
  ///////////////////// control arduino pin
  if(readString.indexOf("BLUE") >0)//checks for on
  {
    leds.setColorRGB(0, 0, 0, 255); 
  }
  if(readString.indexOf("RED") >0)//checks for off
  {
    leds.setColorRGB(0, 255, 0, 0); 
  }
}


