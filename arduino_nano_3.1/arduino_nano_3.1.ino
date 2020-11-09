///////////////////////////////////////////////////////////////////////////////////////
//Terms of use
///////////////////////////////////////////////////////////////////////////////////////
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////////
//Safety note
///////////////////////////////////////////////////////////////////////////////////////
//Always remove the propellers and stay away from the motors unless you 
//are 100% certain of what you are doing.
///////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>                          //Include the Wire.h library so we can communicate with the gyro.
#include <EEPROM.h>                        //Include the EEPROM.h library so we can store information onto the EEPROM
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Servo.h>

Servo esc1; 
Servo esc2; 
Servo esc3; 
Servo esc4; 
Servo esc5; 
Servo esc6;
int sdelayt=20,delayt=8,mspeed=30000,sswitch=0,ledb=30000,
    switchdff,switchdff2,sswitch2=0 
    ,switchdff3,sswitch3=0;//65535max
int pos1=90,pos2=90,pos3=0,pos4=90,pos5=90;
unsigned long time1,time2,time3,time4,time5;


RF24 radio(9, 10);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001";
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
  byte b0;
  byte b1;
  byte b2;
  byte b3;
  byte b4;
  byte b5;
  byte b6;
  byte b7;
  byte b8;
  byte bA1;
};
Data_Package data; //Create a variable with the above structure

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(){
  Serial.begin(115200);
  
  pinMode(A0,1);
  //Use the led on the Arduino for startup indication.
  digitalWrite(A0,HIGH);                                                    //Turn on the warning led.
  delay(100);
  digitalWrite(7,1);     
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver
  resetData();
  esc1.attach(4);
  esc2.attach(3);
  esc3.attach(2);
  esc4.attach(1);
  esc5.attach(6);
  esc6.attach(8);
  digitalWrite(A0,LOW);                                                     //Turn off the warning led.
  esc1.write(90);
  esc2.write(90);
  esc3.write(0);
  esc4.write(90);
  esc5.write(90);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main program loop
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop(){
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); 
    lastReceiveTime = millis(); 
  }

  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) { 
  resetData(); 
  Serial.println("COnnection Lost");
  digitalWrite(A0,1);
  }
   else digitalWrite(A0,LOW);
   /*
if(data.b0==1)switchdff=1;
if(switchdff==1&&data.b0==0){
  if(sswitch==1)sswitch=0;
  else sswitch=1;
  switchdff=0;
}

*/

if(data.b8==1)switchdff2=1;
if(switchdff2==1&&data.b8==0){
  if(sswitch2==1)sswitch2=0;
  else sswitch2=1;
  switchdff2=0;
}

if(sswitch2==0)digitalWrite(7,LOW);
else digitalWrite(7,HIGH);
/*
if(data.b7==1)switchdff3=1;
if(switchdff3==1&&data.b7==0){
  if(sswitch3==1)sswitch3=0;
  else sswitch3=1;
  switchdff3=0;
}
if(sswitch3==0)esc6.write(90);
else esc6.write(170);
*/
}








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
