#include "display.h"

int id_homerGifStart = 10;
int id_homerGifEnd = 24;
int currentID = 10;
unsigned long displayChangeTimestamp;
unsigned long currentDisplayMillis;

displayStates_t displayState;

void setDisplayPicID(int _picID) {
  Serial1.print("p0.pic=");Serial1.print(_picID);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff); 
}

void setDisplayState(displayStates_t _state){
  displayState = _state;
}

void checkDisplayState(){
  switch(displayState){
    case NODISPLAYACTION:
      break;
    case DISPLAYSHOWING_HOMERGIF:
      playHomerGIF();
      break;
  }
}

void setDisplayChangeTimestamp(){
  displayChangeTimestamp = millis();
}

void playHomerGIF(){
  currentDisplayMillis = millis();
  if(currentID < 24){
    if((currentDisplayMillis - displayChangeTimestamp) > 100){
      setDisplayChangeTimestamp();
      //Serial.print(getCurrentActionStep());
      //Serial.print(" - ");
      //Serial.println(currentID);
      setDisplayPicID(currentID);
      currentID++; 
    }
  }
  if(currentID == 24) {
    //Serial.println(currentID);
    currentID = 10;
    //Serial.println(currentID);
    setFinishedPrevStep(true);
    setDisplayState(NODISPLAYACTION);
  }

}