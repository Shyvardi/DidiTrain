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
  pinMode(buttonPin, INPUT);  // הגדרת פין הלחצן כקלט
  pinMode(enablePin, OUTPUT); // פין ההפעלה של בקר המנוע
  pinMode(lowerLimitPin, INPUT_PULLUP); // מפסק גבול תחתון עם Pull-up פנימי
 
  myServo.attach(servoPin);   // חיבור הסרוו לפין 5
  Serial.begin(9600);         // פתיחת חיבור סדרתי לצורכי דיבוג

  // קביעת מהירות ותאוצה למנוע הצעד
  stepper.setMaxSpeed(2000);  // הגדרת מהירות מקסימלית
  stepper.setAcceleration(500);
  Home();

  Serial.println("Servo go to 0");
  for (int angle = myServo.read(); angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);  // המתנה של 15ms כדי להאט את התנועה
  }
  Serial.println("Servo at 0 ");
  Serial.println("לחץ על הכפתור להתחלת תנועה");
}

void loop() {
  
 
  delay(1000);
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


  









  
  