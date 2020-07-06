/* Main Program
   Juni Adi 06/29/2020
 
    Pin Configuration:
    9    : Sonar TRIG
    10   : Sonar Ping/RX
    
    A0    : CH01 :Throttle
    A1    : CH02 : Steer
    A2    : CH03 : Mode  Control Switch
    A3    : CH04 : Front Led Control Switch
    A5    : relay : Front Led relay
*/

/* Motors */
#include <AFMotor.h>

AF_DCMotor lMotor(4);
AF_DCMotor rMotor(3);

/*Ultrasonic sonar sensor*/
#include <NewPing.h>
#define TRIG_PIN 9
#define ECHO_PIN 10
#define SONAR_MAX_DISTANCE 200

NewPing sonar(TRIG_PIN, ECHO_PIN, SONAR_MAX_DISTANCE);
 
/* Led relay */
int relay = A5;
boolean led = false;


/* Receiver variables*/
const int channels = 4;                   // specify the number of receiver channels
float RC_in[channels];                    // an array to store the calibrated input from receiver

unsigned long now;
unsigned long rc_update;

void setup() {

  rMotor.run(RELEASE);
  lMotor.run(RELEASE);

  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH); 

  setup_pwmRead();


  Serial.begin(9600);
  delay(1000);
}

void loop() {

  now = millis();

  if (RC_avail() || now - rc_update > 18) { // frame rate FrSky X8R, 18 mS

    /* read PWM from receiver and decode */
    rc_update = now;

    //print_RCpwm();                        // to print raw PWM

    for (int i = 0; i < channels; i++) {
      int CH = i + 1;

      RC_in[i] = RC_decode(CH);             // decode, calibration, apply deadBand,  and apply failsafe
      //Serial.print(RC_in[i]);
      //Serial.print(" ");

    }
    //Serial.println();


    int rcThrottle = RC_in[0];
    int rcSteer   = RC_in[1];
    int rcMode    = RC_in[2];
    int rcLed     = RC_in[3];

    switchLed(rcLed);


    /* Mode Switching
     * rcMode PWM output: 1000, 1500 , 2000 
     */
     
    // failsafe (rc signal lost)
    if (rcMode == 1) { 
      mStop();
      resetAvoidance(); // to reset Avoidance Mode's variables 
    }
    
    // Manual Mode
    else if (rcMode < 1400) {
      manualMode(rcThrottle, rcSteer);
      resetAvoidance();  
    }
    
    // Object following
    else if (rcMode >= 1400 && rcMode < 1600) {
      followMode();
      resetAvoidance();  
    }
    
    // Obstacle avoidance
    else if (rcMode >= 1600) {
      avoidanceMode();
    }
  }
}

void switchLed(int rcLed){
    if (rcLed > 1500) {
      if(!led){
        digitalWrite(relay, LOW);
        led=true;        
      }

    } else {
      if(led){
        digitalWrite(relay, HIGH);
        led=false;
      }

    }  
}

void mStop() {
  rMotor.run(RELEASE);
  lMotor.run(RELEASE);
}

int readPing() { 

  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = SONAR_MAX_DISTANCE;
  }
  return cm;
}



 
