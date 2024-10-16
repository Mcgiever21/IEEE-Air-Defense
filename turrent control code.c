#include <Servo.h>


Servo ServoX;           // create servo object for x coordinate (horizontal plane)
Servo ServoZ;           // create servo object for z coordinate (vertical plane)

int xcoor;              // place holder for Radar signal x
int xdist;              // place holder for Radar signal x distance to target
int zcoor;              // place holder for Radar signal z
int zdist;              // place holder for Radar signal z distance to target
//int ycoor;            // place holder for Radar signal y
int negx = -180;        // negative x adder for outside the 180 degree range
int Xoffset = null;     //horizontal offset from radar
int Zoffset = null;     //vertical offset from radar
float xturtar;            // place holder for turrent signal x
float xtardist;           // place holder for turrent signal x distance to target
float zturtar;            // place holder for turrent signal z
float ztardist;           // place holder for turrent signal z distance to target
                      /********* x servo motor to be set to (0,90,180)
                      ********** z servo motor to be set to (90,0,-90) for easier calculations
                      *********/
int const xServoControlPin = null; // motor control pin for wiring
int const zServoControlPin = null; // motor control pin for wiring
void TurrentPanTilt(){
  ServoX.Write(xcoor);
  ServoZ.Write(zcoor);
}
void TargetRecieved(){
    if(xcoor>180){
      xcoor =xcoor+negx;
      zcoor = -zcoor;
    }

    float a = xdist*sin(xcoor);       //right triangle wall
    float b = 90-a;                   //target angle to sensor
    float c = c*cos(b);               //right triangle base sensor to square corner
    if()
    float cc = c+Xoffset;             //triangle base leg turrent to square corner
    float d = sqrt(a^2+cc^2);         //triangle new leg turrent to target distance
    float e = sininverse(cc/d);       //turrent angle to target
    xturtar = d;                      //save new x coordinate
    xtardist = e;                     //save new x distance
    a = xdist*sin(zcoor);       //right triangle wall
    b = 90-a;                   //target angle to sensor
    c = c*cos(b);               //right triangle base sensor to square corner
    cc = c+Zoffset;             //triangle base leg turrent to square corner
    d = sqrt(a^2+cc^2);         //triangle new leg turrent to target distance
    e = sininverse(cc/d);       //turrent angle to target
    if(xcoor>180){
        xturtar = xturtar+180;

    }
}
void setup() {
  // put your setup code here, to run once:
ServoX.attach(xServoControlPin);
ServoZ.attach(zServoControlPin);

}

void loop() {
  // put your main code here, to run repeatedly:

////////////////////////// Interupt needs to give both a distance and an angle for both x and z in order to target. prefferred baud rate above 9600 for quick targeting
////////////////////////// ultrasonic hc-sr04 will not work for a z coordinate, there is no vertical sweep. 
////////////////////////// quadrant 1 and part of 3 coded, need an equation to say if the target is beyond between the radar and turrent meaning the traingles are leaning and not 
/////////////////////////// converging between, then change the equation. outside the range between coded. in between is currently a miss zone.
}
// side c = base between turrent and radar
// side b = radar to target
// side a = turrent to target
// angle a = radar to target from 0
// angle b = turrent to target from 0
// angle b = cosinverse((side a^2 + side c^2 - side b^2)/(2*side a* side c))
// side a = sqrt(side b^2 + side c^2 - 2*side b* side c* cos(angle a))