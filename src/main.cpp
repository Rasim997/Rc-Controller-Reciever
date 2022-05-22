#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define LYPin 3
#define LXPin 5
#define RYPin 6
#define RXPin 9

#define Btn1 15
#define Btn2 16
#define Btn3 17
#define Btn4 18
#define Btn5 19


Servo LY,LX,RY,RX;
RF24 radio(7, 8);// CE, CSN
const byte pipe[6] = "00001"; // Radio pipe address for the 2 nodes to communicate.

// D5 D6 D3 D9 PWM Outputs
int y = 0;
uint8_t dataPacket[9];
// 1=Left Y
// 2=Left X
// 3=Right Y
// 4=Right X
// 5=SW 1
// 6=SW 2
// 7=SW 3
// 8=SW 4
// 9=BTN 1
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, pipe);
  radio.setAutoAck(true);  // exchange checksums
  radio.setRetries(0, 10); // retries to send the packet
  radio.startListening();
  Serial.println("Started");
  LY.attach(LYPin);
  LX.attach(LXPin);
  RY.attach(RYPin);
  RX.attach(RXPin);
  //sending stop signal to everything
  LY.writeMicroseconds(1500);
  LX.writeMicroseconds(1500);
  RY.writeMicroseconds(1500);
  RX.writeMicroseconds(1500);
  delay(7000);

  pinMode(Btn1,OUTPUT);
  pinMode(Btn2,OUTPUT);
  pinMode(Btn3,OUTPUT);
  pinMode(Btn4,OUTPUT);
  pinMode(Btn5,OUTPUT);
  digitalWrite(Btn1,LOW);
  digitalWrite(Btn2,LOW);
  digitalWrite(Btn3,LOW);
  digitalWrite(Btn4,LOW);
  digitalWrite(Btn5,LOW);

}

void PWM(){
  int ly = map(dataPacket[1],0,100,1100,1900);
  int lx = map(dataPacket[2],0,100,1100,1900);
  int ry = map(dataPacket[3],0,100,1100,1900);
  int rx = map(dataPacket[4],0,100,1100,1900);
  LY.writeMicroseconds(ly);
  LX.writeMicroseconds(lx);
  RY.writeMicroseconds(ry);
  RX.writeMicroseconds(rx);
}
void Btn(int Button ,int Value){
  if(Value==1){
    digitalWrite(Button,HIGH);
  }
  else{
    digitalWrite(Button,LOW);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:

  if (radio.available())
  {
    radio.read(&dataPacket, sizeof(dataPacket));
    PWM();
    Btn(Btn1,dataPacket[5]);
    Btn(Btn2,dataPacket[6]);
    Btn(Btn3,dataPacket[7]);
    Btn(Btn4,dataPacket[8]);
    Btn(Btn5,dataPacket[9]);

  }
  if (radio.available() == false)
  {
    Serial.println("radio not avaliable");
  }
}

