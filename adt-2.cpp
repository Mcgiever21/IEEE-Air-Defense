#include <BetterJoystick.h>

#include <Servo.h>




Servo ServoX;           // create servo object for x coordinate (horizontal plane)
const int xServoControlPin = 7;
const int zServoControlPin = 8;
Servo ServoZ;           // create servo object for z coordinate (vertical plane)
const int ReceiverXPin = A3; //interupt pin
const int ReceiverZPin = A4; //interupt pin
const int ReceiverAPin = A5;
const int pi=3.14159265359;
const int joystickXPin = A0;  // Replace with your X axis analog pin
const int joystickYPin = A1;  // Replace with your Y axis analog pin
const int joystickswPin = A2; //switch pin
 Joystick joystick(joystickXPin, joystickYPin, joystickswPin);  // Create joystick object
//struct TargetCoor{
  uint8_t side_XRadHyp;         // turrent to target  // side a = sqrt(side b^2 + side c^2 - 2*side b* side c* cos(angle a))
  uint8_t side_XTurHyp;         // radar to target
  uint8_t side_BaseGap;         // base between turrent and radar
  uint8_t angle_Xrad2target;        // radar to target from 0
  uint8_t angle_Xtur2target;        // turrent to target from 0   // angle b = cosinverse((side a^2 + side c^2 - side b^2)/(2*side a* side c))
  uint8_t angle_c;        // angle from  target perspective to turrent and radar
  uint8_t Elevation;      //z bar elevation from ground to target
  uint8_t side_Ztur2target;     //elevation side length
  uint8_t angle_Ztur2target;    //elevation angle for turrent
  uint8_t side_Zrad2target;     //elevation side length
  uint8_t angle_Zrad2target;    //elevation angle for turrent
  uint8_t side_Xtur2target;
  uint8_t RCX;                  //x recieving code
  
//}

void targetx_recieved()
{
  side_XRadHyp = sqrt(side_XTurHyp*side_XTurHyp + side_BaseGap*side_BaseGap - 2 * side_XTurHyp * side_BaseGap * cos(angle_Xrad2target));
  angle_Xtur2target = acos((side_XRadHyp*side_XRadHyp + side_BaseGap*side_BaseGap - side_XTurHyp*side_XTurHyp)/(2 * side_XRadHyp * side_BaseGap));
  targetz_recieved();
}
void targetz_recieved()
{
  uint8_t side_elevation = side_XRadHyp * tan(angle_Zrad2target);
  angle_Ztur2target = atan(side_elevation / side_Xtur2target);

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
void testJoystick() {
  int xVal = joystick.x();  // Read joystick X value (0-1023)
  int yVal = joystick.y();  // Read joystick Y value (0-1023)

  // Map joystick values to servo positions (adjust scaling as needed)
  int xServoPos = map(xVal, 0, 1023, 0, 180);
  int zServoPos = map(yVal, 0, 1023, 0, 180);

  ServoX.write(xServoPos);
  ServoZ.write(zServoPos);
}
void Xrecieving()
{
  RCX = analogRead(ReceiverXPin);
}
void Zrecieving()
{
  RCX = analogRead(ReceiverZPin);
}
void Arecieving()
{
  RCX = analogRead(ReceiverAPin);
}
void setup() {
  // put your setup code here, to run once:
ServoX.attach(xServoControlPin);
ServoZ.attach(zServoControlPin);
attachInterrupt(digitalPinToInterrupt(ReceiverXPin),Xrecieving,HIGH);
attachInterrupt(digitalPinToInterrupt(ReceiverZPin),Zrecieving,HIGH);
attachInterrupt(digitalPinToInterrupt(ReceiverAPin),Arecieving,HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
uint8_t recieved;
uint8_t recievedx;
uint8_t recievedxside;
  angle_Zrad2target = recieved;
  angle_Xrad2target = pi - recievedx;
  side_XRadHyp = recievedxside;
testJoystick();

////////////////////////// Interupt needs to give both a distance and an angle for both x and z in order to target. prefferred baud rate above 9600 for quick targeting
////////////////////////// ultrasonic hc-sr04 will not work for a z coordinate, there is no vertical sweep. 
////////////////////////// quadrant 1 and part of 3 coded, need an equation to say if the target is beyond between the radar and turrent meaning the traingles are leaning and not 
/////////////////////////// converging between, then change the equation. outside the range between coded. in between is currently a miss zone.
}
