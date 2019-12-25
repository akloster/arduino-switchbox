// boardtype: Arduino/Genuino Micro 
// Tested on Arduino Pro Micro clones.

#include <Keyboard.h>
#include "SoftPWM.h"

// use this option for OSX:
//char ctrlKey = KEY_LEFT_GUI;
// use this option for Windows and Linux:
char ctrlKey = KEY_LEFT_CTRL;
const int ledOnLevel = 50;

class Switches{
    public:
      
      int pinNumbers[4];    // pins to read from
      int bankPins[2];      // which pins to pull low for selecting one row
      int states[4];        // states in -1,0,1 with 0 being neutral
      bool triggered;       // event triggered
      int triggeredSwitch; // which switch
      int triggeredState;   // which state
      Switches (int _pinNumbers[4], int _bankPins[2]){
          for (int i=0; i<4; i++){
            pinNumbers[i] = _pinNumbers[i];
            states[i] = 0;
            pinMode(pinNumbers[i], INPUT_PULLUP);
          };
          for (int j=0; j<2; j++){
              int pin = _bankPins[j];
              bankPins[j] = pin;
              pinMode(pin, OUTPUT);
              digitalWrite(pin, HIGH);
          };
          triggered=false;
      }
        // read one bank
      void update(){
        int state[4];
        for (int i=0; i<4; i++){
                state[i] = 0;
        }
        for (int bank=0; bank<2; bank++){
            digitalWrite(bankPins[bank], LOW);
            delay(10);
            for (int i=0; i<4; i++){
                int c = digitalRead(pinNumbers[i]);
                // Serial.print(c);
                if ((bank==0) &&(c==LOW)) {
                    state[i] = -1;
                }
                if ((bank==1) &&(c==LOW)) {
                    state[i] = 1;
                }
            }
            digitalWrite(bankPins[bank], HIGH);
        }
        //Serial.println();

        for (int i=0; i<4; i++){
            if (state[i] != this->states[i]){
                Serial.print("Switch ");
                Serial.print(i);
                Serial.print(" ");
                Serial.println(state[i]);
                triggered = true;
                triggeredSwitch = i;
                triggeredState = state[i];
                this->states[i]=state[i];
                return;
            }
        }
        digitalWrite(bankPins[0], HIGH);
        digitalWrite(bankPins[1], HIGH);
      }
      
};
const int pins[]={7,6,5,4};
const int banks[]={2,3};
const int ledPins[]={15,14,16,10};
Switches switches(pins, banks);
void setup(){
    SoftPWMBegin();
    Serial.begin(115200);
    Serial.println("Starting up");
    for (int i=0; i<4; i++){
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
        SoftPWMSet(ledPins[i], 0);
        SoftPWMSetFadeTime(ledPins[i], 250, 500);
    };
    Keyboard.begin();
};
void loop(){
    switches.update();
    if (switches.triggered){
        int number = switches.triggeredSwitch;
        int state = switches.triggeredState;
        switches.triggered = false;
        switch (number){
            case 0:
                if (state!=0) SoftPWMSet(ledPins[0], ledOnLevel);
                if (state==1){
                    Keyboard.print("Frohe ");
                } else if (state==-1) {
                }
                break;
            case 1:
                if (state!=0) SoftPWMSet(ledPins[1], ledOnLevel);
                if (state==1){
                    Keyboard.print("Weihnachten!");
                } else if (state==-1) {
                }
                break;
            case 2:
                if (state!=0) SoftPWMSet(ledPins[2], ledOnLevel);
                if (state==1){
                    Keyboard.press(ctrlKey);
                    Keyboard.press("a");
                    Keyboard.releaseAll();
                } else if (state==-1) {
                }
                break;
            case 3:
                if (state!=0) SoftPWMSet(ledPins[3], ledOnLevel);
                break;
        }
    }
    for (int i=0; i<4; i++){
        if (switches.states[i]==0) SoftPWMSet(ledPins[i], 0);
    }
};