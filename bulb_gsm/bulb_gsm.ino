#include <SoftwareSerial.h>
#include <String.h>

SoftwareSerial SIM900A(10,11); 
#define RELAY  7
int val = 0;
int rly = 0;
int len = 0;

void setup()
{
pinMode (LED_BUILTIN, OUTPUT);
Serial.begin (9600); 
pinMode (RELAY, OUTPUT);
SIM900A.begin (9600);
SIM900A.println ("AT+CNMI=2,2,0,0,0");
delay (100);
SIM900A.print("AT+CMGF=1\r");

}

void loop()
{
   readsms();
  
}
void relayOn()
{ 
digitalWrite(RELAY,HIGH);
Serial.println("light on ");
rly=1;
}
void relayOff()
{
digitalWrite(RELAY,LOW);
Serial.println("light off ");
rly=0;
}
String readSIM900A()
{
String buffer;
while (SIM900A.available())
{
char c = SIM900A.read();
Serial.println(c);
buffer.concat(c); 
delay(10);
}
return buffer;
}

void readsms() 
{
String buffer = readSIM900A();
if (buffer.startsWith("\r\n+CMT: "))
{
Serial.println(buffer);
Serial.println ("*** RECEIVED A SMS ***");
len = buffer.length();
Serial.println (buffer.substring(len-5,len)); 
if(buffer.indexOf("ON")>0)
relayOn();
else if(buffer.indexOf("OFF")>0)
relayOff();
}
buffer.remove (0,len-1);
delay(100);
return 0;
}
