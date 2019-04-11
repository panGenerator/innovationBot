


class DCSequenceProvider {

  public:
  // ----------------------------------

  Keyframe keyframeBuffer[3];
  int keyframeCount = 3;
  int accelDuration = 1000;
  int deaccelDuration = 1000;

  void setup( unsigned long _kickstartDuration, float _kickstartValue ){
   
  }

  void setup( unsigned long _kickstartDuration, float _kickstartValue, float _kickstartSustainDuration, float _endDuration  ){
   
  }

  void generateSequence( ADSRType type, unsigned long duration, float value ) {

    switch ( type ) {

      case TRIANGLE_FALL:
        //generateTriangleFallSequence( duration, value );
        //generateSquareSequence( duration, value );
        break;

      case TRIANGLE_RISE:
        //generateTriangleRiseSequence( duration, value );
        //generateSquareSequence( duration, value );
        break;

      case SQUARE:
        generateSquareSequence( duration, value );
        break;

      case SQUARE_2:
        //generateSquare2Sequence( duration, value );
        break;

      case CIRCLE:
        //generateCircleSequence( duration, value );
        //generateSquareSequence( duration, value );
        break;

    }

  }


  void generateSquareSequence( unsigned long duration, float value ){
    
    keyframeBuffer[ 0 ] = { value, accelDuration, Easing::easeInCubic };
    keyframeBuffer[ 1 ] = { value, duration, Easing::linearTween }; 
    keyframeBuffer[ 2 ] = { 0.0, deaccelDuration, Easing::easeOutCubic };

    keyframeCount = 3;
    
  }

  
};

