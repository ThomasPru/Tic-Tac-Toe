#include <iostream>
//#include "Humain.hpp"
//#include "Ia.hpp"
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
    _players.push_back(new Joueur(2, 1));
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

  bool gameRun = true;
  
  while (gameRun) {
    p.switchPlayer();
    p.display();

    p.getCoupPossible();
    
    p.poserPion( _players[p.getActualPlayer()-1]-> CreerCoup(p) );

    gameRun = !p.checkVictory();
    if(gameRun == true){
      gameRun = !p.checkBoardFull();
    }
  }

  
  
  p.display();
  if(p.checkBoardFull() && !p.checkVictory()){
    cout << "Egalite !" << endl;
  }
  else{
    cout << "Le gagnant est le joueur " << p.getActualPlayer() << " : "
	 << _players[p.getActualPlayer()-1] -> getName() <<endl;
  }
  return 0;
}
