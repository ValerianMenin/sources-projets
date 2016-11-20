
// Environnement Arduino 1.0.6
// Mise en oeuvre d'un capteur de pression BMP085
// Communication sur bus I2C

#include <Wire.h>

#define A5_SCL 5
#define A4_SDA 4

// Capteur de pression : adressage I2C
// adresse sur le bus I2C du capteur BMP085
#define BMP085_ADDRESS 0x77 //1110111 7 bits de poids le plus fort du device and register address

// Oversampling Setting pour BMP085
// Défini le mode (ultra low power, standard, high, ultra high resolution) = (0, 1, 2, 3)
const unsigned char OSS = 3; 


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

/*---------------------------------------------------------------------------------*/
// Fonctions de gestion du capteur de pression BMP085



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

/*---------------------------------------------------------------------------------*/
// SDA = Data
// SCL = Clock
// Adresse bus i2c page 16 doc Bosch 4.2 (seulement les 7 bits de poids le plus fort = 0x77)

void setup(void)
{ 
  // Votre code à écrire
  Serial.println("***** Demarrage de l'application ****");
  
  Serial.begin(9600);
  Wire.begin();
  
  // Initialidation BMP085 : récupérer les paramètres de calibration du capteur
  // Votre code à écrire
  getbmp085Calibration();
  
}

void loop (void)
{
  
  // Acquisition de la température et de la pression
  // Estimation de l'altitude : optionnel
  // Votre code à écrire
  temperature = bmp085GetTemperature(bmp085ReadUT());
  pressure = bmp085GetPressure(bmp085ReadUP());

  // Gestion de l'affichage des données BMP085
  // Votre code à écrire
  Serial.print("Temperature: ");
  Serial.print(temperature*0.1, DEC);
  Serial.println(" deg C");
  Serial.print("Pressure: ");
  Serial.print(pressure, DEC);
  Serial.println(" Pa");
  Serial.println();

  delay(1000);
}
