#include "Pion.hpp"

Pion::Pion(){
}

Pion::Pion(int x, int y, int owner){
  _x = x;
  _y = y;
  _owner = owner;
}

const int Pion::getX() const{
  return _x;
}

const int Pion::getY() const{
  return _y;
}

const int Pion::getOwner() const{
  return _owner;
}

int Pion::setOwner(int newOwner){
  _owner = newOwner;
}
