void home() {
  if (digitalRead(lowerLimitPin) == HIGH) {
   
  
  Serial.println("Start Homing ");
  // Move towards the limit switch slowly
  
  stepper.setSpeed(30000);
  stepper.moveTo(-10);
 
  // While we haven't hit the limit switch, keep moving
  while (digitalRead(lowerLimitPin)) {
    Serial.println("going home");
    stepper.run();
  }
  
  // We hit the limit switch, so first stop and back up a bit
  stepper.stop();
  delay(50); // Short delay for the stop to take effect
  stepper.setCurrentPosition(0); // Set this position as 0
 // stepper.move(-10); // Move back 100 steps from switch
  
  // Move back from the switch
 // while(stepper.currentPosition() > -10) {
 //   stepper.run();
 // }
  
  // Now set the desired position to go to after homing
 // stepper.setCurrentPosition(0); // Reset position again to 0 if needed
  
  
 

} 

    
    myServo.write(0);              // tell servo to go to position in variable 'pos'
    delay(1000);         
  
      
    
Serial.println("Press button to restart.");

}