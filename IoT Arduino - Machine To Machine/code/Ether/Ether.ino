#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet2.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp2.h>
#include <Twitter.h>
#include <util.h>

#include <SPI.h>

byte Adresse_mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //   90 A2 DA 0F FB BE
byte Adresse_ip[] = { 192, 168, 1, 177 };

// the router's gateway address:
byte gateway[] = { 192, 168, 1, 254 };
// the subnet:
byte subnet[] = { 255, 255, 255, 0 };

EthernetServer MyServer = EthernetServer(80); // HTTP
  
void setup() {
  
  Serial.begin(9600);
  
  Ethernet.begin(Adresse_mac, Adresse_ip, gateway, subnet);
  MyServer.begin();
  
// print your local IP address:
  Serial.println(Ethernet.localIP());
}

void loop() {

}
