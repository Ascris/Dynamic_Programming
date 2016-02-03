#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct item{
    int id;
    int value;
    int cost;
};
typedef struct item item;


int main(int argc, char* argv[])
{
    item* tabItem = (item*)malloc(400*sizeof(item));
    int indRempTabItem = 0; //indice de remplissage du tableau d'items (vector ou pas vector ?)
    
    //fichier à prendre en compte
     ifstream fichier("GARNIER_Antoine.txt");
        if(fichier) {
	  string ligne;
	  int nbLignes = 0;
	  while(getline(fichier, ligne)){
	    if(nbLignes > 0){
	      int tailleLigne = 0;
	      string mot;
	      istringstream line(ligne);
	      
	      while(line >> mot){
		++tailleLigne;
	      }
	      
	      if(tailleLigne == 3){
		int x1, x2, x3;
		string mot;
		istringstream line(ligne);
		int nbMot = 0;
		while(line >> mot){
		  if(nbMot == 0) x1 = std::stoi(mot);
		  else if (nbMot == 1) x2 = std::stoi(mot);
		    else x3 = std::stoi(mot);
		  
		  ++nbMot;
		}
		// x2, x2, x3 a mettre dans une structure
		item new_item;
		new_item.id = x1;
		new_item.value = x2;
		new_item.cost = x3;
		tabItem[indRempTabItem] = new_item;
		++indRempTabItem;
	      }
	    } //premiere ligne particuliere
	      ++nbLignes;
	  }
	} else {
	    cerr << "Impossible d'ouvrir le fichier";
	}
}//fin main