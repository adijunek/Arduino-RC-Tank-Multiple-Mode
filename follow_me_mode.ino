
/* Object Following Simple Alogarithm 
 * Juni Adi Juni Adi 06/29/2020
 */
 
int forwardDistance = 100;  // maximum distance to follow (move forward)
int stopDistance = 30;      // maximum distance to stop
int backwardDistance = 20;  // maximum distance to backup (move backward)

void followMode(){
  
  Serial.println("Follow");

  int distance = readPing();

  Serial.println(distance);
  
  if(distance <= forwardDistance && distance > stopDistance){

    rMotor.setSpeed(255);
    lMotor.setSpeed(255);    
    
    rMotor.run(FORWARD);
    lMotor.run(FORWARD);
    
  }else if(stopDistance <= 30 && distance > backwardDistance){
    //stop
    mStop();
  
  }else if(distance <= backwardDistance ){
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
