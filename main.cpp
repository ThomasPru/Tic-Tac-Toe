#include <iostream>
#include "Plateau.hpp"


using namespace std;

int main(int agrc, char** argv){
  for(unsigned int i = 0; i < 5; i++){
    cout << "-------------------------------------------------------"<<endl;
  }
  cout<< "          --------------MORPION-------------"<<endl;
  for(unsigned int i = 0; i < 3; i++){
    cout << "          -----------------------------------"<<endl;
  }
  
  cout<< "       --------------LANCEMENT DU JEU-----------"<<endl;

  Plateau p;
  
  //On rentre dans la boucle du jeu
  int xposition;
  int yposition;

  bool gameState = true;
  while(gameState){
    p.switchPlayer();
    
    p.display();

    do{
    cout << "Choisissez les coordonnees de votre pion : Joueur "
	 << p.getActualPlayer() << " ! " << endl;
    cout << "Ligne : ";
    cin >> xposition;
    cout << endl;
    cout << "Colonne : ";
    cin >> yposition;
    }
    while (!p.checkLegalMove(xposition, yposition));

    Pion pion(xposition-1, yposition-1, p.getActualPlayer());
    
    p.poserPion(pion);
    gameState = !p.checkVictory();
    
  }
  p.display();
  cout << "Le gagnant est le joueur : " << p.getActualPlayer() << endl;
  
  return 0;
}
