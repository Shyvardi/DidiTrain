#include <AccelStepper.h>
#include <Servo.h>

const int buttonPin = 7;    // פין שאליו מחובר הלחצן
const int servoPin = 5;     // פין שאליו מחובר הסרוו
const int stepPin = 8;      // פין ה-PUL של בקר ה-TB6600
const int dirPin = 10;      // פין ה-DIR של בקר ה-TB6600
const int enablePin = 9;    // פין ה-ENA של בקר ה-TB6600
const int lowerLimitPin = 2; // פין של מפסק הגבול התחתון
const int upperLimitPin = 3; // פין של מפסק הגבול העליון

int buttonState = 0;        // משתנה לאחסון מצב הלחצן הנוכחי
int lastButtonState = 0;    // משתנה לאחסון מצב הלחצן הקודם
bool programStarted = false; // דגל לבדיקת תחילת התוכנית

int ServoStartDealy = 20; // מהירות סיבוב הסרוו בהתחלה
int screwspeed = 2000; // מהירות הבורג



AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin); // יצירת אובייקט למנוע צעד
Servo myServo;               // יצירת אובייקט סרוו

void setup() {
  pinMode(buttonPin, INPUT);  // הגדרת פין הלחצן כקלט
  pinMode(enablePin, OUTPUT); // פין ההפעלה של בקר המנוע
  pinMode(lowerLimitPin, INPUT_PULLUP); // מפסק גבול תחתון עם Pull-up פנימי
  pinMode(upperLimitPin, INPUT_PULLUP); // מפסק גבול עליון עם Pull-up פנימי
  myServo.attach(servoPin);   // חיבור הסרוו לפין 5
  Serial.begin(9600);         // פתיחת חיבור סדרתי לצורכי דיבוג

  // קביעת מהירות ותאוצה למנוע הצעד
  stepper.setMaxSpeed(2000);  // הגדרת מהירות מקסימלית
  stepper.setAcceleration(500);
  moveServoToZeroSlowly;
  // בדיקה אם העגלה במצב התחתון
  checkInitialPosition();
  Serial.print ("ממתין להפעלה");
}

void loop() {
  // קריאת מצב הלחצן הנוכחי
  buttonState = digitalRead(buttonPin);

  // בדיקה אם יש שינוי ממצב לא לחוץ ללחוץ
  if (buttonState == HIGH && lastButtonState == LOW && !programStarted) {
    Serial.println("Button pressed, starting the program...");
    programStarted = true; // התחלת התוכנית
    startProgram();
  }

  // שמירת המצב הנוכחי למצב הקודם ללולאה הבאה
  lastButtonState = buttonState;
}

void startProgram() {
  // הפעלת מנוע הצעד
  digitalWrite(enablePin, HIGH); // הפעלת בקר המנוע (Active High)

  // סובב את העגלה למעלה עד הגעה למפסק העליון
  moveToUpperLimit();
  
  
  // סובב את הסרוו ב-180 מעלות
  Serial.println("Rotating servo to 180 degrees...");
  digitalWrite(enablePin, LOW);
  for (int angle = 0; angle <= 180; angle=angle+5) {
    myServo.write(angle);
   
  }
  
  
  Serial.println("סרבו סיים");
  delay(1000);
  // לאחר סיבוב הסרוו, התחלת תנועת העגלה חזרה למפסק התחתון
  moveToLowerLimit();
  

  // סובב את הסרוו חזרה ל-0 מעלות
  Serial.println("Rotating servo back to 0 degrees...");
  for (int angle = 180; angle >= 0; angle = angle-5) {
    myServo.write(angle);
    
        delay(2);  // המתנה של 15ms כדי להאט את התנועה
  }


  // כיבוי מנוע הצעד
  digitalWrite(enablePin, LOW); // כיבוי בקר המנוע

  // עצירת התוכנית והמתנה ללחיצה על הכפתור מחדש
  programStarted = false; // תסמן שהתוכנית הסתיימה
  Serial.println("Program stopped. Press button to restart.");
}



void moveToUpperLimit() {
  Serial.println("Moving carriage to upper limit...");

  // קביעת כיוון ומהירות המנוע לכיוון מעלה
  stepper.setSpeed(2000);

  // תנועה עד שמפסק הגבול העליון יילחץ
  while (digitalRead(upperLimitPin) == HIGH) {
    stepper.runSpeed();  // סיבוב המנוע
  }

  Serial.println("Upper limit reached.");
  stepper.stop();
  
}

void moveToLowerLimit() {
  //digitalWrite(enablePin, HIGH);
  Serial.println("Moving carriage to lower limit...");
  digitalWrite(enablePin, HIGH);
  // קביעת כיוון ומהירות המנוע לכיוון מטה
  stepper.setSpeed(-2000);

  // תנועה עד שמפסק הגבול התחתון יילחץ
  while (digitalRead(lowerLimitPin) == HIGH) {
    stepper.runSpeed();  // סיבוב המנוע
  }

  Serial.println("Lower limit reached.");
  stepper.stop();
}


void moveServoToZeroSlowly() {
  Serial.println("Moving servo to 0 degrees slowly...");
  
  // סיבוב הסרוו לאט ל-0 מעלות
  for (int angle = myServo.read(); angle >= 0; angle--) {
    myServo.write(angle);
    delay(ServoStartDealy);  // המתנה של 15ms כדי להאט את התנועה
  }

  Serial.println("Servo reached 0 degrees.");
}
void checkInitialPosition() {
  // הפעלת מנוע הצעד
  digitalWrite(enablePin, HIGH); // הפעלת בקר המנוע
  
  // בדיקה אם העגלה במצב התחתון
  if (digitalRead(lowerLimitPin) == LOW) {
    Serial.println("Carriage is already at the lower limit.");
    return; // אם העגלה במצב התחתון, ממשיכים לתוכנית
  }
  
  // אם העגלה לא במצב התחתון, סובב את המנוע ימינה עד שמגיעים למפסק התחתון
  Serial.println("Moving carriage to the lower limit...");
  stepper.setSpeed(-screwspeed);  // קביעת מהירות מקסימלית בכיוון הפוך

  while (digitalRead(lowerLimitPin) == HIGH) {
    stepper.runSpeed();  // סיבוב המנוע
  }

  Serial.println("Carriage reached the lower limit.");
  stepper.stop();        // עצירת המנוע
  delay(500);            // השהייה קלה
  digitalWrite(enablePin, LOW); // כיבוי בקר המנוע
}
