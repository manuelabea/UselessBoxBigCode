#include "display.h"

void setDisplayPicID(int _picID) {
  Serial1.print("p0.pic=");Serial1.print(_picID);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff); 
}