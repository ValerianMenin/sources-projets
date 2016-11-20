#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet2.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp2.h>
#include <Twitter.h>
#include <util.h>

#include <SPI.h>

#include <Wire.h>

#define A5_SCL 5
#define A4_SDA 4

#define PUSH 2 // Boutton

// Capteur de pression : adressage I2C
// adresse sur le bus I2C du capteur BMP085
#define BMP085_ADDRESS 0x77 //1110111 7 bits de poids le plus fort du device and register address

// Oversampling Setting pour BMP085
// Défini le mode (ultra low power, standard, high, ultra high resolution) = (0, 1, 2, 3)
const unsigned char OSS = 3; 

int button = 0;

// Coefficients de calibration du capteur de pression BMP085 : déclaration
int ac1, ac2, ac3; 
unsigned int ac4, ac5, ac6;
int b1, b2, mb, mc, md;

// b5 variable utilisée dans bmp085GetTemperature(...) et bmp085GetPressure(...)
// Temperature(...) doit être appellée avant Pressure(...).
long b5; 

short temperature;
long pressure;

// Pour la conversion d'altitude
const float p0 = 101325; // Pression au niveau de la mer (Pa)
float altitude;

byte Adresse_mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //   90 A2 DA 0F FB BE
byte Adresse_ip[] = { 192, 168, 1, 177 };

const int MAX_PAGENAME_LEN = 8; // max characters in page name
char buffer[MAX_PAGENAME_LEN+1]; // additional character for terminating null

// the router's gateway address:
byte gateway[] = { 192, 168, 1, 254 };
// the subnet:
byte subnet[] = { 255, 255, 255, 0 };

EthernetServer MyServer = EthernetServer(80); // HTTP

/*-----------------------------------------------*/
// Acquisition de la valeurs des parametres de calibration

void getbmp085Calibration()
{
  // Votre code à écrire
  ac1 = bmp085ReadInt(0xAA);
  ac2 = bmp085ReadInt(0xAC);
  ac3 = bmp085ReadInt(0xAE);
  ac4 = bmp085ReadInt(0xB0);
  ac5 = bmp085ReadInt(0xB2);
  ac6 = bmp085ReadInt(0xB4);
  b1 = bmp085ReadInt(0xB6);
  b2 = bmp085ReadInt(0xB8);
  mb = bmp085ReadInt(0xBA);
  mc = bmp085ReadInt(0xBC);
  md = bmp085ReadInt(0xBE);

}
/*-----------------------------------------------*/
// Calcul de la température connaissant ut.
// La valeur retournée est exprimée en 1/10 de °C (valeur entiére) puis convertie en °C (valeur réelle)

// Utilise la méthode de calcul du TP page 4
float bmp085GetTemperature(int ut)
{
  // Votre code à écrire  
  long x1, x2;
  
  x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
  x2 = ((long)mc << 11)/(x1 + md);
  b5 = x1 + x2;

  return ((b5 + 8)>>4);  
}
/*-----------------------------------------------*/
// Calcul de la pression en hPa = 100 Pa
// Les paramètres de calibration doivent être connus
// Le calcul de la valeur du coefficient b5 doit être effectué au préalable.
// La valeur retournée est exprimé en Pa (valeur entiére), puis convertie en hPa (valeur réelle).

// Utilise la méthode de calcul du TP page 4
float bmp085GetPressure(unsigned long up)
{
  long x1, x2, x3, b3, b6, p;
  unsigned long b4, b7;
  
  b6 = b5 - 4000;
  // Calcul de B3
 // Votre code à écrire
  x1 = (b2 * (b6 * b6)>>12)>>11;
  x2 = (ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;
  
  // Calcul de B4
  // Votre code à écrire
  x1 = (ac3 * b6)>>13;
  x2 = (b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
  
  // Calcul de B7
  // Votre code à écrire
  b7 = ((unsigned long)(up - b3) * (50000>>OSS));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;
    
  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;
  
  return p;
}

/*-----------------------------------------------*/
// Calcul de l'altitude par rapport au niveau de la mer
// A faire : compensation du calcul
//PARTIE OPTIONNELLE
float estime_altitude (float pression)
{
  // Votre code à écrire
  
}

/*-----------------------------------------------*/
// Lecture d'un octet depuis le capteur BMP085 
// à l'adresse 'address'
char bmp085Read(unsigned char address)
{
 // Votre code à écrire
  unsigned char data;
  
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  
  Wire.requestFrom(BMP085_ADDRESS, 1);
  while(!Wire.available())
    ;
    
  return Wire.read();
}

/*-----------------------------------------------*/
// Lecture de 2 octets depuis le capteur BMP085
// Premier octet : adresse 'address' (octet poids fort)
// Second octet : adresse 'address'+1 (octet poids faible)
int bmp085ReadInt(unsigned char address)
{
  // Votre code à écrire
  unsigned char msb, lsb;
  
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  
  Wire.requestFrom(BMP085_ADDRESS, 2);
  while(Wire.available()<2)
    ;
  msb = Wire.read();
  lsb = Wire.read();
  
  return (int) msb<<8 | lsb;
}
/*-----------------------------------------------*/
// Lecture de la valeur non compensée de la température ut

// Utilise la méthode de calcul du TP page 4
int bmp085ReadUT()
{
  // Votre code à écrire
  unsigned int ut;
  
  // Write 0x2E into Register 0xF4
  // This requests a temperature reading
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(0xF4);
  Wire.write(0x2E);
  Wire.endTransmission();
  
  // Wait at least 4.5ms
  delay(5);
  
  // Read two bytes from registers 0xF6 and 0xF7
  ut = bmp085ReadInt(0xF6);
  //ut = (int) bmp085ReadInt(0xF6)<<8 + bmp085ReadInt(0xF7);
  return ut;
}
/*-----------------------------------------------*/
// Lecture de la valeur non compensée de la pression up
long bmp085ReadUP()
{
  // Votre code à écrire
  unsigned char msb, lsb, xlsb;
  unsigned long up = 0;
  
  // Write 0x34+(OSS<<6) into register 0xF4
  // Request a pressure reading w/ oversampling setting
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(0xF4);
  Wire.write(0x34 + (OSS<<6));
  Wire.endTransmission();
  
  // Attente de la conversion, delay dépend de la valeur de OSS
  delay(2 + (3<<OSS));
  
  // Lecture des registres d'adresses 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
  // Votre code à écrire
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(0xF6); // queues bytes for transmission from a master to slave device (in-between calls to beginTransmission() and endTransmission())
  Wire.endTransmission();
  Wire.requestFrom(BMP085_ADDRESS, 3); // request 3 bytes from BMP085, if != 0 -> error
  
  // attendre que les données soient disponibles
  // Votre code à écrire
  while(Wire.available() < 3) // BMP085 may send less than requested
    ;
  msb = Wire.read();
  lsb = Wire.read();
  xlsb = Wire.read();
  
  up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
  
  return up;
  
}


void setup() {
  
  Serial.begin(9600);
  
  Wire.begin();
  
  Ethernet.begin(Adresse_mac, Adresse_ip, gateway, subnet);
  MyServer.begin();
  
  pinMode(PUSH, INPUT);
  
// print your local IP address:
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
  getbmp085Calibration();
}

void loop() {
  
  temperature = bmp085GetTemperature(bmp085ReadUT());
  pressure = bmp085GetPressure(bmp085ReadUP());
  
  button = digitalRead(PUSH);
  
// listen for incoming clients
  EthernetClient client = MyServer.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          
            if(client.readBytesUntil('/', buffer,sizeof(buffer))){
              if(strcmp(buffer,"POST ") == 0){
                client.find("\n\r"); // skip to the body
                // find string starting with "FormArd", stop on first blank line
                // the POST parameters expected in the form FormArdx=Y
                while(client.findUntil("pinD", "\n\r")){
                  int pin = client.parseInt();       // the pin number
                  int val = client.parseInt();       // 0 or 1
                  pinMode(pin, OUTPUT);
                  if(pin == 9){
                    Serial.println("BANANANANANANANANANANANANA");
                  }
                  Serial.println(val);
                  if(pin == 6){
                    Serial.println("BANANANANANANANANANANANANA");
                  }
                }
            }
           }
          
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 1");  // refresh the page automatically every 1 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html><body>");

          client.println("<head><meta charset=\"utf-8\" /></head>");
          // output the value of temp sensor
            client.print("Temperature = ");
            client.print(temperature*0.1);
            client.print(" °C");
            client.print("<br />Pressure = ");
            client.print(pressure);
            client.println(" Pa <br />");
            
            if (button == HIGH) {
              client.println(" Boutton pressé <br />");
            }  
            else {
              client.println(" Boutton non pressé <br />");
            }
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD9'");
          client.println(" value='0'><input type='submit' value='Light Off'/></form>");
          //create HTML button to turn on pin 9
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD9'");
          client.print(" value='1'><input type='submit' value='Light On'/></form>");

          //Control of Servo
          //Turn Right
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD6'");
          client.println(" value='0'><input type='submit' value='Servo Right'/></form>");
          //Turn Left
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD6'");
          client.print(" value='180'><input type='submit' value='Servo Left'/></form>");
          //Stop
          client.print(
          "<form action='/' method='POST'><p><input type='hidden' name='pinD6'");
          client.print(" value='90'><input type='submit' value='Servo Stop'/></form>");
           
          client.println("</body></html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
