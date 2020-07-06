/* Obstacle Avoidance Alogarithm
 *  Juni Adi, July 6th 2020
 * 
 * When the vehicle detects an obstacle in range (MIN_DISTANCE), it will:
 * 1. Stop
 * 2. Rotate left (with predefined 'angle': DEFAULT_TURNTIME), then measure the distance 
 * 3. Rotate right (twice as much angle as the left rotate), then measure the distance
 * 4. Move forward based on which distance is bigger (left or right)
 * 
 * Since we do not use stepper motors, we use time (millis) to control  
 * the amount of rotation (angle) when it turn left/right to find the bigger distance 
 * 
 * If one 'look-around' loop failed i.e the bigger distance is less than MIN_DISTANCE,
 * the loop will re-iterate with adding e predefined amount of time: addTime (to produce a bigger angle)
 */


#define MIN_DISTANCE 20 // distance (cm) to obstacle that triger avoidance behaviour 
#define DEFAULT_TURNTIME 50 // how many milliseconds is a turn procces take time 
                            // i.e how wide is the angle of turn
int turnTime = DEFAULT_TURNTIME; 
int addTime = 10; // adding time (millisecond)/incrementing angle if the last 'look arround' failed 

int obstacle = 0;
unsigned long timeLapse = 0;
int goLookLeft = 1;
int goLookRight = 0;

int rDistance;
int lDistance;

void avoidanceMode(){
  if(obstacle == 1){
  
    lookArround(turnTime);

  }else{

     moveForward();
  }  
}

void lookArround(int turnTime){

      //rotate left first 
      if(goLookLeft == 1){
          if(timeLapse == 0){
            timeLapse = millis();
          }else{
              if(millis() - timeLapse <= turnTime ){
                  mTurnLeft();             
              }else{
                  mStop();
                  timeLapse = 0;
                  goLookLeft=0;
                  goLookRight=1;
                  lDistance=readPing();                
              }
          }
          
      }

      //than rotate right
      if(goLookRight == 1){
          if(timeLapse == 0){
            timeLapse = millis();
          }else{
              if(millis() - timeLapse <= turnTime ){
                  mTurnRight();             
              }else{
                  mStop();
                  timeLapse = 0;
                  goLookRight=0;
                  lDistance=readPing();
              }
          }
   
      }

      /* decision is made based on left distance and right distance
       * 
       */
      if(goLookLeft == 0 && goLookRight == 0){
          // if right distance is bigger
          // immediately move forward as the vehicle is now in the right radian position
          if(rDistance >= lDistance && rDistance  > MIN_DISTANCE){
              obstacle = 0;
              goLookLeft = 1;    
          }
          // if left distance is bigger
          // go back to 'left' radian position (rotate left with twice bigger time)
          // and immediately move forward
          else if(lDistance > rDistance && lDistance > MIN_DISTANCE){
              goLookLeft = 0;

              if(timeLapse == 0){
                  timeLapse = millis();
              }else{
                  if(millis() - timeLapse <= (2*turnTime)){
                      mTurnLeft();
                  }else{
                      mStop();
                      timeLapse = 0;
                      obstacle = 0;
                      goLookLeft = 1;                    
                  }
              }
              
          }
          // the look-arround is failed
          // start over with wider angle
          else{
              //digitalWrite(relay, LOW);
              goLookLeft = 1;
              turnTime+=addTime;
              obstacle = 1;
          }
      }                  

}

void moveForward(){
    resetAvoidance(); //just to make sure 
    rMotor.setSpeed(255);
    lMotor.setSpeed(255);

    rMotor.run(FORWARD);
    lMotor.run(FORWARD);

    int distance=readPing();

    if(distance <= MIN_DISTANCE){
        mStop();
        obstacle = 1;
    }
  
}

void mTurnLeft(){
    rMotor.setSpeed(255);
    lMotor.setSpeed(255);
    rMotor.run(FORWARD);
    lMotor.run(BACKWARD);   
}

void mTurnRight(){
    rMotor.setSpeed(255);
    lMotor.setSpeed(255);
    rMotor.run(BACKWARD);
    lMotor.run(FORWARD);   
}

/*
 * Reset Avoidance variable to default 
 * in case user switch mode in the middle of look-around proccess
 * so that when he gets back to Avoidance Mode the look-around loop start from it's default value
 * 
 */
void resetAvoidance(){
    turnTime = DEFAULT_TURNTIME;
    obstacle = 0;
    timeLapse  = 0;
    goLookLeft = 1;
    goLookRight = 0;
}
