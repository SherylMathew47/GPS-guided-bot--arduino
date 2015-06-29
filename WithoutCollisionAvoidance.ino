// This is the same code without collision avoidance
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"


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

float x2lon=radians(72.9154815673),x2lat=radians(19.1287288665);

HMC5883L mag;

int16_t mx, my, mz;
float head,distance=0.0;

void setup() {
  Wire.begin();
   mag.initialize();
 ss.begin(9600);

}

void loop() {
  if(f1!=0)
   gostraight();
  
 do{
   gpshead();} while(distance==0.0);
   
  if(distance<10)
  while(1)
   stopp();
  
  if(f1==0)
   {mag.getHeading(&mx, &my, &mz);
   heading = atan2(my, mx);
    if(heading < 0)
      heading += 2 * M_PI;
    heading=heading*180/M_PI;
      
  // put your main code here, to run repeatedly:
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

head = atan2(sin(x2lon-flon1)*cos(x2lat),cos(flat1)*sin(x2lat)-sin(flat1)*cos(x2lat)*cos(x2lon-flon1));//(2*3.1415926535);

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
