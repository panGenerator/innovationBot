#define BUTT 16
#define ACTIVE_STATE 0 // 0 - press, 1 - release

class ButtonController {
  public:
  
  int lastState = 1;
  unsigned long lastUpdate = 0;
  
  void setup(){
    pinMode(BUTT, INPUT_PULLUP);
  }
  
  bool update() {
    if(millis() - lastUpdate > 10){
      int state = digitalRead(BUTT);
      if(state != lastState){
        lastState = state;
        lastUpdate = millis();
        if(state == ACTIVE_STATE) {
          return true;
        }
        else {
          return false;
        }
      }
      else {
        return false;
      }
    } else {
      return false;
    }
  }
  
};
