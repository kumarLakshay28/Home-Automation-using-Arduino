#include<SoftwareSerial.h>
#include<String.h>

SoftwareSerial SIM900A(10,11);

#define relay 7
#define temp A1
int val=0;
int vtemp=0;
int tempc=0;
int len=0;
int i;
void setup() {
  pinMode(relay,OUTPUT);
  pinMode(temp,INPUT);
  Serial.begin(9600);
  SIM900A.begin(9600);
  SIM900A.println ("AT+CNMI=2,2,0,0,0");
  delay (100);

}

void loop() {
     readsms();
     delay(100);
  
}


String readSIM900A() //function to detect the string received at GSM
{
String buffer;
while (SIM900A.available())
{
char c = SIM900A.read();
buffer.concat(c); 
delay(10);
Serial.println(buffer);
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
if(buffer.indexOf("LIGHT ON")>0)
relayOn();
else if(buffer.indexOf("LIGHT OFF")>0)
relayOff();
else if(buffer.indexOf(" GET TEMPERATURE")>0)
showtemp();
}
buffer.remove (0,len-1);
delay(1000);
return 0;
}
void relayOn() //to turn the relay on
{ 
digitalWrite(relay,LOW);
Serial.println("light on ");
}
void relayOff() //to turn the relay off
{
 digitalWrite(relay,HIGH);
Serial.println("light off ");
}
void showtemp() //function to read LM35 value
{ for(i=0;i<10;i++)
{
  vtemp=analogRead(temp);
  tempc=(vtemp*500)/1024;
  Serial.println(tempc);
  SendMessageTemp();
}
  }
  
void SendMessageTemp() //funtion to send temperature value as sms to user
{
SIM900A.println ("AT+CMGF=1");
delay (1000);
SIM900A.println ("AT+CMGS=\"+918447683437\"\r"); 
delay (1000);
SIM900A.println ("Temperature is");
SIM900A.println(tempc);
delay (100); 
SIM900A.println ((char)26); 
delay (1000);
Serial.println("mansi");
}
