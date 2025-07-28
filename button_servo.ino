#include <Servo.h>

const int analogXPin = A0;
const int analogYPin = A1;
const int analogButtonPin = A2;

// Default values when joystick is centered (tweak if needed)
const int xNeutral = 125;
const int yNeutral = 125;

struct button {
  byte pressed = 0;
};

struct analogInput {
  int x, y;
  button myButton;
};

Servo myServo;

int servoNeutral = 115; // Adjust so arm is parallel when centered

void setup() {
  pinMode(analogButtonPin, INPUT_PULLUP);
  myServo.attach(9);
  Serial.begin(115200);
}

void loop() {
  analogInput analog;

  analog.x = readAnalogAxisLevel(analogXPin) - xNeutral;
  analog.y = readAnalogAxisLevel(analogYPin) - yNeutral;

  // Dead zone
  if (abs(analog.x) < 5) analog.x = 0;
  if (abs(analog.y) < 5) analog.y = 0;

  // Calculate angle (range: -180° to 180°)
  float angle = atan2(analog.y, analog.x) * 180.0 / PI;
  
  // Reverse mapping to correct direction
  int servoOffset = map((int)angle, -90, 90, 65, -65);
  int servoAngle = constrain(servoNeutral + servoOffset, 0, 180);


  myServo.write(servoAngle);

  analog.myButton.pressed = isAnalogButtonPressed(analogButtonPin);

  // Debug output
  Serial.print("X: ");
  Serial.println(analog.x);
  Serial.print("Y: ");
  Serial.println(analog.y);
  Serial.print("Angle: ");
  Serial.println(angle);
  Serial.print("Servo angle: ");
  Serial.println(servoAngle);

  if (analog.myButton.pressed) {
    Serial.println("Button pressed");
  }

  delay(200);
}

int readAnalogAxisLevel(int pin) {
  return map(analogRead(pin), 0, 1023, 0, 255);
}

bool isAnalogButtonPressed(int pin) {
  return digitalRead(pin) == 0;
}
