int initSpeed = 0;
int maxSpeed = 255;


void followMode(){
  
  Serial.println("Follow");

  int distance = readPing();

  Serial.println(distance);
  
  if(distance <= 100 && distance > 30){
    // move forward

    rMotor.setSpeed(255);
    lMotor.setSpeed(255);    
    
    rMotor.run(FORWARD);
    lMotor.run(FORWARD);
    
  }else if(distance <= 30 && distance > 20){
    //stop
    mStop();
  
  }else if(distance <=20 && distance >0){
    rMotor.setSpeed(255);
    lMotor.setSpeed(255);
    rMotor.run(BACKWARD);
    lMotor.run(BACKWARD);
  
  }else{
    //stop
    rMotor.run(RELEASE);
    lMotor.run(RELEASE);    
  }

}
