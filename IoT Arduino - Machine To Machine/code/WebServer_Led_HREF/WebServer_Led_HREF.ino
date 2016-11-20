/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 mofied again 18/11/2016

 */

#include <SPI.h>
#include <Ethernet2.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

String HTTP_req;          // stores the HTTP request
boolean LED_status = 0;   // state of LED, off by default
boolean LEDCheck_status= 0;

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


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        HTTP_req += c;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>Arduino LED Control</title>");
          client.println("</head>");
          client.println("<body>");
          
          client.println("<h1>LED</h1>");
          client.println("<p>Click to switch LED on and off.</p>");
          client.println("<a href=/?on >ON</a>");
          client.println("<a href=/?off >OFF</a>");
//          client.println("<form method=\"get\">");
          ProcessCheckbox(client);
//          client.println("</form>");          
          
          client.println("</body>");
          client.println("</html>");
          
          //Serial.print(HTTP_req);
          HTTP_req = "";    // finished with request, empty string
          
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

// switch LED and send back HTML for LED checkbox
//void ProcessCheckbox(EthernetClient cl)
//{
//    if (HTTP_req.indexOf("LED4=4") > -1) {  // see if checkbox was clicked
//        // the checkbox was clicked, toggle the LED
//        LEDCheck_status = 1;
//    }
//    else{
//        LEDCheck_status = 0;
//    }
//    
//
//          
//    if (LEDCheck_status) {    // switch LED on
//        digitalWrite(4, HIGH);
//        // checkbox is checked
//        cl.println("<input type=\"checkbox\" name=\"LED4\" value=\"4\" \onclick=\"submit();\" checked>LED4");
//    }
//    else {              // switch LED off
//        digitalWrite(4, LOW);
//        // checkbox is unchecked
//        cl.println("<input type=\"checkbox\" name=\"LED4\" value=\"4\" \onclick=\"submit();\">LED4");
//    }
//}

void ProcessCheckbox(EthernetClient cl)
{
    if (HTTP_req.indexOf("on") > -1) {  // see if checkbox was clicked
        Serial.print("On est on");
        digitalWrite(4, HIGH);
    }
    if (HTTP_req.indexOf("off") > -1) {  // see if checkbox was clicked
        Serial.print("On est off");
        digitalWrite(4, LOW);
    }
}
