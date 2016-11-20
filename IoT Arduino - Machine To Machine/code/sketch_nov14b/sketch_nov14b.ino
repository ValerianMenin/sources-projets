
//zoomkat 10-6-13
//simple button GET with iframe code
//open serial monitor to see what the arduino receives
//use the ' instead of " in html ilnes
//address will look like http://192.168.1.102:84/ when submited
//for use with W5100 based ethernet shields

#include <SPI.h>
#include <Ethernet2.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //ethernet shield mac address
byte ip[] = { 192, 168, 1, 177 }; // arduino IP in lan
//byte gateway[] = { 192, 168, 1, 1 }; // internet access via router
//byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

String readString;

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
  pinMode(4, OUTPUT);       // LED on pin 4
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop(){
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
               client.println("HTTP/1.1 204 Zoomkat");
               client.println();
               client.println(); 
             }
             else {
          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<TITLE>Arduino GET test page</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");

          client.println("<H1>Zoomkat's simple Arduino button</H1>");
         
          client.println("<a href='/?on1' target='inlineframe'>ON</a>");
          client.println("<a href='/?off' target='inlineframe'>OFF</a>");

          client.println("<IFRAME name=inlineframe style='display:none'>");         
          client.println("</IFRAME>");

          client.println("</BODY>");
          client.println("</HTML>");
             }

          delay(1);
          //stopping client
          client.stop();

          ProcessCheckbox(client);
          
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
  if(readString.indexOf("on1") >0)//checks for on
  {
    digitalWrite(4, HIGH);    // set pin 4 high
    Serial.println("Led On");
  }
  if(readString.indexOf("off") >0)//checks for off
  {
    digitalWrite(4, LOW);    // set pin 4 low
    Serial.println("Led Off");
  }
}


