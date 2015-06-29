/* this code provides the heading and distance to a programmed gps location from current location
  The information about current location is obtained from a gps module that gives serial NMEA data*/
#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(6, 5);

void gpshead();

float head,distance;
float x2lon=radians(72.9154815673),x2lat=radians(19.1287288665);


void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  

}

void loop() {
  gpshead();
  Serial.print(distance);
   Serial.print("        ");
  Serial.println(head);
  
  
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

head = atan2(sin(x2lon-flon1)*cos(x2lat),cos(flat1)*sin(x2lat)-sin(flat1)*cos(x2lat)*cos(x2lon-flon1));//,(2*3.1415926535);

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
  head=0;
  distance=0;
 }
}
