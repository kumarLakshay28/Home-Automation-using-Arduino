
int led=6;
int sensor=2;
int val=0;

void setup() {
pinMode(led,OUTPUT);
pinMode(sensor,INPUT);
Serial.begin(9600);  

}

void loop() {
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);               // delay 100 milliseconds
    Serial.println("Motion detected!"); 
    
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(2000);             // delay 200 milliseconds 
      }
  }
