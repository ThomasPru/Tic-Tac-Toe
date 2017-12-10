#include "Plateau.hpp"

Plateau::Plateau(){
  _player = 2;
  _isFull = false;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      grille[i][j] = Pion(i,j,0);
    }
  }
}

bool Plateau::checkBoardFull(){
  _isFull = true;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(grille[i][j].getOwner() == 0){
	_isFull = false;
      }
    }
  }
  return _isFull;
}

void Plateau::poserPion(Pion p){
  grille[p.getX()][p.getY()] = p;
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
  return !(grille[x-1][y-1].getOwner() != 0 ||
	   x > 3 || x < 1 || y > 3 || y < 1);
}

void Plateau::display() const{
  for(int x = 0; x < 4; x++){
    cout << "-------------------------------------------------" << endl;
  }
  cout << "-----------ETAT DU PLATEAU-----------" << endl;
  for(int x = 0; x < 2; x++){
    cout << "-----------------------------------------" << endl;
  }
  for(int i = 0;i < 3; i++){
    for(int j = 0; j < 3; j++){
      switch (grille[i][j].getOwner()){
      case 1 :
	cout << "X   ";
	break;
      case 2 :
	cout << "O   ";
	break;
      default:
	cout << ".   ";
	break;
      }
    }
    cout << endl << endl;
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
  return grille[i][0].getOwner() == grille[i][1].getOwner()
    && grille[i][0].getOwner() == grille[i][2].getOwner()
    && grille[i][0].getOwner() != 0;
}

bool Plateau::checkColumn(int i) const{
  return grille[0][i].getOwner() == grille[1][i].getOwner()
    && grille[0][i].getOwner() == grille[2][i].getOwner()
    && grille[0][i].getOwner() != 0;
}

bool Plateau::checkDiagonal() const{
  if(grille[0][0].getOwner() == grille[1][1].getOwner()
     && grille[0][0].getOwner() == grille[2][2].getOwner()
     && grille[1][1].getOwner() != 0){
    return true;
  }
  if(grille[0][2].getOwner() == grille[1][1].getOwner()
     && grille[0][2].getOwner() == grille[2][0].getOwner()
     && grille[1][1].getOwner() != 0){
    return true;
  }
  return false;
}
