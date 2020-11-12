#include <PIDController.h>
volatile long int encoder_pos = 0;
volatile long int encoder_pos2 = 0;
PIDController pos_pid; 
int motor_value = 30000;
 int integerValue=0;  // Max value is 65535
 int absmotor;
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
  attachInterrupt(digitalPinToInterrupt(PA0), encoder, RISING);

  pos_pid.begin();    
  pos_pid.tune(400, 0, 16000);    
  pos_pid.limit(-35535, 35535);
  pos_pid.setpoint(integerValue);
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
      pos_pid.setpoint(integerValue);
    }
}

  Serial.print(encoder_pos);
  Serial.print("  ");
  Serial.print(encoder_pos2);
  Serial.print("  ");
  Serial.print(integerValue);
  Serial.print("  ");


  
   motor_value = pos_pid.compute(encoder_pos);
if(motor_value > 0){
  MotorClockwise(motor_value);

}else{
  absmotor=abs(motor_value);
  MotorCounterClockwise(absmotor);

}


  delay(10);
}


void encoder2(){

  if(digitalRead(PB4) == HIGH){
    encoder_pos2++;
  }else{
    encoder_pos2--;
  }
}

void encoder(){

  if(digitalRead(PA1) == HIGH){
    encoder_pos--;
  }else{
    encoder_pos++;
  }
}

void MotorClockwise(int power){
  Serial.print("CW: ");
  Serial.print(power);
  Serial.println("  CCW:");
  
  if(power > 10){
  analogWrite(PB8, power);
  analogWrite(PB9, 0);
  }else{
    analogWrite(PB8, 0);
    analogWrite(PB9, 0);
  }
}

void MotorCounterClockwise(int power){
  Serial.print("CW:    ");
  Serial.print("CCW: ");
  Serial.println(power);

  if(power > 10){
  analogWrite(PB9, power);
  analogWrite(PB8, 0);
  }else{
    analogWrite(PB8, 0);
    analogWrite(PB9, 0);
  }
}
