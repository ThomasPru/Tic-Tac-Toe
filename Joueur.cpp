#include "Joueur.hpp"

Joueur::Joueur(int id, int power){
  _name = "Alice-BOT";
  _type = "Ia";
  _id = id;
  _power = power;
}

Joueur::Joueur(string name, int id){
  _name = name;
  _id = id;
  _type = "Humain";
}

string Joueur::getName() const{
  return _name;
}

string Joueur::getType() const{
  return _type;
}

int Joueur::getId() const{
  return _id;
}

Pion Joueur::CreerCoup(Plateau plat){
  Pion p;
  if(getType() == "Humain"){
    p = Coup_Humain(plat);
  }
  else{
    p = Coup_Ia(plat);
  }
  return p;
}


Pion Joueur::Coup_Humain(Plateau plat){
  int xposition;
  int yposition;
  do{
    cout << "Choisissez les coordonnees de votre pion : Joueur "
	 << getId() << " ! " << endl;
    cout << "Ligne : ";
    cin >> xposition;
    cout << "Colonne : ";
    cin >> yposition;
    }
  while(!plat.checkLegalMove(xposition, yposition));

  Pion p(xposition-1,yposition-1,getId());

  return p;
}

Pion Joueur::Coup_Ia(Plateau plat){
  int xposition;
  int yposition;

  vector <vector<int> > possibilities;
  possibilities = plat.getCoupPossible();
  
  int indice = rand()%possibilities.size();

  xposition = possibilities[indice][0];
  yposition = possibilities[indice][1];
  
  Pion p(xposition,yposition,getId());

  return p;
}


