
void m1(int degree){
  x=encoder_pos+degree;
  while(encoder_pos<(x-1) || encoder_pos>(x+1) || stationary==0){
    elapsed=millis();

    if(encoder_pos<(x-1) || encoder_pos>(x+1))elapsedd=millis();
    if((elapsed-elapsedd)>200)stationary=1;
    run();

    
  //Serial.println("running");
  delayMicroseconds(600);
  }
}


void m2(int degree){
  y=encoder_pos2+degree;
  while(encoder_pos2<(y-1) || encoder_pos2>(y+1) || stationary2==0){
    elapsed2=millis();

    if(encoder_pos2<(y-1) || encoder_pos>(y+1))elapsedd2=millis();
    if((elapsed2-elapsedd2)>200)stationary2=1;
    run();

    
  //Serial.println("running");
  delayMicroseconds(600);}
}

void m12(int degree){
  x=encoder_pos+degree;
  y=encoder_pos2+degree;
  
  while(encoder_pos<(x-2) || encoder_pos>(x+2)
        ||encoder_pos2<(y-2) || encoder_pos2>(y+2) || stationary==0){
    elapsed=millis();

    if(encoder_pos<(x-2) || encoder_pos>(x+2)
      ||encoder_pos2<(y-2) || encoder_pos2>(y+2))elapsedd=millis();
    if((elapsed-elapsedd)>200)stationary=1;
    run();

    
  //Serial.println("running");
  delayMicroseconds(delaymic);
  }
}

void m12slow(int degree){
  x=encoder_pos+degree;
  y=encoder_pos2+degree;
  
  while(encoder_pos<(x-2) || encoder_pos>(x+2)
        ||encoder_pos2<(y-2) || encoder_pos2>(y+2) || stationary==0){
    elapsed=millis();

    if(encoder_pos<(x-2) || encoder_pos>(x+2)
      ||encoder_pos2<(y-2) || encoder_pos2>(y+2))elapsedd=millis();
    if((elapsed-elapsedd)>200)stationary=1;
    run();

    
  //Serial.println("running");
  delayMicroseconds(500);
  }
}
void m12left(int degree){
  x=encoder_pos+degree;
  y=encoder_pos2-degree;
  
  while(encoder_pos<(x-2) || encoder_pos>(x+2)
        ||encoder_pos2<(y-2) || encoder_pos2>(y+2) || stationary==0){
    elapsed=millis();

    if(encoder_pos<(x-2) || encoder_pos>(x+2)
      ||encoder_pos2<(y-2) || encoder_pos2>(y+2))elapsedd=millis();
    if((elapsed-elapsedd)>200)stationary=1;
    run();



    
  //Serial.println("running");
  delayMicroseconds(430);
  }
}

void m12right(int degree){
  x=encoder_pos-degree;
  y=encoder_pos2+degree;
  
  while(encoder_pos<(x-2) || encoder_pos>(x+2)
        ||encoder_pos2<(y-2) || encoder_pos2>(y+2) || stationary==0){
    elapsed=millis();

    if(encoder_pos<(x-2) || encoder_pos>(x+2)
      ||encoder_pos2<(y-2) || encoder_pos2>(y+2))elapsedd=millis();
    if((elapsed-elapsedd)>200)stationary=1;
    run();


    
  //Serial.println("running");
  delayMicroseconds(430);
  }
}

void run(){
    pos_pid.setpoint(x);
    motor_value = pos_pid.compute(encoder_pos);
    if(motor_value > 0)mCW(motor_value);
    else{
    absmotor=abs(motor_value);
    mCCW(absmotor);}

    pos_pid2.setpoint(y);
    motor_value2 = pos_pid2.compute(encoder_pos2);
    if(motor_value2 > 0)mCW2(motor_value2);
    else{
    absmotor2=abs(motor_value2);
    mCCW2(absmotor2);}

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

/*
void encoder_(){

  if(digitalRead(PA0) == HIGH){
    encoder_pos++;
  }else{
    encoder_pos--;
  }
}
void encoder2_(){

  if(digitalRead(PB1) == HIGH){
    encoder_pos2--;
  }else{
    encoder_pos2++;
  }
  Serial.println("trig");
}*/
void mCW(int power){
  /*
  Serial.print("CW: ");
  Serial.print(power);
  Serial.println("  CCW:");
  */
  if(power > 10){
  analogWrite(PB8, power);
  analogWrite(PB9, 0);
  }else{
    analogWrite(PB8, 0);
    analogWrite(PB9, 0);
  }
}

void mCCW(int power){
  /*
  Serial.print("CW:    ");
  Serial.print("CCW: ");
  Serial.println(power);
*/
  if(power > 10){
  analogWrite(PB9, power);
  analogWrite(PB8, 0);
  }else{
    analogWrite(PB8, 0);
    analogWrite(PB9, 0);
  }
}


void mCW2(int power){

    Serial.print("CW: ");
  Serial.print(power);
  Serial.println("  CCW:");
  
  if(power > 10){
  analogWrite(PB6, power);
  analogWrite(PB7, 0);
  }else{
    analogWrite(PB6, 0);
    analogWrite(PB7, 0);
  }
}

void mCCW2(int power){
  Serial.print("CW:    ");
  Serial.print("CCW: ");
  Serial.println(power);
  
  if(power > 10){
  analogWrite(PB7, power);
  analogWrite(PB6, 0);
  }else{
    analogWrite(PB6, 0);
    analogWrite(PB7, 0);
  }
}
void wait(int del){
  timeee=millis();
  timee=millis();
  while((timee-timeee)<del){
    run();
    timee=millis();
  }
}
