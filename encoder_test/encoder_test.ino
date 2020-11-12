#include <PIDController.h>
volatile long int encoder_pos = 0;
volatile long int encoder_pos2 = 0;
PIDController pos_pid; 
int motor_value = 255;
unsigned int integerValue=0;  // Max value is 65535
char incomingByte;
void setup() {

  Serial.begin(9600);
  pinMode(PB1, INPUT);
  pinMode(PB4, INPUT);
  pinMode(PA0, INPUT);
  pinMode(PA1, INPUT);
  pinMode(PB6, OUTPUT);
  pinMode(PB7, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PB1), encoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(PA0), encoder, RISING);

  pos_pid.begin();    
  pos_pid.tune(15, 0, 2000);    
  pos_pid.limit(-255, 255);
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

   motor_value = pos_pid.compute(encoder_pos);
if(motor_value > 0){
  MotorCounterClockwise(motor_value);
}else{
  MotorClockwise(abs(motor_value));
}

  Serial.print(encoder_pos);
  Serial.print("  ");
  Serial.println(encoder_pos2);
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
  if(power > 100){
  analogWrite(9, power);
  digitalWrite(10, LOW);
  }else{
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
}

void MotorCounterClockwise(int power){
  if(power > 100){
  analogWrite(10, power);
  digitalWrite(9, LOW);
  }else{
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
}
