
void followMode(){
  
  Serial.println("Follow");

  int distance = readPing();

  Serial.println(distance);
  
  if(distance <= 100 && distance > 30){

    rMotor.setSpeed(255);
    lMotor.setSpeed(255);    
    
    rMotor.run(FORWARD);
    lMotor.run(FORWARD);
    
  }else if(distance <= 30 && distance > 20){
    //stop
    mStop();
  
  }else if(distance <=20 ){
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
