#include <SPI.h>
#include <String.h>
#include <Ethernet.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = { 192, 168, 1, 177 };
EthernetServer server(8090);//
int led = 5;
String readString = String(30);
boolean statusLed = false;
void setup() {
  // put your setup code here, to run once:
Ethernet.begin(mac,ip);
pinMode(led, OUTPUT);
Serial.begin(9600);
}

void loop() {
  EthernetClient client = server.available();
  if (client){
    while(client.connected())
    {
      if(client.available())
      {
        char c = client.read();
        if(readString.length() < 30)
        {
          readString += (c);
        }
        if (c == '\n')
        {
          if(readString.indexOf("TurnOnLed")>=0)
          {
            digitalWrite(led, HIGH);
            statusLed = true;
          }
          if(readString.indexOf("TurnOffLed")>=0)
          {
            digitalWrite(led, LOW);
            statusLed = false;
          }
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type; text/html");
          client.println();
          client.print("<font size='20'>");
          if(statusLed){
            client.print("Led Switched On");
          }
          else
          {
            client.print("Led Switched Off");
          }
          readString="";
          client.stop();
          }
        }
      }
    }
    }