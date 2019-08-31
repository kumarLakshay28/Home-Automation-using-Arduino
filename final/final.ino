#include<SoftwareSerial.h>
#include<String.h>

SoftwareSerial SIM900A(10,11);
#define RELAY 3
#define TOUCH A1
#define PIR 6
#define TEMP A0
#define led 8

int vtemp=0;
int tempc=0;
int touchval=0;
int motion=0;
int len=0;

void setup() {
  SIM900A.begin (9600);
  Serial.begin(9600);
  pinMode(RELAY,OUTPUT);
  pinMode(TEMP,INPUT);
  pinMode(PIR,INPUT);
  pinMode(TOUCH,INPUT);
  pinMode(led,OUTPUT);
  }

void loop() {
  readsms();
  touchval=analogRead(TOUCH);
  if(touchval>1000)
  SendMessageTheft();
  motion=digitalRead(PIR);
  motionworking();
 }
void motionworking()
{
  if(motion==HIGH)
  { digitalWrite(led, HIGH);   // turn LED ON
    delay(100);               // delay 100 milliseconds
    Serial.println("Motion detected!"); 
  }
  else
  {
  digitalWrite(led, LOW); // turn LED OFF
      delay(2000);        // delay 200 milliseconds 
  Serial.println("Motion undetected!");
  }
}
void showtemp() 
{
  vtemp=analogRead(TEMP);
  tempc=(vtemp*500)/1024;
  SendMessageTemp();
  
}

String readSIM900A()
{
String buffer;
while (SIM900A.available())
{
char c = SIM900A.read();
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
  Serial.println ("*** RECEIVED A SMS ***");
  len = buffer.length();
  Serial.println (buffer.substring(len-5,len)); 
  if(buffer.indexOf(" LIGHT ON ")>0)
  relayOn();
  else if(buffer.indexOf(" LIGHT OFF ")>0)
  relayOff();
}
  else if(buffer.indexOf(" GET TEMPERATURE")>0)
  showtemp();
  buffer.remove(0,len - 1);
  delay(1000);
  return 0;
}
void relayOn()
{ 
digitalWrite(RELAY,LOW);
Serial.println("light on ");

}
void relayOff()
{
 digitalWrite(RELAY,HIGH);
Serial.println("light off ");

}
void SendMessageTheft()
{
SIM900A.println ("AT+CMGF=1");
delay (1000);
SIM900A.println ("AT+CMGS=\"+918447683437\"\r"); 
delay (1000);
SIM900A.println ("EMERGENCY THEFT ALERT!!!");
delay (100); 
SIM900A.println ((char)26); 
delay (1000);
}
void SendMessageTemp()
{
SIM900A.println ("AT+CMGF=1");
delay (1000);
SIM900A.println ("AT+CMGS=\"+918447683437\"\r"); 
delay (1000);
SIM900A.println ("Temperature is");
SIM900A.println(tempc);
delay (100); 
SIM900A.println ((char)18); 
delay (1000);
}
