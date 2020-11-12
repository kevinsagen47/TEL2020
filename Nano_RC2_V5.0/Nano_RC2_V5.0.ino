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
    switchdff,switchdff2,sswitch2=0 
    ,switchdff3,sswitch3=0
    ,switchdff4,sswitch4=0;//65535max
int pos1=90,pos2=88,pos3=180,pos4=150,pos5=150;
unsigned long time1,time2,time3,time4,time5,loading=0;
RF24 radio(9, 10);   // nRF24L01 (CE, CSN)PB13,PB12 PB0, PA4
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
  digitalWrite(A3,HIGH);
  pinMode(A3,OUTPUT);
  servo1.attach(5);
  servo2.attach(4);
  servo3.attach(3);
  servo4.attach(2);
  servo5.attach(6);
  servo6.attach(8);

  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver
  resetData();

  pinMode(7, OUTPUT);
  pinMode(A0, OUTPUT);

}
void(* resetFunc) (void) = 0; //declare reset function @ address 0


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
  digitalWrite(A0,HIGH);
  
  }
  else digitalWrite(A0,LOW);


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
  Serial.print("; b2: ");
  Serial.println(data.b2); 
*/
if(data.L2==1)switchdff=1;
if(switchdff==1&&data.L2==0){
  if(sswitch==1)sswitch=0;
  else sswitch=1;
  switchdff=0;
}


if(digitalRead(A4)==1&&digitalRead(A5)==1)digitalWrite(A3,LOW);
//camera
else{
if(digitalRead(A4)==1&&digitalRead(A5)==0)digitalWrite(7,HIGH);
else digitalWrite(7,LOW);

if(digitalRead(A5)==1&&digitalRead(A4)==0)servo6.write(16);
else servo6.write(97);
}
 


if(data.L1==1){
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
  if(pos1>118){
    if((addtime-time1)>sdelayt+8){
    pos1=pos1-1;
    time1=millis();}
  }
   if(pos1<118){
    if((addtime-time1)>sdelayt+8){
    pos1=pos1+1;
    time1=millis();}
  }

    if(pos2>61){
    if((addtime-time2)>sdelayt){
    pos2=pos2-1;
    time2=millis();}
  }
   if(pos2<61){
    if((addtime-time2)>sdelayt){
    pos2=pos2+1;
    time2=millis();}
  }

    if(pos3>0){
    if((addtime-time3)>sdelayt){
    pos3=pos3-1;
    time3=millis();}
  }

  if(pos1<=119 && pos1>=117 &&
     pos2<=63 && pos2>=61 &&
     pos3<=2){
      pos4=126;
     loading=3;}
}
if(loading==3&&(addtime-time3)>1000)loading=1;
 if(loading==1){
   if(pos1>100){
    if((addtime-time2)>sdelayt){
    pos1=pos1-1;
    time3=millis();}
  }
   if(pos2<88){
    if((addtime-time2)>sdelayt){
    pos2=pos2+1;
    time2=millis();}
  }
    if(pos3<180){
    if((addtime-time3)>delayt){
    pos3=pos3+1;
    time3=millis();}
  }

  if(pos1<=100&&pos2>=87&&pos3>=179)loading=0;
  
 }}




if(data.R2==1)switchdff4=1;
if(switchdff4==1&&data.R2==0){
  if(sswitch4==1)sswitch4=0;
  else sswitch4=1;
  switchdff4=0;
}




if(sswitch4==1){ 
}
else{
if(sswitch==1){
addtime=millis();
if(loading==0){
if(data.Lx>=1515){
  if((addtime-time1)>delayt){
  if(pos1<=179)pos1=pos1+1;
  time1=millis();}
  //servo1.write(pos1);
}
if(data.Lx<=1475){
  if((addtime-time1)>delayt){
  if(pos1>=1)pos1=pos1-1;
  time1=millis();}
  //servo1.write(pos1);
}
if(data.Ly<=1460){
  if((addtime-time2)>(delayt+10)){
  if(pos2<=179)pos2=pos2+1;
  time2=millis();}
}
if(data.Ly>=1500){
  if((addtime-time2)>(delayt+10)){
  if(pos2>=20)pos2=pos2-1;
  time2=millis();}
}
if(data.bup==1){
  if((addtime-time3)>delayt){
  if(pos3<=179)pos3=pos3+1;
  time3=millis();}
}
if(data.bdown==1){
  if((addtime-time3)>delayt){
  if(pos3>=1)pos3=pos3-1;
  time3=millis();}
}
if(data.bleft==1){
  if((addtime-time4)>delayt){
  if(pos4<=180)pos4=pos4+1;
  time4=millis();}
}
if(data.bright==1){
  if((addtime-time4)>delayt){
  if(pos4>=1)pos4=pos4-1;
  time4=millis();}
}}
}

else{
addtime=millis();
if(loading==0){
if(data.Lx>=1515){
  if((addtime-time1)>sdelayt){
  if(pos1<=179)pos1=pos1+1;
  time1=millis();}
  //servo1.write(pos1);
}
if(data.Lx<=1475){
  if((addtime-time1)>sdelayt){
  if(pos1>=1)pos1=pos1-1;
  time1=millis();}
  //servo1.write(pos1);
}
if(data.Ly<=1460){
  if((addtime-time2)>(sdelayt+10)){
  if(pos2<=179)pos2=pos2+1;
  time2=millis();}
}
if(data.Ly>=1500){
  if((addtime-time2)>(sdelayt+10)){
  if(pos2>=20)pos2=pos2-1;
  time2=millis();}
}
if(data.bup==1){
  if((addtime-time3)>sdelayt){
  if(pos3<=179)pos3=pos3+1;
  time3=millis();}
}
if(data.bdown==1){
  if((addtime-time3)>sdelayt){
  if(pos3>=1)pos3=pos3-1;
  time3=millis();}
}
if(data.bleft==1){
  if((addtime-time4)>sdelayt){
  if(pos4<=180)pos4=pos4+1;
  time4=millis();}
}
if(data.bright==1){
  if((addtime-time4)>sdelayt){
  if(pos4>=1)pos4=pos4-1;
  time4=millis();}
}}
}
}

Serial.print(pos1);
Serial.print("  ");
Serial.print(pos2);
Serial.print("  ");
Serial.print(pos3);
Serial.print("  ");
Serial.println(pos4);
//Serial.print("  ");
//Serial.print(pos5);
//Serial.print("  ");
//Serial.println(pos6);

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
  data.Lx = 1495; // Values from 0 to 255. When Joystick is in resting position, the value is in the middle, or 127. We actually map the pot value from 0 to 1023 to 0 to 255 because that's one BYTE value
  data.Ly = 1482;
  data.Rx = 1500;
  data.Ry = 1500;
  data.L1 =0;
  data.L2 =0;
  data.R1 =0;
  data.R2 =0;
  data.bup =0;
  data.bdown =0;
  data.bright =0;
  data.bleft =0;
  data.b1 =0;
  data.b2 =0;
  data.b3 =0;
  data.b4 =0;
  data.bstart =0;
  data.bselect =0;
  data.banalog =0;
  if(loading==0){
  pos1=90;
  pos2=88;
  pos3=180;
  pos4=150;
  pos5=150;}
}
