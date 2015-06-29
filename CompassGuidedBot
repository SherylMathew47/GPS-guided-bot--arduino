#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"

int mo1=2,mo2=3,mo3=4,mo4=5;
float heading;
void stopp();
void rightturn();
void gostraight();
void leftturn();
void turn();

HMC5883L mag;

int16_t mx, my, mz;
int head=60;                                          //bot turns 60 degrees east of north

void setup() {
  Wire.begin();
   mag.initialize();
 

}

void loop() {
  gostraight();
  
   mag.getHeading(&mx, &my, &mz);
   heading = atan2(my, mx);
    if(heading < 0)
      heading += 2 * M_PI;
    heading=heading*180/M_PI;
      
  while((heading>head+5) || (heading<head-5))
  { stopp();
   delay(10);
   turn();
   delay(5);
   mag.getHeading(&mx, &my, &mz);
   heading = atan2(my, mx);
   if(heading < 0)
   heading += 2 * M_PI;
   heading=heading*180/M_PI;
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
void leftturn()
{ digitalWrite(mo1,LOW);
  digitalWrite(mo2,LOW);
  digitalWrite(mo3,HIGH);
  digitalWrite(mo4,LOW);
  delay(10);
}
void stopp()
{
  digitalWrite(mo1,LOW);
  digitalWrite(mo2,LOW);
  digitalWrite(mo3,LOW);
  digitalWrite(mo4,LOW);
}
  
void rightturn()
{ digitalWrite(mo1,LOW);
  digitalWrite(mo2,HIGH);
  digitalWrite(mo3,LOW);
  digitalWrite(mo4,LOW);
}
void gostraight()
{ digitalWrite(mo1,LOW);
  digitalWrite(mo2,HIGH);
  digitalWrite(mo3,HIGH);
  digitalWrite(mo4,LOW);
}
