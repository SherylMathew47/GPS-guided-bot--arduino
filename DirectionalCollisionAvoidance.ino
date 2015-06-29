/* This is a code for making the bot move in a particular direction (specified using variable head)
   and avoid collision should an obstacle come in its path.   */
#include <Servo.h> 
#include <NewPing.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"

float heading;
HMC5883L mag;
int16_t mx, my, mz;
float head;

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

//long sensorcm(int trig,int echo);
void gostraight();
void stopp();
void rightturn();
void leftturn();
void turn();

Servo myservo;

void setup() {
 Wire.begin();
   mag.initialize();
  
pinMode (vcc,OUTPUT);
pinMode (gnd,OUTPUT);
pinMode (A0,OUTPUT);
pinMode (A1,OUTPUT);
pinMode (12,OUTPUT);
pinMode (2,OUTPUT);
//initialize serial communication:

myservo.attach(7);
}

void loop()
{head=70;
mag.getHeading(&mx, &my, &mz);
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
gostraight();
cm1=sonar.ping_cm();
delay(50);
cm1+=sonar.ping_cm();
cm1=cm1/2;
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

}
delay(100);
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
