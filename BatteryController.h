#define VBATPIN A9

class BatteryController {
  public:
  
  void setup(){
    // NOTHING TO DO... MOVE ALONG...
  }
  
  float getBatteryVoltage() {
    float measuredvbat = analogRead(VBATPIN);
    measuredvbat *= 2;
    measuredvbat *= 3.3;
    measuredvbat /= 1024;
    return measuredvbat;
  }

};
