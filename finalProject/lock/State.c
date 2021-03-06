/*
 * State.c
 *
 *  Created on: Dec 2, 2017
 *      Author: amabo
 */
#include "State.h"
#include "RGB.h"
#include "BeamBreaks.h"
#include "Buzzer.h"

extern State lockState;
extern uint8_t timedOut;
extern uint8_t checkBeamBreak;
extern uint8_t RGBCount;

//This function configures Timer A3
void configure_UnlockableTimer(){

}

/*When transitioning between states we need to make sure the proper functions are
 * enabled and disabled.  For that reason check which state we are leaving and
 */
void enterState(State newState){
    //Turn off the LEDs
    LED_Off();
    timedOut = 0;
    checkBeamBreak = 0;
    RGBCount = 0;

    //Turn off the current state's features
    if(lockState == Error){

    }
    else if(lockState == Locked){
        //Once we leave the locked state, we expect the beam to be broken, so disable its interrupts
        disable_BeamBreaks();
    }
    else if(lockState == Unlockable){

    }
    else if(lockState == Unlocked){

    }

    //Turn on the new State's features
    if(newState == Error){
        //SEND ERROR MESSAGE

        //State Transition
        lockState = Error;
    }
    else if(newState == Locked){
        //If we are in the lock state, breaking the beams unexpectedly is a major issue. This lets us set an interrupt to enter this state
        enable_BeamBreaks();
        Red_LED_On();
        long_buzz();

        //State Transition
        lockState = Locked;
    }
    else if(newState == Unlockable){
        //We will start the solenoid Timer A1 to force this

        Blue_LED_On();
        long_buzz();

        //State Transition
        lockState = Unlockable;
    }
    else if(newState == Unlocked){

        //State Transition
        lockState = Unlocked;
    }

}
