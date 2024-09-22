void movestepper (long Position, const char* message ){
  Serial.println(message);
  if  (Position > 0) {
    
    stepper.moveTo(Position);
    while (stepper.distanceToGo() != 0) {  // נמשיך להריץ את המנוע עד שהוא יגיע ליעד
    if (stepper.distanceToGo() <= Position-200 && digitalRead(lowerLimitPin) == LOW ) {
       Serial.println("לא זז מהמקום");
       
       //stopProgram();
       }
    stepper.run();
      }
  } else{
    stepper.moveTo(Position);
  while (stepper.distanceToGo() != 0) {  // נמשיך להריץ את המנוע עד שהוא יגיע ליעד
    stepper.run();
  }
  if (digitalRead(lowerLimitPin) == HIGH ){
    Serial.println("לא הגיע למקום");
    
    //stopProgram();
     }
  }


delay(500);
  }
