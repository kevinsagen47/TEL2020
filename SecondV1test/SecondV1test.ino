#include <PIDController.h>
#include<Servo.h>
volatile long int encoder_pos = 0;
volatile long int encoder_pos2 = 0;
PIDController pos_pid;
PIDController pos_pid2; 


Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
int pos1=95,pos2=63,pos3=4,pos4=99,pos5=90;
int popping=0;
int motor_value = 30000,motor_value2 = 30000;
 int integerValue=0;  // Max value is 65535
 int absmotor;
 int x,stationary;
 unsigned long elapsed,elapsedd,timee,timeee;
unsigned long addtime,delayt=8
,time1,time2,time3,time4,fdelayt=8,sdelayt=20;
 int absmotor2;
 int y,stationary2;
 unsigned long elapsed2,elapsedd2;
char incomingByte;
int delaymic=750;
void setup() {

    servo1.attach(PA8);
  servo2.attach(PA9);
  servo3.attach(PA10);
  servo4.attach(PA2);
  servo5.attach(PA3);
  servo6.attach(PB4);
  
  Serial.begin(115200);
  pinMode(PB1, INPUT);
  pinMode(PB4, INPUT);
  pinMode(PA0, INPUT);
  pinMode(PA1, INPUT);
  pinMode(PB6, OUTPUT);
  pinMode(PB7, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PB1), encoder2, RISING);
//  attachInterrupt(digitalPinToInterrupt(PB4), encoder2_, RISING);
  attachInterrupt(digitalPinToInterrupt(PA0), encoder, RISING);
 // attachInterrupt(digitalPinToInterrupt(PA1), encoder_, RISING);

  pos_pid.begin();    
  pos_pid.tune(3500, 0, 3500);    
  pos_pid.limit(-46040, 46040);
  pos_pid.setpoint(integerValue);


  pos_pid2.begin();    
  pos_pid2.tune(3400, 0, 4000);    
  pos_pid2.limit(-45540, 45540);
  pos_pid2.setpoint(integerValue);
servo1.write(pos1);
servo2.write(pos2);
servo3.write(pos3);
servo4.write(pos4);
servo5.write(180-pos4);
}

void loop() {

if (Serial.available() > 0) {  
    integerValue = 0;        
    while(1) {           
      incomingByte = Serial.read();
      if (incomingByte == '\n') break;   
      if (incomingByte == -1) continue;  
      integerValue *= 10;  
      integerValue = ((incomingByte - 48) + integerValue);

    }
handown();
wait(1000);
grabbing();
wait(1000);
letgo();
wait(1000);
  pos4=99;
    servo4.write(pos4);
    servo5.write(180-pos4);
resethand();


//m12left(40);







run();
//delay(10000000);
}
/*
  Serial.print(pos1);
Serial.print("  ");
Serial.print(pos2);
Serial.print("  ");
Serial.print(pos3);
Serial.print("  ");
Serial.println(pos4);
*/

/*  Serial.print(encoder_pos);
  Serial.print("  ");
  Serial.print(encoder_pos2);
  Serial.print("  ");
  Serial.print(integerValue);
  Serial.println("  ");

*/

run();
delayMicroseconds(delaymic);
// delay(1); 
}
