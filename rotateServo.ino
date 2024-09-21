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
  delay(500);
}