void movestepper (long Position, const char* message ){
  Serial.println(message);
  if  (Position > 0) {
    
    stepper.moveTo(Position);
    while (stepper.distanceToGo() != 0) {  // נמשיך להריץ את המנוע עד שהוא יגיע ליעד
    if (stepper.distanceToGo() <= Position-200 && digitalRead(lowerLimitPin) == LOW ) {
       stopProgram();
       }
    stepper.run();
      }
  } else{
    stepper.moveTo(Position);
  while (stepper.distanceToGo() != 0) {  // נמשיך להריץ את המנוע עד שהוא יגיע ליעד
    stepper.run();
  }
  }


delay(500);
  }
