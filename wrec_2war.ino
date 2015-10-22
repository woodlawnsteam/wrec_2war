
/* 
 *  
 *  Software for WREC 2-Wheel Automomous Robot
 *  
 */

#define SERIAL_DEBUG

// constants

// operating modes
#define modeStartup             0
#define modeSelection            1
#define modeObstacleAvoidance   2
#define modeLineFollower        3
#define modeMazeWalled          4
#define modeMazeLined           5 
#define modeCompassGoal         6
#define modeDemo                7
#define modeUser1               8

// encoders
#define ENCODER_RIGHT           2
#define ENCODER_LEFT            3

#define abs(X) ((X < 0) ? -1 * X : X)

// obstacle sensors
#define OS_LEFT_LEFT            4
#define OS_LEFT                 5
#define OS_RIGHT                6
#define OS_RIGHT_RIGHT          11

// motor control pins
#define motorLeftDir 7
#define motorLeftPWM 9
#define motorRightDir 8
#define motorRightPWM 10
#define motorForward LOW
#define motorReverse HIGH

// default speed
const int baseSpeed = 100;

// global variables
int mode = modeStartup;

unsigned long startTime;

int led = 13;
unsigned long ledStartTime= 0;
int ledCount = 0;
int ledStatus = 0;

// encoder variables
int encoderRightCount = 0;
int encoderLeftCount = 0;

// motor variables
int leftPower = 0;
int rightPower = 0;

void setup() {

   // save start time for future reference
   startTime = millis();

   // initilize serial port
   #ifdef SERIAL_DEBUG
   Serial.begin(9600);
   #endif
   
   // initialze onboard LED
   ledSetup(led);

  // setup wheel encoders
  encoderSetup();

  // setup motors
  motorSetup(motorLeftDir,motorLeftPWM,motorRightDir,motorRightPWM);

}

void loop() {

  // global loop actions

  #ifdef SERIAL_DEBUG
  Serial.print("Encoders: ");
  Serial.print(encoderLeftCount);
  Serial.print(" : ");
  Serial.println(encoderRightCount);
  #endif


  // mode specific loop actions
  
  if (mode == modeStartup) {
    doStartupMode();
  } else if (mode == modeSelection) {
    doSelectionMode();
  } else if (mode == modeObstacleAvoidance) {

  } else if (mode == modeLineFollower) {

  } else if (mode == modeMazeWalled) {

  } else if (mode == modeMazeLined) {

  } else if (mode == modeCompassGoal) {

  } else if (mode == modeDemo) {
    doDemoMode();
  } else if (mode == modeUser1) {
    doUser1Mode();
  };



}

// user mode 1
int doUser1Mode() {
  #ifdef SERIAL_DEBUG
  Serial.println("MODE: user 1");
  #endif

  
}

// demo mode
int doDemoMode() {
  #ifdef SERIAL_DEBUG
  Serial.println("MODE: demo");
  #endif


  goForward(baseSpeed);



}


// selection mode
int doSelectionMode() {
  #ifdef SERIAL_DEBUG
  Serial.println("MODE: selection");
  #endif

  int selval = 0;
  if (ledSignal(3,500,500)) {
    selval = checkAllObstacleSensors();
    if (selval ==  0) {
      // default mode
      mode = modeDemo;
      
    } else if (selval == 1) {
      // demo
      mode = modeDemo;
      
    } else if (selval == 2) {
      // user
      mode = modeUser1;
      
    } else if (selval == 3) {
      // walled maze
      mode = modeMazeWalled;
      
    } else if (selval == 4) {
      // obstacle avoidance
      mode = modeObstacleAvoidance;
      
    } else if (selval == 6) {
      // compass goal
      
    } else if (selval == 8) {
      // line follower
      mode = modeLineFollower;
      
    } else if (selval == 12) {
      // lined maze
      mode = modeMazeLined;
      
    } else {
      // default mode
      mode = modeDemo;
    }
  };

  
}

// startup mode
int doStartupMode() {
  #ifdef SERIAL_DEBUG
  Serial.println("MODE: startup");
  #endif

  if (ledSignal(3,500,500)) {
    
    if (checkObstacleSensor(OS_LEFT_LEFT)) {
      #ifdef SERIAL_DEBUG
      Serial.println("going to selection");
      #endif

      mode = modeSelection;
    } else {
      #ifdef SERIAL_DEBUG
      Serial.println("going to demo");
      #endif

      mode = modeDemo;
    };
  };
  
}

int motorSetup(int leftDir,int leftPWM,int rightDir,int rightPWM) {
    pinMode(leftDir, OUTPUT);
    pinMode(leftPWM, OUTPUT);
    pinMode(rightDir, OUTPUT);
    pinMode(rightPWM, OUTPUT);
    goStop();
}

int goForward(int speed) {

  digitalWrite(motorLeftDir, motorForward);
  digitalWrite(motorRightDir, motorForward);
  analogWrite(motorLeftPWM, speed);
  analogWrite(motorRightPWM, speed);
}

int goBackwards(int speed) {

  digitalWrite(motorLeftDir, motorReverse);
  digitalWrite(motorRightDir, motorReverse);
  analogWrite(motorLeftPWM, speed);
  analogWrite(motorRightPWM, speed);
}

int goRotateLeft(int speed) {
  digitalWrite(motorLeftDir, motorReverse);
  digitalWrite(motorRightDir, motorForward);
  analogWrite(motorLeftPWM, speed);
  analogWrite(motorRightPWM, speed);
}

int goRotateRight(int speed) {
  digitalWrite(motorLeftDir, motorForward);
  digitalWrite(motorRightDir, motorReverse);
  analogWrite(motorLeftPWM, speed);
  analogWrite(motorRightPWM, speed);
}
int goStop() {
  analogWrite(motorLeftPWM, 0);
  analogWrite(motorRightPWM, 0);
  
}

// encoder functions
int encoderSetup() {
  attachInterrupt (0, encoderRightCounter, CHANGE);
  attachInterrupt (1, encoderLeftCounter, CHANGE);
}

void encoderRightCounter () {
  encoderRightCount++;
}

void encoderLeftCounter () {
  encoderLeftCount++;
}

// OA IR functions
int oaSetupAll() {
  oaSetup(OS_LEFT_LEFT);
  oaSetup(OS_LEFT);
  oaSetup(OS_RIGHT);
  oaSetup(OS_RIGHT_RIGHT);
}

int oaSetup(int pin) {
  pinMode(pin,INPUT);
}

int oaGet(int pin) {
  return digitalRead(pin);
}


// led functions
int ledSetup(int pin) {
  pinMode (pin, OUTPUT);
  ledOff(pin);
}

int ledOn(int pin) {
  digitalWrite (pin, HIGH);
  ledStatus = HIGH;
}

int ledOff(int pin) {
  digitalWrite (pin, LOW);
  ledStatus = LOW;
}

int ledSet(int pin, int value) {
  digitalWrite (pin, value);
  ledStatus = value;
}

int ledSignal(int count, unsigned long onDuration, unsigned long offDuration ) {
  int nowTime;
  if (ledCount < count) {
    nowTime = millis();
    if (ledStartTime == 0) {
        ledStartTime = nowTime;
    } else {
    if (ledStatus && ((nowTime - ledStartTime) > onDuration)) {
      ledSet(led,LOW);
      ledStartTime = nowTime;
    } else if (!ledStatus && ((nowTime - ledStartTime) > offDuration)) {
      ledSet(led,HIGH);
      ledStartTime = nowTime;
      ledCount++;
    };
    };
    return false;
    
  };  
  return true;
}

int checkObstacleSensor(int pin) {
  #ifdef SERIAL_DEBUG
  Serial.println(oaGet(pin));
  #endif

  if (oaGet(pin) == LOW) {
    return true;
  }
  return false;
  
}

int checkAllObstacleSensors() {
  int val = 0;
  if (checkObstacleSensor(OS_LEFT_LEFT)) {
    val =+ 1;
  };

  if (checkObstacleSensor(OS_LEFT)) {
    val =+ 2;
  };
  
  if (checkObstacleSensor(OS_RIGHT)) {
    val =+ 4;
  };

  if (checkObstacleSensor(OS_RIGHT_RIGHT)) {
    val =+ 8;
  };
  return val;
}

