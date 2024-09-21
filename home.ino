void Home() {
  if (digitalRead(lowerLimitPin) == HIGH) {
   
  
  Serial.println("Home");
  // Move towards the limit switch slowly
  digitalWrite(enablePin, HIGH);
  stepper.moveTo(-1);
  stepper.setSpeed(600);
  
  // While we haven't hit the limit switch, keep moving
  while (digitalRead(lowerLimitPin)) {
    stepper.run();
  }
  
  // We hit the limit switch, so first stop and back up a bit
  stepper.stop();
  delay(50); // Short delay for the stop to take effect
  stepper.setCurrentPosition(0); // Set this position as 0
  stepper.move(-10); // Move back 100 steps from switch
  
  // Move back from the switch
  while(stepper.currentPosition() > -10) {
    stepper.run();
  }
  
  // Now set the desired position to go to after homing
  stepper.setCurrentPosition(0); // Reset position again to 0 if needed
  stepper.setMaxSpeed(400); // Set the target speed for moving towards desired position
  stepper.setAcceleration(400); // Set the acceleration
  // Set the target position after homing
  stepper.moveTo(10); // We want to move to position 500 after homing
  
  // Go to the target position from the backed-up position
  
  
  // Optional: Set the current position to 0 again if this is your new home/reference position
  stepper.setCurrentPosition(0);
  
 

} 

}