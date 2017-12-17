#ifndef PION_HPP_
#define PION_HPP_

class Pion{
protected:
  int _x;
  int _y;
  int _owner;
public:
  Pion();
  Pion(int x, int y, int owner);
  
  const int getX() const;
  const int getY() const;
  const int getOwner() const;

};

#endif
