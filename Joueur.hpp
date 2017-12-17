#ifndef JOUEUR_HPP_
#define JOUEUR_HPP_

#include <iostream>
#include <string>
#include "Plateau.hpp"

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

  Pion CreerCoup(Plateau p);

  Pion Coup_Humain(Plateau plat);
  Pion Coup_Ia(Plateau plat);
};

#endif
