#include <iostream>
#include "Joueur.hpp"

using namespace std;

int main(int agrc, char** argv){
  
  srand (time(NULL));
  
  for(unsigned int i = 0; i < 5; i++){
    cout << "-------------------------------------------------------"<<endl;
  }
  cout<< "          --------------MORPION--------------"<<endl;
  for(unsigned int i = 0; i < 3; i++){
    cout << "          -----------------------------------"<<endl;
  }

  //-----Initialisation des joueurs
  vector <Joueur*> _players;
  
  string J1name;
  cout << "Joueur 1, quel est ton nom ?" << endl;
  cout << "name = ";
  cin >> J1name;
  _players.push_back(new Joueur(J1name, 1));
  
  int typeJ2;
  cout << "Votre adversaire est-il un humain ? ou une Ia ? (Humain:0 / Ia:1 ) " << endl; 
  cin >> typeJ2;
  
  if(typeJ2 == 0){
    string J2name;
    cout << "Joueur 2, quel est ton nom ?" << endl;
    cout << "name = ";
    cin >> J2name;
    _players.push_back(new Joueur(J2name, 2));
  }
  else{
    int pow;
    cout << "Quel est le niveau de votre adversaire ?" << endl;
    cout << "FACILE (1) --- NORMAL (2)" << endl;
    cin >> pow;
    while(pow != 1 && pow != 2){
      cout << "Veuillez saisir 1 ou 2 : ";
      cin >> pow;
    }
    _players.push_back(new Joueur(2, pow));
  }
  //-----Fin initialisation joueurs

  
  for(unsigned int i = 0; i < 3; i++){
    cout << "------------------------------------------------------"<<endl;
  }
  cout << "JOUEUR 1 :" << _players[0]->getName() << " (" <<_players[0]->getType() <<")  ***    VS    *** "
       << "JOUEUR 2 :" << _players[1]->getName() << " (" <<_players[1]->getType() <<")"<< endl;
  for(unsigned int i = 0; i < 3; i++){
    cout << "------------------------------------------------------"<<endl;
  }


  cout << "     ----------------LANCEMENT DU JEU----------------"<<endl;
  Plateau p;

  //On rentre dans le jeu
  int xposition;
  int yposition;

  int gameRun = 0;
  
  while (gameRun == 0) {
    p.switchPlayer();
    p.display();
    
    p.poserPion( _players[p.getActualPlayer()-1]-> CreerCoup(p) );

    gameRun = p.checkVictory();
    if(gameRun == 0){
      gameRun = p.checkBoardFull();
    }
  }

  p.display();
  if(p.checkBoardFull() == 1 && p.checkVictory() == 0){
    cout << "Egalite !" << endl;
  }
  else{
    cout << "Le gagnant est le joueur " << p.checkVictory() << " : "
	 << _players[p.checkVictory()-1] -> getName() <<endl;
  }
  return 0;
}
