
#define PWMA 5 //Speed control
#define AIN1 20 //Direction
#define AIN2 6 //Direction

#define PWMB 10 //Speed control
#define BIN1 15 //Direction
#define BIN2 12 //Direction

#define STBY 14 // Standby pin

class MotorController {

    int motorSpeed[2] = {0, 0};
    float speedRatio[2] = {1.0, 1.0};
    MotionDirType motorDir[2] = {FORWARD, FORWARD};

    DCSequenceProvider dcSequenceProvider;
    Timeline dcTimeline;
    boolean moveFinished = false;

    unsigned long motionDuration = 0;


    // ----------------------------------------------

  public:

    void setup() {

      pinMode(PWMA, OUTPUT);
      pinMode(AIN1, OUTPUT);
      pinMode(AIN2, OUTPUT);

      pinMode(PWMB, OUTPUT);
      pinMode(BIN1, OUTPUT);
      pinMode(BIN2, OUTPUT);

      pinMode(STBY, OUTPUT);

    }

    void moveStraight( int duration, int speed, MotionDirType dir ) {

      speedRatio[0] = speedRatio[1] = 1.0;
      motorDir[0] = motorDir[1] = dir;
      startMove( duration, speed );

    }

    void turn( int duration, int speed, MotionDirType dir ) {

      if ( dir == LEFT ) {

        motorDir[0] = FORWARD;
        motorDir[1] = BACKWARD;

      } else if ( dir == RIGHT ) {

        motorDir[0] = BACKWARD;
        motorDir[1] = FORWARD;

      }

      speedRatio[0] = speedRatio[1] = 1.0;
      startMove( duration, speed );

    }

    void moveArc( int duration, int speed, MotionDirType dir, MotionDirType turnDir, float ratio ) {

      if ( turnDir == LEFT ) {

        speedRatio[0] = ratio;
        speedRatio[1] = 1.0;

      } else if ( turnDir == RIGHT ) {

        speedRatio[0] = 1.0;
        speedRatio[1] = ratio;

      }

      
      motorDir[0] = motorDir[1] = dir;
      startMove( duration, speed );

    }

    void startMove( int duration, int speed ){

      dcSequenceProvider.generateSequence( SQUARE, duration, speed );
      dcTimeline.play( dcSequenceProvider.keyframeBuffer, dcSequenceProvider.keyframeCount );
      
    }

    void brake() {

    }


    void move(int motor, int speed, MotionDirType dir) {

      boolean inPin1 = LOW;
      boolean inPin2 = HIGH;

      if (dir == FORWARD ) {
        inPin1 = HIGH;
        inPin2 = LOW;
      }

      if (motor == 1) {
        digitalWrite(AIN1, inPin1);
        digitalWrite(AIN2, inPin2);
        analogWrite(PWMA, speed);
      } else {
        digitalWrite(BIN1, inPin1);
        digitalWrite(BIN2, inPin2);
        analogWrite(PWMB, speed);
      }

    }

    void update() {

      dcTimeline.update();
      int currentSpeed = int(dcTimeline.getCurrentValue());

      move( 0, currentSpeed * speedRatio[0], motorDir[0] );
      move( 1, currentSpeed * speedRatio[1], motorDir[1] );

      moveFinished = dcTimeline.isFinished();
      
      if( dcTimeline.isFinished() ){
        Serial.println( "MOVE FINISHED" );
      }

    }

    void reset(){
      dcTimeline.reset();
    }


    void sleep() {
      reset();
      digitalWrite(STBY, LOW);
    }

    void wake() {
      digitalWrite(STBY, HIGH);
    }

    bool isMoveFinished(){
      return moveFinished;
    }

};

