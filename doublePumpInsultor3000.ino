#include <Keyboard.h>

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int button2Pin = 4;     // the number of the pushbutton pin

const int ledPin =  13;      // the number of the LED pin


//timing
unsigned long lastSwitchMillis = 0;



// variables will change
bool buttonState1 = false;
bool buttonState2 = false;
bool switchToFirstWeapon = true;
bool didOutputKey = false;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  Keyboard.begin();

}

void loop() {

  buttonState1 = digitalRead(2) == HIGH;
  buttonState2 = digitalRead(4) == HIGH;

  //reset vars after key release
  if(!buttonState1 && !buttonState2 && didOutputKey){
    didOutputKey = false;
    digitalWrite(ledPin, LOW);
    delay(50);
  }


  //reset switch counter after 5s
  if(millis() - lastSwitchMillis > 5000){
    switchToFirstWeapon = true;
  }

  

  //quit if already printed character
  if(didOutputKey && (buttonState1 || buttonState2)){
    return;
  }

  if(buttonState1){
    didOutputKey = true;
    digitalWrite(ledPin, HIGH);
    if(switchToFirstWeapon){
      Keyboard.press('k');
      switchToFirstWeapon = false;
    }else{
      Keyboard.press('l');
      switchToFirstWeapon = true;
    }
    delay(100);
    Keyboard.releaseAll();
    //store millis of last keypress
    
    lastSwitchMillis = millis();
  }

  if(buttonState2){
    digitalWrite(ledPin, HIGH);
    didOutputKey = true;
    Serial.println(0);
  }


}