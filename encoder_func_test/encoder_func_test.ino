#include <PIDController.h>
volatile long int encoder_pos = 0;
volatile long int encoder_pos2 = 0;
PIDController pos_pid;
PIDController pos_pid2; 
int motor_value = 30000,motor_value2 = 30000;
 int integerValue=0;  // Max value is 65535
 int absmotor;
 int x,stationary;
 unsigned long elapsed,elapsedd;

 int absmotor2;
 int y,stationary2;
 unsigned long elapsed2,elapsedd2;
char incomingByte;
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
  pos_pid.tune(500, 0, 8000);    
  pos_pid.limit(-35535, 35535);
  pos_pid.setpoint(integerValue);


  pos_pid2.begin();    
  pos_pid2.tune(500, 0, 8000);    
  pos_pid2.limit(-35535, 35535);
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
m12(integerValue);
}

  Serial.print(encoder_pos);
  Serial.print("  ");
  Serial.print(encoder_pos2);
  Serial.print("  ");
  Serial.print(integerValue);
  Serial.println("  ");



run();
delayMicroseconds(500);
// delay(1); 
}
