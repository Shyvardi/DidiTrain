void home() {
  
   
  delay(500);
  Serial.println("Start Homing ");
  //stepper.setSpeed(1000);
  stepper.moveTo(-100);
  stepper.setSpeed(1000);
 
 
  
  while (digitalRead(lowerLimitPin) == HIGH) {
    
    stepper.run();
  }
  //
  // We hit the limit switch, so first stop and back up a bit
  stepper.stop();
  delay(50); // Short delay for the stop to take effect
  stepper.setCurrentPosition(0); // Set this position as 0
 
  

  
  
 



    
    myServo.write(0);              // tell servo to go to position in variable 'pos'
    delay(1000);         
  
      
    
Serial.println("Press button to restart.");

}
