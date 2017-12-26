#include "Plateau.hpp"

Plateau::Plateau(){
  _player = rand()%2 + 1;
  _pastTrapIA = false;
  cout << "------------JOUEUR " << _player%2 +1 << " COMMENCE ! " << endl;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      grille[i][j] = 0;
    }
  }
}

bool Plateau::checkBoardFull(){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(grille[i][j] == 0){
	return false;
      }
    }
  }
  return true;
}

void Plateau::poserPion(Pion p){
  grille[p.getX()][p.getY()] = p.getOwner();
  if(getCoupPossible().size() <= 4){
    _pastTrapIA = true;
  }
  else{
    _pastTrapIA = false;
  }
}

void Plateau::retirerPion(Pion p){
  grille[p.getX()][p.getY()] = 0;
  if(getCoupPossible().size() <= 4){
    _pastTrapIA = true;
  }
  else{
    _pastTrapIA = false;
  }
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
  return !(grille[x-1][y-1] != 0 ||
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
      switch (grille[i][j]){
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



int Plateau::checkVictory() const{
  int gagnant = 0;
  for(unsigned int i = 0; i < 3; i++){
    if(gagnant == 0){
      gagnant = checkLine(i);
    }
    if(gagnant == 0){
      gagnant = checkColumn(i);
    }
  }
  if(gagnant == 0){
    gagnant = checkDiagonal();
  }
  return gagnant;
}

int Plateau::checkLine(int i) const{
  if( grille[i][0] == grille[i][1]
    && grille[i][0] == grille[i][2]){
    return grille[i][0];
  }
  return 0;
}

int Plateau::checkColumn(int i) const{
  if( grille[0][i] == grille[1][i]
      && grille[0][i] == grille[2][i]){
    return grille[0][i];
  }
  return 0;
}

int Plateau::checkDiagonal() const{
  if(grille[0][0] == grille[1][1]
     && grille[0][0] == grille[2][2]
     && grille[1][1] != 0){
    return grille[1][1];
  }
  if(grille[0][2] == grille[1][1]
     && grille[0][2] == grille[2][0]
     && grille[1][1] != 0){
    return grille[1][1];
  }
  return 0;
}

vector<Pion> Plateau::getCoupPossible(){
  vector<Pion> CoupPossible;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(grille[i][j] == 0){
	Pion pi(i,j,getActualPlayer());
	CoupPossible.push_back(pi);
      }
    }
  }
  return CoupPossible;  
}


int Plateau::countDiagoAsc(int player){
  int count = 0;
  for(int i = 0; i < 3; i++){
    if (grille[i][2-i] == player)
      count++;
  }
  return count;
}

int Plateau::countDiagoDesc(int player){
  int count = 0;
  for(int i = 0; i < 3; i++){
    if(grille[i][i] == player)
      count++;
  }
  return count;
}

int Plateau::countColonne(int player, int i){
  int count = 0;
  for(int j = 0; j < 3; j++){
    if(grille[j][i] == player){
      count++;
    }
  }
  return count;
}

int Plateau::countLine(int player, int i){
  int count = 0;
  for(int j = 0; j < 3; j++){
    if(grille[i][j] == player)
      count++;
  }
  return count;
}

bool Plateau::verifTrap(){
  if((countDiagoDesc(1) == 2 || countDiagoAsc(1) == 2) && grille[1][1] == 2){
    return true;
  }
  return false;
}
