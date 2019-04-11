
#define FLOOR_SENSOR_1_VAL A5
#define FLOOR_SENSOR_2_VAL A4

#define FLOOR_SENSOR_1_PWR 19
#define FLOOR_SENSOR_2_PWR 18

#define XSHUT 21 // VL53L0X enable pin

class SensorsController {

    unsigned long lastUpdate = 0;
    int sensorUpdateInterval = 10;

    VL53L0X frontSensor;
    int frontSensorReadout = 0;
    boolean frontSensorTriggered = false;
    boolean prevFrontSensorState = false;
    int frontSensorTreshold = 70;

    int floorSensor1Val = 0;
    int floorSensor2Val = 0;
    boolean floorSensorTriggered = false;
    boolean prevFloorSensorState = false;
    int floorSensorTreshold = 200;
    

  public:

    void setup() {

      // FLOOR
      pinMode(FLOOR_SENSOR_1_PWR, OUTPUT);
      pinMode(FLOOR_SENSOR_2_PWR, OUTPUT);
      setFloorSensorsPwr( HIGH );

      // FRONT
      pinMode(XSHUT, INPUT);
      Wire.begin();
      frontSensor.init();
      frontSensor.setTimeout(500);
      frontSensor.startContinuous();

    }

    void update() {

      unsigned long currentTime = millis();

      if (currentTime - lastUpdate > sensorUpdateInterval) {

        checkFrontSensor();
        checkFloorSensor();

//            Serial.print("FLOOR1: ");
//            Serial.println(floorSensor1Val);
//        
//            Serial.print("FLOOR2: ");
//            Serial.println(floorSensor2Val);
//        
//            Serial.print("FRONT: ");
//            Serial.println(frontSensorReadout);

        lastUpdate = currentTime;

      }

    }

    void checkFloorSensor(){

      floorSensor1Val = analogRead(FLOOR_SENSOR_1_VAL);
      floorSensor2Val = analogRead(FLOOR_SENSOR_2_VAL);
      
      boolean floorSensror1State = ( floorSensor1Val > floorSensorTreshold );
      boolean floorSensror2State = ( floorSensor2Val > floorSensorTreshold );

      boolean combinedFloorSensorState = floorSensror1State || floorSensror2State;

      if (combinedFloorSensorState != prevFloorSensorState) {

        prevFloorSensorState = combinedFloorSensorState;

        if ( combinedFloorSensorState ) {
          floorSensorTriggered = true;
        }

      } else {
        floorSensorTriggered = false;
      }
      
    }

    void checkFrontSensor() {
      
      frontSensorReadout = frontSensor.readRangeContinuousMillimeters();

      boolean frontSensorState = ( frontSensorReadout < frontSensorTreshold  );

      if (frontSensorState != prevFrontSensorState) {

        prevFrontSensorState = frontSensorState;

        if ( frontSensorState ) {
          frontSensorTriggered = true;
        }

      } else {
        frontSensorTriggered = false;
      }
      
    }

    void setFloorSensorsPwr( int pwr ) {

      digitalWrite(FLOOR_SENSOR_1_PWR, pwr);
      digitalWrite(FLOOR_SENSOR_2_PWR, pwr);

    }

    void sleep() {
      setFloorSensorsPwr( LOW );
      frontSensor.stopContinuous();
      pinMode(XSHUT, OUTPUT);
    }

    void wake() {
      setFloorSensorsPwr( HIGH );
      pinMode(XSHUT, INPUT);
      frontSensor.init();
      frontSensor.startContinuous();
    }

    bool isFrontSensorTriggered() {
      return frontSensorTriggered;
    }

    int getFrontSensorValue(){
      return frontSensorReadout;
    }

    bool isFloorSensorTriggered(){
      return floorSensorTriggered;
    }

    int getFloorSensor1Value(){
      return floorSensor1Val;
    }

    int getFloorSensor2Value(){
      return floorSensor2Val;
    }

};

