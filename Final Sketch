#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"
#include <Servo.h> 
#include <NewPing.h>
int vcc = 3; 
int trig1 = 8; 
int echo1 = 9; 
int trig2 = 11; 
int echo2 = 10; 
int gnd = 4; 
long cm1,cm2;
int i=0;
NewPing sonar(trig1,echo1,250);
NewPing sonar2(trig2,echo2,250);
int f1=0;
float heading;
TinyGPS gps;
SoftwareSerial ss(6, 5);
void gpshead();
void stopp();
void rightturn();
void gostraight();
void leftturn();
void turn();
Servo myservo;
float x2lon=radians(72.9154815673),x2lat=radians(19.1287288665);
HMC5883L mag;
int16_t mx, my, mz;
float head,distance=0.0;
void setup() {
 Wire.begin();
 mag.initialize();
 ss.begin(9600);
 pinMode (vcc,OUTPUT);
 pinMode (gnd,OUTPUT);
 pinMode (A0,OUTPUT);
 pinMode (A1,OUTPUT);
 pinMode (12,OUTPUT);
 pinMode (2,OUTPUT);
 myservo.attach(7);
}
void loop() {
  if(f1!=0)
   gostraight();
 cm1=sonar.ping_cm();
 delay(50);
 cm1=sonar.ping_cm();
if(cm1<20&&cm1>0)
{
 mag.getHeading(&mx, &my, &mz);
   heading = atan2(my, mx);
    if(heading < 0)
      heading += 2 * M_PI;
    heading=heading*180/M_PI;
  if((i%2)==0)
 {head=heading+100;
 if (head>360)
 head=head-360;
 /*leftturn();
 myservo.write(180); 
 delay(2000);*/
  myservo.write(180); 
 i++;}
else
 {head=heading-100;
 if (head<0)
 head=head+360;
/* rightturn();
 myservo.write(0); 
 delay(1000);*/
  myservo.write(0); 
 i++;
}
  while((heading>head+5) || (heading<head-5))         // this loop turns the bot till its facing (head)degrees east of north
  {
   turn();
   delay(5);
   mag.getHeading(&mx, &my, &mz);
   heading = atan2(my, mx);
   if(heading < 0)
   heading += 2 * M_PI;
   heading=heading*180/M_PI;
   }
stopp();
delay(100);
cm2=sonar2.ping_cm();
delay(50);
cm2+=sonar2.ping_cm();
cm2=cm2/2;
while((cm2<50)&&(cm2>0))
{gostraight();
delay(50);
cm2=sonar2.ping_cm();
delay(50);
cm2+=sonar2.ping_cm();
cm2=cm2/2;}
delay(500);
stopp();
}
 do{
   gpshead();} while(distance==0.0);
  if(distance<20)
  while(1)
   stopp();
  if(f1==0)
   {mag.getHeading(&mx, &my, &mz);
   heading = atan2(my, mx);
    if(heading < 0)
      heading += 2 * M_PI;
    heading=heading*180/M_PI;


  while((heading>head+5) || (heading<head-5))
  {
   turn();
   delay(5);
   mag.getHeading(&mx, &my, &mz);
   heading = atan2(my, mx);
   if(heading < 0)
   heading += 2 * M_PI;
   heading=heading*180/M_PI;
   }
   f1=4;
   }
 f1--;
}
void turn()
{float tur=heading-head;
  if(tur<0.0)
  {if(tur>-180.0)
  leftturn();
  else
  rightturn();}
  else
  {if(tur<180.0)
  rightturn();
  else leftturn();}
}
void gostraight()
{ digitalWrite(A0,LOW);
  digitalWrite(A1,HIGH);
  digitalWrite(12,LOW);
  digitalWrite(2,HIGH);
}
void stopp()
{
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(12,LOW);
  digitalWrite(2,LOW);
}
void rightturn()
{ digitalWrite(A0,LOW);
  digitalWrite(A1,HIGH);
  digitalWrite(12,LOW);
  digitalWrite(2,LOW);
}
void leftturn()
{ digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(12,LOW);
  digitalWrite(2,HIGH);
}
void gpshead()
{ 
bool newData = false;
for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }
if (newData)
{
float flat1, flon1;
unsigned long age;
gps.f_get_position(&flat1, &flon1, &age);
flon1 = radians(flon1);  //also must be done in radians
flat1 = radians(flat1);  //also must be done in radians
head = atan2(sin(x2lon-flon1)*cos(x2lat),cos(flat1)*sin(x2lat)-sin(flat1)*cos(x2lat)*cos(x2lon-flon1));
head = head*180/3.1415926535;  // convert from radians to degrees
float dist_calc=0;
float diflat=0;
float diflon=0;
diflat=x2lat-flat1;  //notice it must be done in radians
diflon=(x2lon)-(flon1);   //subtract and convert longitudes to radians
distance = (sin(diflat/2.0)*sin(diflat/2.0));
dist_calc= cos(flat1);
dist_calc*=cos(x2lat);
dist_calc*=sin(diflon/2.0);                                      
dist_calc*=sin(diflon/2.0);
distance +=dist_calc;
distance=(2*atan2(sqrt(distance),sqrt(1.0-distance)));
distance*=6371000.0; //Converting to meters
if(head<0){
 head+=360;   //if the heading is negative then add 360 to make it positive
}
}
else
{
  head=0.0;
  distance=0.0;
 }
}
