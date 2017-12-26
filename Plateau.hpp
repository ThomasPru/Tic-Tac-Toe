#ifndef PLATEAU_HPP_
#define PLATEAU_HPP_

#include "Pion.hpp"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

class Plateau{
public:
  int grille[3][3];
  int _player;
  int _pastTrapIA;
public:
  Plateau();
  
  void poserPion(Pion p);
  void retirerPion(Pion p);

  void switchPlayer();
  int getActualPlayer() const;

  void display() const;

  bool checkBoardFull();
  bool checkLegalMove(int x, int y) const;
  int checkVictory() const;
  int checkLine(int i) const;
  int checkColumn(int i) const;
  int checkDiagonal() const;

  vector<Pion > getCoupPossible();

 
  int countLine(int player, int i);
  int countColonne(int player, int i);
  int countDiagoDesc(int player);
  int countDiagoAsc(int player);
  bool verifTrap();
};
#endif
