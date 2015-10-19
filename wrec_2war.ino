
/* 
 *  
 *  Software for WREC 2-Wheel Automomous Robot
 *  
 */

#define modeStartup             0
#define modeSelection            1
#define modeObstacleAvoidance   2
#define modeLineFollower        3
#define modeMazeWalled          4
#define modeMazeLined           5 
#define modeCompassGoal         6
#define modeDemo                7
#define modeUser1               8

#define OS_LEFT_LEFT            0
#define OS_LEFT                 1
#define OS_RIGHT                2
#define OS_RIGHT_RIGHT          3

int mode = modeStartup;

unsigned long startTime;
unsigned long ledStartTime;
int ledCount = 0;
int ledStatus = HIGH;

void setup() {

   startTime = millis();
   
   # setup hardware


}

void loop() {

  // global loop actions


  // mode specific loop actions
  
  if (mode == modeStartup) {

  } else if (mode == modeSelection) {

  } else if (mode == modeObstacleAvoidance) {

  } else if (mode == modeLineFollower) {

  } else if (mode == modeMazeWalled) {

  } else if (mode == modeMazeLined) {

  } else if (mode == modeCompassGoal) {

  } else if (mode == modeDemo) {
    
  } else if (mode == modeUser1) {
  
  };



}



// startup mode
int doStartupMode() {

  if (!ledSignal(3,1000)) }
    if (checkObstacleSensor(OS_LEFT_LEFT)) {
      mode = modeSelection;
    } else {
      mode = modeObstacleAvoidance;
    };
  };
  
}

int ledSignal(int count, int duration) {

  int nowTime = millis();
  if (nowTime - startTime) > duration {
    if (ledStatus == HIGH) {
       ledStatus = LOW;
    } else {
       ledStatus = HIGH;
    }
    ledCount++;
  };
  if (ledCount > count) {
    return false;
  };
  return true;
}

int checkObstacleSensor(int pin) {


}


