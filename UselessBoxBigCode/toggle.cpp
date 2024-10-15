#include "toggle.h"

states_t state; // global variable to store current state

void setToggleState(states_t _state){
  state = _state;
}

states_t getToggleState(){
  return state;
}