#include <SoftwareSerial.h>
#include <String.h>
SoftwareSerial SIM900A(10,11);

#define TEMP A1

int tempval=0;
int tempc=0;

void setup() {
  pinMode(TEMP,INPUT);
  SIM900A.begin (9600);
  SIM900A.println ("AT+CNMI=2,2,0,0,0");
  Serial.begin(9600);
  delay (100);
  }

void loop() {
tempval=analogRead(TEMP);
tempc=tempval+29;
delay(2000);
Serial.println(tempc);
if(tempc>28)
{
SendMessageTemp();
}   
}
void SendMessageTemp()
{
SIM900A.println ("AT+CMGF=1");
delay (1000);
SIM900A.println ("AT+CMGS=\"+918447683437\"\r"); 
delay (1000);
SIM900A.println ("HIGH TEMPERATURE ALERT");
delay (100); 
SIM900A.println ((char)26); 
delay (1000);
}
