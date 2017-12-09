#include "Plateau.hpp"

Plateau::Plateau(){
  _player = 2;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      plateau[i][j] = Pion(i,j,0);
    }
  }
}
  
void Plateau::poserPion(Pion p){
  plateau[p.getX()][p.getY()] = p;
}

int Plateau::getActualPlayer() const{
  return _player;
}

void Plateau::switchPlayer(){
  if(getActualPlayer() == 1){
    _player = 2;
  }
  else{
    _player = 1;
  }
}

bool Plateau::checkLegalMove(int x, int y) const{
  if(x > 3 || x < 1 || y > 3 || y < 1){
    return false;
  }
  else{
    if(plateau[x-1][y-1].getOwner() != 0){
      return false;
    }
  }
  return true;
}

void Plateau::display() const{
  for(unsigned int x = 0; x < 4; x++){
    cout << "-------------------------------------------------" << endl;
  }
  cout << "-----------ETAT DU PLATEAU-----------" << endl;
  for(unsigned int x = 0; x < 2; x++){
    cout << "-----------------------------------------" << endl;
  }
  for(unsigned int i = 0;i < 3; i++){
    for(unsigned int j = 0; j < 3; j++){
      switch (plateau[i][j].getOwner()){
      case 1 :
	cout << "X ";
	break;
      case 2 :
	cout << "O ";
	break;
      default:
	cout << ". ";
	break;
      }
    }
    cout << endl;
  }
}

bool Plateau::checkVictory() const{
  for(unsigned int i = 0; i < 3; i++){
    if (checkLine(i) || checkColumn(i))
      return true;
  }
  if(checkDiagonal()){
    return true;
  }
  return false;
}

bool Plateau::checkLine(int i) const{
  return plateau[i][0].getOwner() == plateau[i][1].getOwner()
    && plateau[i][0].getOwner() == plateau[i][2].getOwner()
    && plateau[i][0].getOwner() != 0;
}

bool Plateau::checkColumn(int i) const{
  return plateau[0][i].getOwner() == plateau[1][i].getOwner()
    && plateau[0][i].getOwner() == plateau[2][i].getOwner()
    && plateau[0][i].getOwner() != 0;
}

bool Plateau::checkDiagonal() const{
  if(plateau[0][0].getOwner() == plateau[1][1].getOwner()
     && plateau[0][0].getOwner() == plateau[2][2].getOwner()
     && plateau[1][1].getOwner() != 0){
    return true;
  }
  if(plateau[0][2].getOwner() == plateau[1][1].getOwner()
     && plateau[0][2].getOwner() == plateau[2][0].getOwner()
     && plateau[1][1].getOwner() != 0){
    return true;
  }
  return false;
}
