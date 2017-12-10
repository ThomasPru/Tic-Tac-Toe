#ifndef PLATEAU_HPP_
#define PLATEAU_HPP_

#include "Pion.hpp"
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Plateau{
private:
  Pion grille[3][3];
  int _player;
  bool _isFull;
public:
  Plateau();
  
  void poserPion(Pion p);

  void switchPlayer();
  int getActualPlayer() const;

  void display() const;

  bool checkBoardFull();
  bool checkLegalMove(int x, int y) const;
  bool checkVictory() const;
  bool checkLine(int i) const;
  bool checkColumn(int i) const;
  bool checkDiagonal() const;
};

#endif
