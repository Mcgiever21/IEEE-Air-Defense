#include <Servo.h>
#include <attachinterrupt>

Servo ServoX;           // create servo object for x coordinate (horizontal plane)
Servo ServoZ;           // create servo object for z coordinate (vertical plane)
ReceiverXPin = null;
ReceiverZPin = null;

//struct TargetCoor{
  float side_XRadHyp;         // turrent to target  // side a = sqrt(side b^2 + side c^2 - 2*side b* side c* cos(angle a))
  float side_XTurHyp;         // radar to target
  float side_BaseGap;         // base between turrent and radar
  float angle_Xrad2target;        // radar to target from 0
  float angle_Xtur2target;        // turrent to target from 0   // angle b = cosinverse((side a^2 + side c^2 - side b^2)/(2*side a* side c))
  float angle_c;        // angle from  target perspective to turrent and radar
  float Elevation;      //z bar elevation from ground to target
  float side_Ztur2target;     //elevation side length
  float angle_Ztur2target;    //elevation angle for turrent
  float side_Zrad2target;     //elevation side length
  float angle_Zrad2target;    //elevation angle for turrent
//}

void targetx_recieved()
{
  side_XRadHyp = sqrt(side_XTurHyp^2 + side_BaseGap^2 - 2 * side_XTurHyp * side_BaseGap * cos(angle_Xrad2target));
  angle_Xtur2target = cosinverse((side_XRadHyp^2 + side_BaseGap^2 - side_XTurHyp^2)/(2 * side_XRadHyp * side_BaseGap));
  targetz_recieved()
}
void targetz_recieved()
{
  side_elevation = side_xradHyp * tan(angle_zrad2target);
  angle_ztur2target = taninverse(side_elevation / side_xtur2target);

}

void turrent_point()
{
  if(angle_Xtur2target > pi){
    angle_Xtur2target = angle_Xtur2target - pi;
    angle_Ztur2target= pi - angle_Ztur2target;
  }
  ServoX.write(angle_Xtur2target);
  ServoZ.write(angle_Ztur2target);
}
void setup() {
  // put your setup code here, to run once:
ServoX.attach(xServoControlPin);
ServoZ.attach(zServoControlPin);


}

void loop() {
  // put your main code here, to run repeatedly:

  angle_Zrad2target = float recieved;
  angle_Xrad2target = pi - float recievedx;
  side_XRadHyp = float recievedxside;

////////////////////////// Interupt needs to give both a distance and an angle for both x and z in order to target. prefferred baud rate above 9600 for quick targeting
////////////////////////// ultrasonic hc-sr04 will not work for a z coordinate, there is no vertical sweep. 
////////////////////////// quadrant 1 and part of 3 coded, need an equation to say if the target is beyond between the radar and turrent meaning the traingles are leaning and not 
/////////////////////////// converging between, then change the equation. outside the range between coded. in between is currently a miss zone.
}
