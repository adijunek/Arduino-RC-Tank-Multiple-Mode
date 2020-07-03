void manualMode(int rcThrottle, int rcSteer) {
  
  Serial.println("Manual");
  int lThrottle;
  int rThrottle;

  // failsafe
  if (rcThrottle == 0 & rcSteer  == 0 ) {
    mStop();
  }


  // move forward
  else if (rcThrottle > 1500 ) {
    rcThrottle = map(rcThrottle, 1500, 2000, 0, 255);

    if (rcSteer > 1500) {         // forward turn right


      rThrottle = map(rcSteer, 1500, 2000, rcThrottle, 0);

      rMotor.setSpeed(rThrottle);
      lMotor.setSpeed(rcThrottle);

      rMotor.run(FORWARD);
      lMotor.run(FORWARD);

    }
    else if (rcSteer < 1500 ) { // FORWARD TURN LEFT

      lThrottle = map(rcSteer, 1500, 1000, rcThrottle, 0);

      lMotor.setSpeed(lThrottle);
      rMotor.setSpeed(rcThrottle);

      rMotor.run(FORWARD);
      lMotor.run(FORWARD);
    }
    else {                      // forward turn left

      rMotor.setSpeed(rcThrottle);
      lMotor.setSpeed(rcThrottle);

      rMotor.run(FORWARD);
      lMotor.run(FORWARD);
    }
  }
  // BACKWARD
  else if (rcThrottle < 1500 && rcThrottle > 0) {

    rcThrottle = map(rcThrottle, 1500, 1000, 0, 255);

    if (rcSteer > 1500) {         // backward turn right


      lThrottle = map(rcSteer, 1500, 2000, rcThrottle, 0);

      lMotor.setSpeed(lThrottle);
      rMotor.setSpeed(rcThrottle);

      rMotor.run(BACKWARD);
      lMotor.run(BACKWARD);

    }
    else if (rcSteer < 1500 ) { // backward turn left

      rThrottle = map(rcSteer, 1500, 1000, rcThrottle, 0);

      rMotor.setSpeed(rThrottle);
      lMotor.setSpeed(rcThrottle);

      rMotor.run(BACKWARD);
      lMotor.run(BACKWARD);
    }

    else {                      // backward straight

      rMotor.setSpeed(rcThrottle);
      lMotor.setSpeed(rcThrottle);

      rMotor.run(BACKWARD);
      lMotor.run(BACKWARD);
    }

  }

  // IDDLE
  else {
    if (rcSteer > 1500) {         // rotate right


      rcThrottle = map(rcSteer, 1500, 2000, 0, 255);

      rMotor.setSpeed(rcThrottle);
      lMotor.setSpeed(rcThrottle);

      rMotor.run(BACKWARD);
      lMotor.run(FORWARD);

    }
    else if (rcSteer < 1500) {     // rotate left


      rcThrottle = map(rcSteer, 1500, 1000, 0, 255);

      rMotor.setSpeed(rcThrottle);
      lMotor.setSpeed(rcThrottle);

      rMotor.run(FORWARD);
      lMotor.run(BACKWARD);

    }
    else {
      mStop();

    }

  }

}
