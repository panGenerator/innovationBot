

class BehaviourController {
  
  public:

  BotBehaviour previousBehaviour = NULL;
  BotBehaviour currentBehaviour = WAITING;

  MotorController* motorController;
  SensorsController* sensorsController;
  
  void setup( MotorController* _motorCtrl, SensorsController* _sensorsCtrl ){
    motorController = _motorCtrl;
    sensorsController = _sensorsCtrl;
  }

  void setBehaviour( BotBehaviour newBehaviour ){

    currentBehaviour = newBehaviour;

    switch( newBehaviour ){

      case WAITING:
        Serial.println("WAITING");
      break;

      case MOVING_FORWARD:
        Serial.println("MOVING_FORWARD");
        motorController->moveStraight( random( 1000, 3000 ) , random( 100, 250 ), FORWARD );
      break;

      case RETREAT:
        Serial.println("RETREAT");
        motorController->moveStraight( random( 1000, 1500 ) , random( 150 ), BACKWARD );
      break;

      case LOOKING_AROUND:
        Serial.println("LOOKING_AROUND");
        motorController->turn( random( 500, 1000 ), 150 , ( random(0,10) > 5 ) ? LEFT : RIGHT );
      break;
      
    }

    previousBehaviour = currentBehaviour;
    
  }

  void update(){

    if( sensorsController->isFrontSensorTriggered() ){
      
      Serial.println( "FRONT SENSOR TRIGGERED!" );
      Serial.println( sensorsController->getFrontSensorValue() );
      
      if( currentBehaviour != RETREAT && currentBehaviour != LOOKING_AROUND ){
        setBehaviour( RETREAT );
      }
      
    }

    if( sensorsController->isFloorSensorTriggered() ){
      Serial.println( "FLOOR SENSOR TRIGGERED!" );
      setBehaviour( RETREAT );
    }

    if( motorController->isMoveFinished() ){
      
      if( currentBehaviour == MOVING_FORWARD || currentBehaviour == RETREAT ){
        
        setBehaviour( LOOKING_AROUND );
        
      }else if( currentBehaviour == LOOKING_AROUND ){
        
        setBehaviour( MOVING_FORWARD );
        
      }
      
      
    }
    
  }

};
