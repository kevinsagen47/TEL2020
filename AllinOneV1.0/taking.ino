void handown(){
  popping=1;
while(popping==1){
  run();
  while(pos3<=142){
    run();
    addtime=millis();
    if((addtime-time3)>delayt){
    pos3=pos3+1;
    time3=millis();
    servo3.write(pos3);
    }
  }
      pos4=51;
    servo4.write(pos4);
    servo5.write(180-pos4);
    while(pos2<=129){
    run();
    addtime=millis();
    if((addtime-time2)>delayt){
    pos2=pos2+1;
    time2=millis();
    servo2.write(pos2);
    }
  }
    Serial.print(pos2);
    Serial.print("  ");
    Serial.print(pos3);
    Serial.println("shit");

    popping=0;
  }
}

void letgo(){
  pos4=51;
    servo4.write(pos4);
    servo5.write(180-pos4);
}

void grabbing(){
  popping=1;
  pos4=105;
  servo4.write(pos4);
  servo5.write(180-pos4);
  wait(500);
while(popping==1){
  run();
    while(pos2>=76){
    run();
    addtime=millis();
    if((addtime-time2)>delayt){
    pos2=pos2-1;
    time2=millis();
    servo2.write(pos2);
    }
  }
    Serial.print(pos2);
    Serial.print("  ");
    Serial.print(pos3);
    Serial.println("shit");
   
    popping=0;
  }
}
