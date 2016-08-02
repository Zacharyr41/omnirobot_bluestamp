 #include <PS2X_lib.h>  //for v1.6, most current version as of 2013 see billporter.info for updates
#include <Servo.h>         //copy from servo code
// a maximum of eight servo objects can be created
#include <NewPing.h>
Servo myservoA;  // works on motor A
Servo myservoB;  // works on motor B
Servo myservoC;  // works on motor C
Servo microServo; // Motor on the walkie talkie
PS2X ps2x; // create PS2 Controller Class

#define TRIGGER_PIN  27  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     26  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_TWO 29 //Pin for second sensor, next is trig for second, and then third for each
#define ECHO_PIN_TWO 28
#define TRIGGER_PIN_THREE 31
#define ECHO_PIN_THREE 30
#define MAX_DISTANCE 200
NewPing sonarone(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Configuring the sensors
NewPing sonartwo(TRIGGER_PIN_TWO, ECHO_PIN_TWO, MAX_DISTANCE);
NewPing sonarthree(TRIGGER_PIN_THREE, ECHO_PIN_THREE, MAX_DISTANCE);

  int timesRun = 0; // times loop has been run
int error = 0;// error, type, and vibrate are all used to configure controller.
byte type = 0;
byte vibrate = 0;
long lastDebounce;
                                                                                            
void setup() {
  Serial.begin(115200);
  myservoA.attach(2);  // attaches the servo on pin 3 to the servo object  //copy from servo code
 myservoB.attach(3);  // attaches the servo on pin 5 to the servo object
 myservoC.attach(4);  // attaches the servo on pin 6 to the servo object
 microServo.attach(5); // walkie talkie servo to pin 5
pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
  

  error = ps2x.config_gamepad(25, 24, 23, 22, true, true); //setup pins (in this order) and settings:  GamePad(clock, command, attention, data, Pressures, Rumble)
  //Pay attention to order of "command" and "attention" wires


  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("HOLDING L1 or R1 will print out the ANALOG STICK values.");
    Serial.println("www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
  }

}

void loop() {
  /* You must Read Gamepad to get new values
    Read GamePad and set vibration values
    ps2x.read_gamepad(small motor on/off, larger motor strength from 0-255)
    if you don't enable the rumble, use ps2x.read_gamepad(); with no values
    you should call this at least once a second
  */
  
  if (error == 1) { //skip loop if no controller found
    return;
  } else { //DualShock Controller Found
    ps2x.read_gamepad(false, vibrate);      //false unless a command written for vibrate (if "true" large motor spins at 'vibrate' speed)
   // vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on how hard you press the blue (X) button
  }

  /*Large portions below commented out are included in source code, uncomment as needed.
    Placing code under the "if" commands allow you to configure buttons.
  */

  //    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
  //      Serial.println("Start is being held");
  //    if(ps2x.Button(PSB_SELECT))
  //      Serial.println("Select is being held");
  //
  //    if(ps2x.Button(PSB_PAD_UP)) {
  //      Serial.print("Up held this hard: ");
  //      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
  //    }
  //    if(ps2x.Button(PSB_PAD_RIGHT)){
  //      Serial.print("Right held this hard: ");
  //      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
  //    }
  //    if(ps2x.Button(PSB_PAD_LEFT)){
  //      Serial.print("LEFT held this hard: ");
  //      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
  //    }
  //    if(ps2x.Button(PSB_PAD_DOWN)){
  //      Serial.print("DOWN held this hard: ");
  //      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
  //    }
  //
  //
  //    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
  //    {
  //
  //      if(ps2x.Button(PSB_L1))
  //        Serial.println("L1 pressed");
  //      if(ps2x.Button(PSB_R1))
  //        Serial.println("R1 pressed");
  //      if(ps2x.Button(PSB_L2))
  //        Serial.println("L2 pressed");
  //      if(ps2x.Button(PSB_R2))
  //        Serial.println("R2 pressed");
  //      if(ps2x.Button(PSB_GREEN))
  //        Serial.println("Triangle pressed");
  //
  //    }
  //
  // if(ps2x.ButtonPressed(PSB_RED)) {         //will be TRUE if button is pressed
  //
  // if(ps2x.ButtonReleased(PSB_RED)) {         //will be TRUE if button is released
  //
  // if(ps2x.ButtonPressed(PSB_PINK)) {         //will be TRUE if button is pressed
  //
  // if(ps2x.ButtonReleased(PSB_PINK)) {         //will be TRUE if button is released
  
   if(ps2x.ButtonPressed(PSB_RED)){ // For the walkie talkie servo
      
      microServo.write(160)
      ;//will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");}
  if (ps2x.ButtonReleased(PSB_RED))
  {
    microServo.write(90); // Set it to rest when released.
  }

  
  //    if(ps2x.ButtonPressed(PSB_PINK)){             //will be TRUE if button was JUST released
  //      Serial.println("Square just pressed");}
  //
  //    if(ps2x.NewButtonState(PSB_BLUE)) {           //will be TRUE if button was JUST pressed OR released
  //      Serial.println("X just changed");
  //    }
  //---------------------------------------------------------------------------------------------------------------------------------
  
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uoneS = sonarone.ping();// Send ping, get ping time in microseconds (uS).
  unsigned int utwoS = sonartwo.ping(); // Get the ping for each sensor, the distance amounts are after the pings are converted
  unsigned int uthreeS = sonarthree.ping();
  float distanceone = uoneS/US_ROUNDTRIP_CM;
  float distancetwo = utwoS/US_ROUNDTRIP_CM;
  float distancethree = uthreeS/US_ROUNDTRIP_CM;
  
  Serial.print("Ping 1: "); // writing it to the serial monitor
  Serial.print(distanceone); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  Serial.print("Ping 2: ");
  Serial.print(distancetwo); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  Serial.print("Ping 3: ");
  Serial.print(distancethree); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  millis();
if (distanceone < 6 && distanceone != 0) {
  unsigned long a = millis(); // time in program until this point
Serial.println("A is:");
Serial.print(a);
  if ((millis() - a) < 1000){ // Move servos in opposite direction for 1000 ms, or one second
    
    myservoA.writeMicroseconds(1000); // writing the particular servos in the right direction to move opposite the sensor
    myservoC.writeMicroseconds(2000);
  }
 /* else {
    myservoA.writeMicroseconds(1500);
    myservoC.writeMicroseconds(1500);
  }*/
}
 else if (distancetwo < 6 && distancetwo !=0){
 unsigned long b = millis();
Serial.println("B is:");
Serial.print(b);
  if ((millis() - b )< 1000){
    
    myservoC.writeMicroseconds(1000);
    myservoB.writeMicroseconds(2000);
    
  }
 /* else {
    myservoC.writeMicroseconds(1500);
    myservoB.writeMicroseconds(1500);
  }*/
}
 else if (distancethree < 6 && distancethree != 0){
  unsigned long c = millis();
  Serial.println("C is:");
Serial.print(c);
 if ((millis() - c) < 1000){
  
    myservoB.writeMicroseconds(1000);
    myservoA.writeMicroseconds(2000);
  }
  /*else {
    myservoB.writeMicroseconds(1500);
    myservoA.writeMicroseconds(1500);
  }*/
}
else { // if the robot is not about to crash.

  int val = ps2x.Analog(PSS_RX); // reads the value of RX on the the PS2 receiver (value between 0 and 255)
  int mapval = map(val, 0, 255, 2000, 1000); //reads val, creates a mapval integer between 1000 and 2000 that motor controller reads

  int x = ps2x.Analog(PSS_LX); // reads the value of LX on the the PS2 receiver (value between 0 and 255)
  int y = ps2x.Analog(PSS_LY); // reads the value of LY on the the PS2 receiver (value between 0 and 255)

   
if (x == 128 && y == 127 && mapval == 128) {
    myservoA.writeMicroseconds(1500);  //making sure nothing happens if nothing is pressed or moved
    myservoB.writeMicroseconds(1500);
    myservoC.writeMicroseconds(1500);
    delay(10);
  }
     


  
  if (x == 128 && y == 127) {
    myservoA.writeMicroseconds(mapval);  //stationary rotation, spin in onoe direction, used to help configure camera.
    myservoB.writeMicroseconds(mapval);
    myservoC.writeMicroseconds(mapval);
    delay(10);
  }


  int mapx = map(x, 0, 255, 100, -100);
  int mapy = map(y, 0, 255, 100, -100); //values from PS2 controller are read from 0-255, read as 100 to -100 value to represent a 
  //cartesian plane with a 0 in the center to simplify calculations. Numbers opposite in highest to lowest because you need to invert the values from the analog

  float theta = atan2(mapx, mapy); // arc tangent of x/y. The measure of the angle facing x axi

  int L = sqrt(mapx * mapx + mapy * mapy); //Pythagorean theorem, L is the hypotenuse.

  float wheelone = L * cos(150 * M_PI / 180 - theta); //150 degrees minus theta
  float wheeltwo = L * cos(30 * M_PI / 180 - theta); //first value is L (hypotenuse)
  float wheelthree = L * cos(270 * M_PI / 180 - theta); //second value (parentheses section) represents adjacent side along x axis
// Based on the variations of theta and the hypotenuse, this "re-aligns" the axes which is why only cosine is used for the x.
  int Fa = map(wheelone, -142, 142, 1000, 2000); //-142 and 142 are limits of calculations above (should be), map them to servo range.
  int Fb = map(wheeltwo, -142, 142, 1000, 2000);
  int Fc = map(wheelthree, -142, 142, 1000, 2000);


 int dThree = analogRead(3);
 
  int readFa = myservoA.read();
    int readFb = myservoB.read();
    int readFc = myservoC.read();
     int mapFa = map(Fa, 1000, 2000, 0, 180);
   int mapFb = map(Fb, 1000, 2000, 0, 180);
   int mapFc = map(Fc, 1000, 2000, 0, 180);
  

   if (ps2x.Analog(PSS_LX) == 255 && ps2x.Analog(PSS_LY)== 255){
       //return;
    
   }
    if (val == 128) {   
    if (x > 136 || x < 120 || y > 136 || y < 120){
    //F values indicate motor rotation, robot navigation
  
   
    myservoA.writeMicroseconds(Fa);
    myservoB.writeMicroseconds(Fb);
    myservoC.writeMicroseconds(Fc);
    
      
      
    
    delay(10);
    }
  }

  //Next four sets of code allow you to read stick values
  if (ps2x.Button(PSB_L1)) {
    Serial.print(Fa, DEC);
    Serial.print(",");
    Serial.print(Fb, DEC);
    Serial.print(",");
    Serial.println(Fc, DEC);
  }

  if (ps2x.Button(PSB_L2)) {
    Serial.print(ps2x.Analog(PSS_LX), DEC);
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_LY), DEC);
  }                                          //same values as R2

  if (ps2x.Button(PSB_R1)) {
    Serial.print(ps2x.Analog(PSS_RX), DEC);
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RY), DEC);
  }

  if (ps2x.Button(PSB_R2)) {
    Serial.print(x, DEC);
    Serial.print(",");
    Serial.println(y, DEC);
  }            
}//same values as L2
  Serial.println ("LX is");
  Serial.print (ps2x.Analog(PSS_LX));
  Serial.println("LY is");
  Serial.print(ps2x.Analog(PSS_LY));
  delay(50);

timesRun = timesRun + 1;
Serial.print("Times Run is:");
Serial.println(timesRun);
}

