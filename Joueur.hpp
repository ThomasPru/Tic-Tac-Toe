#ifndef JOUEUR_HPP_
#define JOUEUR_HPP_

#include <iostream>
#include <string>
#include "Plateau.hpp"
#include "time.h"

using namespace std;

class Joueur{
private:
  string _type;
  string _name;
  int _id;
  int _power;
public:
  Joueur(int id, int power);
  Joueur(string name, int id);

  string getName() const;
  string getType() const;
  int getId() const;
  int getPower() const;

  Pion CreerCoup(Plateau p);

  Pion Coup_Humain(Plateau plat);
  Pion Coup_Ia(Plateau plat, int diff);
  Pion CoupAlea(Plateau plat);
  
  Pion CoupMinMax(Plateau* plat);
  int MinCoup(Plateau* copiePlat, int profondeur, int nb_Coups,Pion c);
  int MaxCoup(Plateau* copiePlat, int profondeur, int nb_Coups,Pion c);

  int evaluation(Plateau* p, int nbCoups,Pion c);
  int countEffective(int nbCoups);
};

int Decision(int nbP1, int nbP2, int nbCoups);


#endif
