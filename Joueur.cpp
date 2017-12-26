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

int Joueur::getPower() const{
  return _power;
}

Pion Joueur::CreerCoup(Plateau plat){
  Pion p;
  if(getType() == "Humain"){
    p = Coup_Humain(plat);
  }
  else{
    p = Coup_Ia(plat,getPower());
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

Pion Joueur::Coup_Ia(Plateau plat, int diff){
  if(diff == 1){
    Pion p = CoupAlea(plat);
    return p;
  }
  Pion p = CoupMinMax(&plat);
  return p;
}

Pion Joueur::CoupAlea(Plateau plat){
  int xposition;
  int yposition;

  vector <Pion > possibilities;
  possibilities = plat.getCoupPossible();
  
  int indice = rand()%possibilities.size();

  xposition = possibilities[indice].getX();
  yposition = possibilities[indice].getY();
  
  Pion p(xposition,yposition,getId());
  return p;
}


//----------------------------------


Pion Joueur::CoupMinMax(Plateau* plat){
  int max_value = -99999;
  int actual_value;

  Pion bestP;
  int profondeur = 1;
  int nbCoups = 0;
  
  // on calcule les coups possibles
  vector<Pion> coups_jouables = plat->getCoupPossible();
  
  for(int x = 0; x < coups_jouables.size(); x++){
    //simulerCoup
    plat->poserPion(coups_jouables[x]);
    actual_value = MinCoup(plat,profondeur-1, nbCoups+1, coups_jouables[x]);
    if (actual_value > max_value || ((actual_value == max_value) && rand()%2)){
      
      max_value = actual_value;
      bestP = coups_jouables[x];
    }
    plat->retirerPion(coups_jouables[x]);
  }
  return bestP;
}

int Joueur::MaxCoup(Plateau* plat, int profondeur, int nbCoups,Pion c){
  if (plat->checkBoardFull() == true || plat->checkVictory() != 0 || profondeur==0){
    return evaluation(plat,nbCoups, c);
  }

  int actual_value;
  int max_value = -99999;

  vector<Pion > coups_jouables = plat->getCoupPossible();
  
  for(int x = 0; x < coups_jouables.size(); x++){
    //simulerCoup
    plat->poserPion(coups_jouables[x]);
    actual_value = MinCoup(plat, profondeur-1, nbCoups+1, c);

    if (actual_value > max_value || ((actual_value == max_value) && rand()%2)){
      max_value = actual_value;
    }
    
    plat->retirerPion(coups_jouables[x]);
  }
  return max_value;

}

int Joueur::MinCoup(Plateau* plat,int profondeur, int nbCoups,Pion c){
  if(plat->checkBoardFull() == true || plat->checkVictory() != 0 || profondeur == 0){
    return evaluation(plat,nbCoups, c);
  }

  int actual_value;
  int min_value = 99999;
  
  vector<Pion> coups_jouables = plat->getCoupPossible();

   for(int x = 0; x < coups_jouables.size(); x++){
    plat->poserPion(coups_jouables[x]);
    actual_value = MaxCoup(plat,profondeur-1,nbCoups+1, c);

    if (actual_value < min_value || ((actual_value == min_value) && rand()%2)){
      min_value = actual_value;
    }
    
    plat->retirerPion(coups_jouables[x]);
  }
   return min_value;
}



int Joueur::evaluation(Plateau* p,int nbCoups,Pion c){
  nbCoups = 0;
  if(p->checkBoardFull() == true || p->checkVictory() != 0){
    if(p->checkVictory() == 2){
      return 50000-nbCoups;
    }
    if(p->checkVictory() == 1){
      return -50000+nbCoups;
    }
    return 0;
  }

  int Value = 0;
  int pion_j1 = 0;
  int pion_j2 = 0;
  for(int i = 0; i < 3; i++){
    pion_j1 = p->countLine(1,i);
    pion_j2 = p->countLine(2,i);
    Value += Decision(pion_j1, pion_j2,nbCoups);
    
    pion_j1 = p->countColonne(1,i);
    pion_j2 = p->countColonne(2,i);
    Value += Decision(pion_j1, pion_j2,nbCoups);
  }
  pion_j1 = p->countDiagoDesc(1);
  pion_j2 = p->countDiagoDesc(2);
  Value += Decision(pion_j1, pion_j2,nbCoups);

  pion_j1 = p->countDiagoAsc(1);
  pion_j2 = p->countDiagoAsc(2);
  Value += Decision(pion_j1, pion_j2,nbCoups);

  
  int trap = false;
  trap = p->verifTrap();
  if(trap && p->_pastTrapIA == false){
    if(c.getX() ==1 || c.getY() ==1){
      cout << "Correction Trap ! " << endl;
      Value+=1000;
    }
  }
  return Value;
}


int Decision(int nbp1, int nbp2, int nbCoups){
  if(nbp1 == 2 && nbp2 == 1){return 300-nbCoups;}
  if(nbp1 == 0 && nbp2 == 2){return 100-nbCoups;}
  if(nbp1 == 0 && nbp2 == 1){return 50-nbCoups;}
  
  if(nbp1 == 1 && nbp2 == 1){return nbCoups;}
  if(nbp1 == 0 && nbp2 == 0){return 0;}
  if(nbp1 == 1 && nbp2 == 2){return -nbCoups;}
  
  if(nbp1 == 1 && nbp2 == 0){return -100+nbCoups;}
  if(nbp1 == 2 && nbp2 == 0){return -290+nbCoups;}

  return 0;
}
