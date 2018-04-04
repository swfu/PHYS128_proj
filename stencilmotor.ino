#include <Servo.h>

Servo servo;
int servoPin = 11;

void setup()
{
  servo.attach(servoPin);
  Serial.begin(9600);
  Serial.println("set Angle 0 to 180");}
  
//  servo.write(90);
// }
// int pos;
// void loop() {
//   //servo.write(0);
//   for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
//   {                                  // in steps of 1 degree 
//     servo.write(pos);              // tell servo to go to position in variable 'pos' 
//     delay(15);                       // waits 15ms for the servo to reach the position 
//   }
//   delay(50000);

// }


int angle;

void loop() {
  if (Serial.available())
  {
    // char str[10];
    angle = Serial.parseInt(); 
    // itoa(angle, str, 10);
    Serial.println("Angle");
    // Serial.println(str);
    if (angle >= 0.05 && angle <= 180)
      {
        servo.write(angle);
        Serial.println(angle);
        delay(1000);
      }
  }
}



// void setup() {
// Serial.begin(9600);
// myservo.writeMicroseconds(1500); //set initial servo position if desired
// myservo.attach(7);  //the pin for the servo control 
// Serial.println("servo-test-22-dual-input"); // so I can keep track of what is loaded
// }

// void loop() {
// while (Serial.available()) {
//   char c = Serial.read();  //gets one byte from serial buffer
//   readString += c; //makes the string readString
//   delay(2);  //slow looping to allow buffer to fill with next character
// }

// if (readString.length() >0) {
//   Serial.println(readString);  //so you can see the captured string 
//   int n = readString.toInt();  //convert readString into a number

//   // auto select appropriate value, copied from someone elses code.
//   if(n >= 500)
//   {
//     Serial.print("writing Microseconds: ");
//     Serial.println(n);
//     myservo.writeMicroseconds(n);
//   }
//   else
//   {   
//     Serial.print("writing Angle: ");
//     Serial.println(n);
//     myservo.write(n);
//   }

//   readString=""; //empty for next input
// } 
// }
