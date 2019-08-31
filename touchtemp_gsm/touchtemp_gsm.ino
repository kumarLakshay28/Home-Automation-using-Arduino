#include <SoftwareSerial.h>
#include <String.h>
SoftwareSerial SIM900A(10,11);

#define TEMP A1
#define TOUCH A0

int touchvalue = 0;
int tempval=0;
int tempc=0;

void setup() {
//SIM900A.begin (9600);
Serial.begin (9600);
pinMode(TEMP,INPUT);
pinMode(TOUCH,INPUT);
delay(100);
//SIM900A.println ("AT+CNMI=2,2,0,0,0"); 

}

void loop() {
 touchvalue=analogRead(TOUCH);
 tempval=analogRead(TEMP);
 tempc=tempval+23.7;
 Serial.println(tempc);
 delay(2000);
 if(touchvalue>900){
  SendMessageTheft();
 }
 if (tempc>25){
  sendMessageTemp();
 }
 }
void sendMessageTemp()
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

void SendMessageTheft()
{
SIM900A.println ("AT+CMGF=1");
delay (1000);
SIM900A.println ("AT+CMGS=\"+919650437397\"\r"); 
delay (1000);
SIM900A.println ("EMERGENCY THEFT ALERT!!!");
delay (100); 
SIM900A.println ((char)26); 
delay (1000);
}
