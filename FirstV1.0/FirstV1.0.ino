#include <PIDController.h>
volatile long int encoder_pos = 0;
volatile long int encoder_pos2 = 0;
PIDController pos_pid;
PIDController pos_pid2; 
int motor_value = 30000,motor_value2 = 30000;
 int integerValue=0;  // Max value is 65535
 int absmotor;
 int x,stationary;
 unsigned long elapsed,elapsedd,timee,timeee;

 int absmotor2;
 int y,stationary2;
 unsigned long elapsed2,elapsedd2;
char incomingByte;
int delaymic=750;
void setup() {

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
  pos_pid.limit(-45535, 45535);
  pos_pid.setpoint(integerValue);


  pos_pid2.begin();    
  pos_pid2.tune(3400, 0, 4000);    
  pos_pid2.limit(-45535, 45535);
  pos_pid2.setpoint(integerValue);
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
m2(150);
wait(200);
m1(150);
wait(300);
m12(510);
wait(1500);

m12left(210);
wait(200);
m12(270);
wait(200);
m12right(210);
wait(400);
m12(800);
wait(1500);
m12right(210);
wait(300);
m12(570);
wait(300);
m12left(220);

wait(300);
m12(830);
wait(1500);
m12left(210);
wait(300);
m12(540);
wait(200);
m12right(210);
run();
//delay(10000000);
}

  Serial.print(encoder_pos);
  Serial.print("  ");
  Serial.print(encoder_pos2);
  Serial.print("  ");
  Serial.print(integerValue);
  Serial.println("  ");



run();
delayMicroseconds(delaymic);
// delay(1); 
}
