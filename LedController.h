
#define MAIN_LED 11
#define STATUS_LED 13

class LedController {

  public:
  float spd = 100.0;
  void setup(){
    
    pinMode(MAIN_LED, OUTPUT);
    pinMode(STATUS_LED, OUTPUT);
    
  }

  void update(){

    analogWrite(MAIN_LED, 255 * (sin(millis() / (spd*4.0)) + 1.0) / 2.0);
    analogWrite(STATUS_LED, 255 * (sin(millis() / spd) + 1.0) / 2.0);
    
  }
  
  void sleep() {
    spd = 100.0;
  }
  
  void wake() {
    spd = 25.0;
  }
  
};

