const int analogXPin = A0;
const int analogYPin = A1; 
const int analogButtonPin = A2;
   
//Default values when axis not actioned 
const int xNeutral = 128; 
const int yNeutral = 128;
   
struct button { 
   byte pressed = 0; 
}; 
   
struct analog { 
   int x, y; 
   
   button myButton; 
}; 
   
void setup() 
{ 
   pinMode(analogButtonPin, INPUT_PULLUP); 
   
   Serial.begin(115200); 
} 
   
void loop() 
{ 
   analog analog; 
   
   analog.x = readAnalogAxisLevel(analogXPin) - xNeutral; 
   analog.y = readAnalogAxisLevel(analogYPin) - yNeutral; 
   
   analog.myButton.pressed = isAnalogButtonPressed(analogButtonPin); 
   
   Serial.print("X:"); 
   Serial.println(analog.x); 
   
   Serial.print("Y:"); 
   Serial.println(analog.y); 
   
   if (analog.myButton.pressed) { 
     Serial.println("Button pressed"); 
   } else { 
     Serial.println("Button not pressed"); 
   } 
   
   delay(200); 
} 
   
byte readAnalogAxisLevel(int pin) 
{ 
   return map(analogRead(pin), 0, 1023, 0, 255); 
} 
   
bool isAnalogButtonPressed(int pin) 
{ 
   return digitalRead(pin) == 0; 
} 
