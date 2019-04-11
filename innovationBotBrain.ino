//
// innovationBotBrain v0.1
// by panGanerator 2019
//
// ------ LIBRARY INCLUDE --------

#include <Wire.h>
#include <Easing.h>
#include <VL53L0X.h>

// -------------------------------

// ----- CLASS INCLUDE --------

#include "Utils.h"
#include "Timeline.h"
#include "DCSequenceProvider.h"

#include "MotorController.h"
#include "SensorsController.h"
#include "LedController.h"
#include "BatteryController.h"
#include "ButtonController.h"
#include "BehaviourController.h"

// ----------------------------

// ------- DEFINE -------------



// ----------------------------


BotState botState = STANDBY;
BotType botType = GOLD_BOT;

MotorController motorController;
SensorsController sensorsController;
LedController ledController;
BatteryController batteryController;
ButtonController buttonController;
BehaviourController behaviourController;

void setup() {

  motorController.setup();
  sensorsController.setup();
  ledController.setup();
  batteryController.setup();
  buttonController.setup();
  behaviourController.setup( &motorController, &sensorsController );
  
  Serial.begin(9600);
 
}

void loop() {
   
  bool changedState = buttonController.update();
  if(changedState){
    toggleBotState();
  }
  
  if( botState == EXPLORE ){

    //motorController.moveArc(1000,150,FORWARD);

    behaviourController.update();
    sensorsController.update();
    motorController.update();

    
  } else { // STANDBY
    
    //...
    //Serial.println( "Standby" );
    
  }

  ledController.update();
  
}

void setBotState( BotState state ){
  
  if( state == STANDBY ){

    motorController.sleep();
    sensorsController.sleep();
    ledController.sleep();
    botState = STANDBY;
    Serial.println("STANDBY");
    
  }else if( state == EXPLORE ){

    motorController.wake();
    sensorsController.wake();
    ledController.wake();
    botState = EXPLORE;

    Serial.println("EXPLORE");

    behaviourController.setBehaviour( MOVING_FORWARD );
    
    //motorController.moveStraight(2000,250,FORWARD);
    //motorController.turn(2000,250,RIGHT);
    //motorController.moveArc(2000,250,BACKWARD,LEFT,0.8);
    
  }else{
    Serial.println( "UNKNOWN MODE!" );
  }
}

void toggleBotState() {

  setBotState( ( botState == EXPLORE ) ? STANDBY : EXPLORE );

}

//EOF.
