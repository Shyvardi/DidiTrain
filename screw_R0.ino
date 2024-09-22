#include <AccelStepper.h>
#include <Servo.h>

const int buttonPin = 7;    // פין שאליו מחובר הלחצן
const int servoPin = 5;     // פין שאליו מחובר הסרוו
const int stepPin = 8;      // פין ה-PUL של בקר ה-TB6600
const int dirPin = 10;      // פין ה-DIR של בקר ה-TB6600
const int enablePin = 9;    // פין ה-ENA של בקר ה-TB6600
const int lowerLimitPin = 2; // פין של מפסק הגבול התחתון




int buttonState = 0;        // משתנה לאחסון מצב הלחצן הנוכחי
int lastButtonState = 0;    // משתנה לאחסון מצב הלחצן הקודם
bool programStarted = false; // דגל לבדיקת תחילת התוכנית
bool errorFlag = false;  // משתנה שמייצג את מצב השגיאה
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin); // יצירת אובייקט למנוע צעד
Servo myServo;               // יצירת אובייקט סרוו

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(lowerLimitPin, INPUT_PULLUP);

  myServo.attach(servoPin);
  Serial.begin(9600);

  stepper.setMaxSpeed(1000000);
  stepper.setAcceleration(1500);
  stepper.setSpeed(30000);
  digitalWrite(enablePin, HIGH);
  if (digitalRead(lowerLimitPin) == HIGH) {
  home();
  } else { stepper.setCurrentPosition(0);}
}

void loop() {
    
// קריאת מצב הלחצן הנוכחי
  buttonState = digitalRead(buttonPin);

  // בדיקה אם יש שינוי ממצב לא לחוץ ללחוץ
  if (buttonState == HIGH && lastButtonState == LOW && !programStarted) {
    Serial.println("Button pressed, starting the program...");
    programStarted = true; // התחלת התוכנית
    motion();
    
  }

  // שמירת המצב הנוכחי למצב הקודם ללולאה הבאה
  lastButtonState = buttonState;
}
void stopProgram() {
  Serial.println("Program stopped.");
  while (true);
}





