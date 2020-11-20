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
  pinMode(PB12, INPUT_PULLUP);
  pinMode(PB13, INPUT_PULLUP);
  pinMode(PB14, INPUT_PULLUP);
  //pinMode(PB12, INPUT_PULLUP);
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

if(digitalRead(PB12)==0&&
  (digitalRead(PB13)==0||digitalRead(PB14)==0)){
  wait(1500);
      
    m12(380);
    wait(300);
    m2(200);
    wait(300);
    m1(200);
    wait(300);
    
    //wait(200);
    m12(430);
    if(!(digitalRead(PB13)==0&&digitalRead(PB14)==1)){
    wait(300);
    pop1st();//58 86 139 99s
    }
    wait(300);
    
    
    //wait(200);
    
    resethand();
    wait(300);
    m12left(210);
    wait(300);
    m12(330);
    wait(300);
    m12right(210);
    wait(400);
    if(!(digitalRead(PB13)==1&&digitalRead(PB14)==0)){
    pop2nd();
    wait(300);
    }
    m12(830);
    //pop2nd();
    wait(500);
    
    resethand();
    
    m12right(210);
    wait(300);
    m12(520);
    wait(300);
    m12left(212);
    wait(300);
    if(!(digitalRead(PB13)==0&&digitalRead(PB14)==0)){
    pop3rd();
    wait(300);
    m12(830);
    wait(300);
    pop2nd();
    wait(300);
    servo1.write(145);
    }
    else m12(830);
    wait(500);
    
    //wait(200);
    m12left(210);
    wait(300);
    m12(540);
    wait(300);
    m12right(210);
    wait(300);
    resethand();
    wait(300);
    m12(600);
    wait(200);
    m2(330);
    wait(230);
    m1(320);
    wait(230);
    m12(600);
}



  
else if(digitalRead(PB12)==0&&
  digitalRead(PB13)==1&&digitalRead(PB14)==1){
    wait(1500);
m2(430);
wait(300);
m1(430);
wait(300);
m12(710);
wait(300);
handown();
wait(1000);
grabbing();
wait(300);
m1(101);
wait(300);
m2(100);
wait(300);
m12(660);
wait(300);
letgo();
wait(500);
resethand();

wait(300);
m12slow(-90);
wait(1000);
m12left(210);
wait(500);
m12(300);
wait(300);
handown();
wait(500);
grabbing();
wait(500);
m12(220);
wait(300);
m12right(210);
wait(500);
servo1.write(125);
wait(500);
m12(550);
wait(400);
letgo();
wait(1000);
resethand();
wait(300);
m12slow(-150);
wait(500);
m2(400);
wait(300);
//m12(50);
//wait(300);
m1(400);
wait(300);




  }
//m12left(40);







run();
//delay(10000000);

  Serial.print(pos1);
Serial.print("  ");
Serial.print(pos2);
Serial.print("  ");
Serial.print(pos3);
Serial.print("  ");
Serial.println(pos4);


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
