void motion() {

if (myServo.read() == 0) {
movestepper  (80000,"Going Up");
 }
 rotateServo(0, 128, 10);

if (myServo.read() == 128) {
movestepper  (0,"Going Down");
}
rotateServo(128, 0, 10);
  programStarted = false; // תסמן שהתוכנית הסתיימה
  
  Serial.println("Program stopped. Press button to restart.");
}
