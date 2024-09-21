void motion() {
  digitalWrite(enablePin, HIGH);
  stepper.setSpeed(3000);

  // תזוזה של מנוע הצעד למעלה (1200 צעדים)
  if (myServo.read() == 0) {
    moveStepperToPosition(1200, "going up");
    unsigned long currentMillis = millis();

    // בדיקה אם עזבה את המפסק גבול התחתון אחרי 2 שניות
    if (currentMillis - previousMillis >= interval) {
    // קוד שיבוצע כל 2 שניות
    previousMillis = currentMillis;
  
    if (digitalRead(lowerLimitPin) == LOW) {
      Serial.println("Error: Carriage did not leave the bottom limit switch.");
      stopProgram();  // פונקציה שעוצרת את התוכנית
      return;  // יציאה מהפונקציה
    }
    }
  }

  // סיבוב הסרוו מ-0 ל-128 מעלות
  rotateServo(0, 128, 10);

  // תזוזה של מנוע הצעד חזרה למטה (ל-0 צעדים)
  if (myServo.read() == 128) {
    moveStepperToPosition(0, "Going down");
  }

  // סיבוב הסרוו חזרה מ-128 ל-0 מעלות
  rotateServo(128, 0, 10);
   delay(500);
   if (digitalRead(lowerLimitPin) == HIGH) {
    Serial.println("Error: Carriage did not return to the bottom limit switch.");
  }



  programStarted = false; // תסמן שהתוכנית הסתיימה
  Serial.println("Program stopped. Press button to restart.");
}

// פונקציה לסיבוב סרוו
void rotateServo(int startAngle, int endAngle, int delayTime) {
  if (startAngle < endAngle) {
    for (int angle = startAngle; angle <= endAngle; angle++) {
      myServo.write(angle);
      delay(delayTime);
    }
  } else {
    for (int angle = startAngle; angle >= endAngle; angle--) {
      myServo.write(angle);
      delay(delayTime);
    }
  }
}

void moveStepperToPosition(int position, const char* message) {
  Serial.println(message);
  stepper.runToNewPosition(position);
  delay(1000);  // השהיה בין התנועות
}

// פונקציה שעוצרת את התוכנית
void stopProgram() {
  Serial.println("Stopping program due to error.");
  while (true) {
    // לולאה אינסופית שתעצור את התוכנית
  }
}
