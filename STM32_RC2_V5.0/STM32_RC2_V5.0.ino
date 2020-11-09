#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
int sdelayt=20,delayt=8,mspeed=30000,sswitch=0,ledb=30000,
    switchdff,switchdff2,sswitch2=0,switchdff3,sswitch3=0 ;//65535max
int pos1=90,pos2=90,pos3=0,pos4=90,pos5=90;
int loading=0;
unsigned long time1,time2,time3,time4,time5;
RF24 radio(PA4, PB0);   // nRF24L01 (CE, CSN)PB13,PB12 PB0, PA4
const byte address[6] = "11100";
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;
unsigned long addtime;
unsigned long switchtime;
// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  short Lx;
  short Ly;
  short Rx;
  short Ry;
  byte L1;
  byte L2;
  byte R1;
  byte R2;
  byte bup;
  byte bdown;
  byte bright;
  byte bleft;
  byte b1;
  byte b2;
  byte b3;
  byte b4;
  byte bstart;
  byte bselect;
  byte banalog;
};
Data_Package data; //Create a variable with the above structure
void setup() {
  servo1.attach(PA8);
  servo2.attach(PA9);
  servo3.attach(PA10);
  servo4.attach(PA2);
  servo5.attach(PA3);
  servo6.attach(PB4);
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening(); //  Set the module as receiver
  resetData();

  pinMode(PB11, OUTPUT);
  pinMode(PB10, OUTPUT);
  pinMode(PB6, OUTPUT);
  pinMode(PB7, OUTPUT);
  pinMode(PB8, OUTPUT);
  pinMode(PB9, OUTPUT);
  pinMode(PC13, OUTPUT);
  pinMode(PC14, OUTPUT);//green
  pinMode(PC15, OUTPUT);//blue
}
void loop() {
  // Check whether there is data to be received
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
    lastReceiveTime = millis(); // At this moment we have received the data
  }
  // Check whether we keep receving data, or we have a connection between the two modules
  currentTime = millis();

  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone has a throttle up and we lose connection, it can keep flying unless we reset the values
  Serial.println("COnnection Lost");
  digitalWrite(PC13,HIGH);
  
  }
  else digitalWrite(PC13,LOW);


  /*
  // Print the data in the Serial Monitor
  Serial.print("Rx: ");
  Serial.print(data.Rx);
  Serial.print("; Ly: ");
  Serial.print(data.Ry);
  Serial.print("Lx: ");
  Serial.print(data.Lx);
  Serial.print("; Ly: ");
  Serial.print(data.Ly);
  Serial.print("; button3: ");
  Serial.print(data.b3);
    Serial.print("; button5: ");
  Serial.print(data.b5);
 Serial.print("; button8: ");
  Serial.print(data.b8);
 Serial.print("; buttonA1: ");
  Serial.print(data.bA1);
  //Serial.print("; b2: ");
  //Serial.println(data.b2); 
  Serial.println(sswitch2); 
*/
if(data.L2==1)switchdff=1;
if(switchdff==1&&data.L2==0){
  if(sswitch==1)sswitch=0;
  else sswitch=1;
  switchdff=0;
}


//camera
if(data.bselect==1)switchdff2=1;
if(switchdff2==1&&data.bselect==0){
  if(sswitch2==1)sswitch2=0;
  else sswitch2=1;
  switchdff2=0;
}
if(sswitch2==0)digitalWrite(PB10,LOW);
else digitalWrite(PB10,HIGH);

//door
if(data.bstart==1)switchdff3=1;
if(switchdff3==1&&data.bstart==0){
  if(sswitch3==1)sswitch3=0;
  else sswitch3=1;
  switchdff3=0;
}
if(sswitch3==0)digitalWrite(PB11,LOW);
else digitalWrite(PB11,HIGH);



//auto load
if(data.bR1==1){
  if(loading==0)loading=2;
}

//pos 75 62 2 74
addtime=millis();
/*if(loading==0){
if(data.Lx>=1520){
  if((addtime-time1)>sdelayt){
  if(pos1<=179)pos1=pos1+1;
  time1=millis();}
  //servo1.write(pos1);
}
*/
if(loading>=1){
if(loading==2){
  if(pos1>76){
    if((addtime-time1)>sdelayt){
    pos1=pos1-1;
    time1=millis();}
  }
   if(pos1<74){
    if((addtime-time1)>sdelayt){
    pos1=pos1+1;
    time1=millis();}
  }

    if(pos2>63){
    if((addtime-time2)>sdelayt){
    pos2=pos2-1;
    time2=millis();}
  }
   if(pos2<61){
    if((addtime-time2)>sdelayt){
    pos2=pos2+1;
    time2=millis();}
  }

    if(pos3>3){
    if((addtime-time3)>sdelayt){
    pos3=pos3-1;
    time3=millis();}
  }

  if(pos1<=76 && pos1>=74 &&
     pos2<=63 && pos2>=61 &&
     pos3<=3){
      pos4=74;
     loading=3;}
}
if(loading==3&&(addtime-time3)>1000)loading=1;
 if(loading==1){
   if(pos2>33){
    if((addtime-time2)>sdelayt){
    pos2=pos2-1;
    time2=millis();}
  }
    if(pos3<180){
    if((addtime-time3)>delayt){
    pos3=pos3+1;
    time3=millis();}
  }

  if(pos2>=33&&pos3>=179)loading=0;
  
 }



}

if(sswitch==1){
if(data.b4==1){
  analogWrite(PB7,65535);
  analogWrite(PB9,65535);
  analogWrite(PB6,0);
  analogWrite(PB8,0);
}
else if(data.b2==1){
  analogWrite(PB7,0);
  analogWrite(PB9,0);
  analogWrite(PB6,65535);
  analogWrite(PB8,65535);
}
else if(data.b5==1){
  analogWrite(PB7,65535);
  analogWrite(PB9,0);
  analogWrite(PB6,0);
  analogWrite(PB8,65535);
}
else if(data.b3==1){
  analogWrite(PB7,0);
  analogWrite(PB9,65535);
  analogWrite(PB6,65535);
  analogWrite(PB8,0);
}

else{
  analogWrite(PB7,0);
  analogWrite(PB9,0);
  analogWrite(PB6,0);
  analogWrite(PB8,0);
}

addtime=millis();
if(loading==0){
if(data.Lx>=1520){
  if((addtime-time1)>delayt){
  if(pos1<=179)pos1=pos1+1;
  time1=millis();}
  //servo1.write(pos1);
}
if(data.Lx<=1480){
  if((addtime-time1)>delayt){
  if(pos1>=1)pos1=pos1-1;
  time1=millis();}
  //servo1.write(pos1);
}
if(data.Ly>=1520){
  if((addtime-time2)>delayt){
  if(pos2<=179)pos2=pos2+1;
  time2=millis();}
}
if(data.Ly<=1480){
  if((addtime-time2)>delayt){
  if(pos2>=20)pos2=pos2-1;
  time2=millis();}
}
if(data.Ry<=1480){
  if((addtime-time3)>delayt){
  if(pos3<=179)pos3=pos3+1;
  time3=millis();}
}
if(data.Ry>=1520){
  if((addtime-time3)>delayt){
  if(pos3>=1)pos3=pos3-1;
  time3=millis();}
}
if(data.Rx>=1520){
  if((addtime-time4)>delayt){
  if(pos4<=105)pos4=pos4+1;
  time4=millis();}
}
if(data.Rx<=1480){
  if((addtime-time4)>delayt){
  if(pos4>=1)pos4=pos4-1;
  time4=millis();}
}}
digitalWrite(PC15,HIGH);
digitalWrite(PC14,LOW);
}

else{
if(data.b4==1){
  analogWrite(PB7,mspeed);
  analogWrite(PB9,mspeed);
  analogWrite(PB6,0);
  analogWrite(PB8,0);
}
else if(data.b2==1){
  analogWrite(PB7,0);
  analogWrite(PB9,0);
  analogWrite(PB6,mspeed);
  analogWrite(PB8,mspeed);
}
else if(data.b5==1){
  analogWrite(PB7,mspeed);
  analogWrite(PB9,0);
  analogWrite(PB6,0);
  analogWrite(PB8,mspeed);
}
else if(data.b3==1){
  analogWrite(PB7,0);
  analogWrite(PB9,mspeed);
  analogWrite(PB6,mspeed);
  analogWrite(PB8,0);
}

else{
  analogWrite(PB7,0);
  analogWrite(PB9,0);
  analogWrite(PB6,0);
  analogWrite(PB8,0);
}

addtime=millis();
if(loading==0){
if(data.Lx>=1520){
  if((addtime-time1)>sdelayt){
  if(pos1<=179)pos1=pos1+1;
  time1=millis();}
  //servo1.write(pos1);
}
if(data.Lx<=1480){
  if((addtime-time1)>sdelayt){
  if(pos1>=1)pos1=pos1-1;
  time1=millis();}
  //servo1.write(pos1);
}
if(data.Ly>=1520){
  if((addtime-time2)>sdelayt){
  if(pos2<=179)pos2=pos2+1;
  time2=millis();}
}
if(data.Ly<=1480){
  if((addtime-time2)>sdelayt){
  if(pos2>=1)pos2=pos2-1;
  time2=millis();}
}
if(data.Ry<=1480){
  if((addtime-time3)>sdelayt){
  if(pos3<=179)pos3=pos3+1;
  time3=millis();}
}
if(data.Ry>=1520){
  if((addtime-time3)>sdelayt){
  if(pos3>=1)pos3=pos3-1;
  time3=millis();}
}
if(data.Rx>=1520){
  if((addtime-time4)>sdelayt){
  if(pos4<=105)pos4=pos4+1;
  time4=millis();}
}
if(data.Rx<=1480){
  if((addtime-time4)>sdelayt){
  if(pos4>=1)pos4=pos4-1;
  time4=millis();}
}}
digitalWrite(PC15,LOW);
digitalWrite(PC14,HIGH);
}


Serial.print(pos1);
Serial.print("  ");
Serial.print(pos2);
Serial.print("  ");
Serial.print(pos3);
Serial.print("  ");
Serial.println(pos4);

servo1.write(pos1);
servo2.write(pos2);
servo3.write(pos3);
servo4.write(pos4);
servo5.write(180-pos4);
//Serial.println(pos4);

}


//Channel 1 => Roll     => data.Rx
//Channel 2 => pitch    => data.Ry
//Channel 3 => throttle => data.Ly
//Channel 4 => yaw      => data.Lx


void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.Lx = 1500; // Values from 0 to 255. When Joystick is in resting position, the value is in the middle, or 127. We actually map the pot value from 0 to 1023 to 0 to 255 because that's one BYTE value
  data.Ly = 1500;
  data.Rx = 1500;
  data.Ly = 1500;
  data.b0 = 0;
  data.b1 = 0;
  data.b2 = 0;
  data.b3 = 0;
  data.b4 = 0;
  data.b5 = 0;
  data.b6 = 0;
  data.b7 = 0;
  data.b8 = 0;
  data.bA1 = 0;
}
