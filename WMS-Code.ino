#include<dht.h>
#include <SoftwareSerial.h>

#define DHT11_PIN 3
#define pirPin 2

dht DHT;
SoftwareSerial mySerial(9, 10);
const int sensor=A1; 
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading
int PIRValue = 0;
const int gasPin = A0; //GAS sensor output pin to Arduino analog A0 pin
char msg;

void setup() {

  pinMode(sensor,INPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.println("send message");
  Serial.println();
  delay(100);
}

char sense_humidity(){
  
  int chk = DHT.read11(DHT11_PIN);
  Serial.println(" Humidity " );
  Serial.println(DHT.humidity);
  Serial.println(" Temparature ");
  Serial.println(DHT.temperature);
  
  if(DHT.temperature>100.00){
    
    return 'b';
    }
    
  if(DHT.temperature<15.00||DHT.temperature>30.00){
    
    return 't';
    }

  else if(DHT.humidity<12.00||DHT.humidity>13.00){
    
    return 'h';
    }
  else{
    
    return '0';
    }
}

char sense_motion(){
      
    PIRValue = digitalRead(pirPin);
    //Serial.println(PIRValue);
    if(PIRValue>0){
      
      Serial.println("Motion Detected");
      return 'm';
      }
    else{
      
      return '0';
      
      }
    }

char sense_gas(){
  Serial.println(analogRead(gasPin));
  delay(1000); // Print value every 1 sec.
  if(analogRead(gasPin)>300)
  {
    return 'g';
    }
    else
    {
      return '0';
      }
}

void SendMessage_Motion(){
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"x\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Motion Alert!");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessage_Gas(){
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"x\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Smoke Alert!");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessage_Temperature(){
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"x\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Temperature Alert!");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessage_Humidity(){
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"x\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Humidity Alert!");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void SendMessage_Fire(){
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"x\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Fire Alert!");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void loop() { // READ DATA

 
char h = sense_humidity();
char g = sense_gas();
char m = sense_motion();

Serial.println(h);
Serial.println(g);
Serial.println(m);

     if(h=='t'){
      SendMessage_Temperature();
      delay(5000);
     }
     
     else if(g=='g'){
      
      SendMessage_Gas();
      delay(5000);
    }
    else if(m=='m'){
      
      SendMessage_Motion();
      delay(5000);
    }
     else if(h=='h'){
      
      SendMessage_Humidity();
      delay(5000);
     }
    else if(h=='b'){
      SendMessage_Fire();
      delay(5000);
      }
}


