#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(8, 10);//CE, CSN
const byte pipe[6] = "00001";// Radio pipe address for the 2 nodes to communicate.

//D5 D6 D3 D9 PWM Outputs

const int EN1 = 5;
const int EN2 = 6;

const int M11 = 4; 
const int M12 = 3;
const int M21 = 2;
const int M22 = 7;
int y = 0;
uint8_t dataPacket[9];
//1=Left Y
//2=Left X
//3=Right Y
//4=Right X
//5=SW 1
//6=SW 2
//7=SW 3
//8=SW 4
//9=BTN 1
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, pipe);
  radio.setAutoAck(true);//exchange checksums
  radio.setRetries(0,10);//retries to send the packet
  radio.startListening();
  Serial.println("Started");
  
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

  
  if (radio.available()) {
     radio.read(&dataPacket, sizeof(dataPacket));
     y =dataPacket[4];
    Serial.println(y);
    //Serial.println(map(dataPacket[3],0,100,0,180));
  }
 if(radio.available()==false){
  Serial.println("radio not avaliable");
  }
}