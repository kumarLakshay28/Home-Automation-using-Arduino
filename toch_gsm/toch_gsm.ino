#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); 
int analogPin = A0;
int touchValue = 0;

void setup()
{
mySerial.begin (9600);
Serial.begin (9600);
delay (100);

}
void loop()
{
touchValue = analogRead(analogPin); 
Serial.print (touchValue); 
Serial.print ("\n");
if (touchValue >1000)
SendMessage();
}
void SendMessage()
{
mySerial.println ("AT+CMGF=1");
delay (1000);
mySerial.println ("AT+CMGS=\"+918882776597\"\r"); 
delay (1000);
mySerial.println ("EMERGENCY THEFT ALERT!!!");
delay (100); 
mySerial.println ((char)26); 
delay (1000);
}
