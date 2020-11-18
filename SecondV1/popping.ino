void pop3rd(){
   popping=1;
while(popping==1){
  run();
  while(pos3<=160){
    run();
    addtime=millis();
    if((addtime-time3)>delayt){
    pos3=pos3+1;
    time3=millis();
    servo3.write(pos3);
    }
  }
  
  while(pos2<77||pos3>=147){
    run();
    addtime=millis();
    if(pos2<=77){
    
    if((addtime-time2)>fdelayt){
    pos2=pos2+1;
    time2=millis();
    servo2.write(pos2);
    }}
    
    if((addtime-time3)>fdelayt){
    pos3=pos3-1;
    time3=millis();
    servo3.write(pos3);
    }
    Serial.print(pos2);
    Serial.print("  ");
    Serial.print(pos3);
    Serial.println("shit");
    }
    
    popping=0;
  }
}
void pop2nd(){
   popping=1;
while(popping==1){
  run();
  while(pos3<=160){
    run();
    addtime=millis();
    if((addtime-time3)>delayt){
    pos3=pos3+1;
    time3=millis();
    servo3.write(pos3);
    }
  }
  while(pos1<=125){
    run();
    addtime=millis();
    if((addtime-time1)>delayt){
    pos1=pos1+1;
    time1=millis();
    servo1.write(pos1);
    }
  }
  while(pos2<77||pos3>=147){
    run();
    addtime=millis();
    if(pos2<=77){
    
    if((addtime-time2)>fdelayt){
    pos2=pos2+1;
    time2=millis();
    servo2.write(pos2);
    }}
    
    if((addtime-time3)>fdelayt){
    pos3=pos3-1;
    time3=millis();
    servo3.write(pos3);
    }
    Serial.print(pos2);
    Serial.print("  ");
    Serial.print(pos3);
    Serial.println("shit");
    }
    
    popping=0;
  }
}
void pop1st(){
  popping=1;
while(popping==1){
  run();
  while(pos3<=160){
    run();
    addtime=millis();
    if((addtime-time3)>delayt){
    pos3=pos3+1;
    time3=millis();
    servo3.write(pos3);
    }
  }
  while(pos1>=50){
    run();
    addtime=millis();
    if((addtime-time1)>delayt){
    pos1=pos1-1;
    time1=millis();
    servo1.write(pos1);
    }
  }
  while(pos2<=87||pos3>=130){
    run();
    addtime=millis();
    if(pos2<=87){
    
    if((addtime-time2)>fdelayt){
    pos2=pos2+1;
    time2=millis();
    servo2.write(pos2);
    }}
    
    if((addtime-time3)>fdelayt){
    pos3=pos3-1;
    time3=millis();
    servo3.write(pos3);
    }
    Serial.print(pos2);
    Serial.print("  ");
    Serial.print(pos3);
    Serial.println("shit");
    }
    
    popping=0;
  }
}

void resethand(){
  pos4=99;
    servo4.write(pos4);
    servo5.write(180-pos4);
while((pos1<95 && pos1>94) ||
     (pos2<63 && pos2<61) ||
     pos3>3){
      run();
      addtime=millis();
if(pos1>96){
    if((addtime-time1)>delayt){
    pos1=pos1-1;
    time1=millis();}
  }
   if(pos1<94){
    if((addtime-time1)>delayt){
    pos1=pos1+1;
    time1=millis();}
  }

    if(pos2>63){
    if((addtime-time2)>delayt){
    pos2=pos2-1;
    time2=millis();}
  }
   if(pos2<61){
    if((addtime-time2)>delayt){
    pos2=pos2+1;
    time2=millis();}
  }

    if(pos3>3){
    if((addtime-time3)>delayt){
    pos3=pos3-1;
    time3=millis();}
  }
 servo1.write(pos1);
servo2.write(pos2);
servo3.write(pos3);
servo4.write(pos4);
  Serial.print(pos1);
Serial.print("  ");
Serial.print(pos2);
Serial.print("  ");
Serial.print(pos3);
Serial.print("  ");
Serial.println(pos4);
  }}
