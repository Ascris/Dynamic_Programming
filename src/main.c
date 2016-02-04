#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct item{
    int id;
    int a;
    int c;
};
typedef struct item item;


int main(int argc, char* argv[])
{
    item* tabItem;// = (item*)malloc(400*sizeof(item));
    int indRempTabItem = 0; //indice de remplissage du tableau d'items (vector ou pas vector ?)
    int nbItems, sizeKS;
    
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
	      
	      if(tailleLigne == 2){
// 		int nbItems, sizeKS;
		string mot;
		istringstream line(ligne);
		int nbMot = 0;
		while(line >> mot){
		    if(nbMot == 0) nbItems = stoi(mot);
		    else if (nbMot == 1) sizeKS = stoi(mot);
		    printf("nbItems = %d ; sizeKS = %d", nbItems, sizeKS);
		}
		//allocation de la memoire necessaire au stokage de tous les items
		tabItem = (item*)malloc(nbItems*sizeof(item));
		
	      } else if(tailleLigne == 3){
		int x1, x2, x3;
		string mot;
		istringstream line(ligne);
		int nbMot = 0;
		while(line >> mot){
		  if(nbMot == 0) x1 = stoi(mot);
		  else if (nbMot == 1) x2 = stoi(mot);
		    else x3 = stoi(mot);
		  
		  ++nbMot;
		}
		// x2, x2, x3 a mettre dans une structure
		item new_item;
		new_item.id = x1;
		new_item.a = x2;
		new_item.c = x3;
		tabItem[indRempTabItem] = new_item;
		++indRempTabItem;
	      }
	    } //premiere ligne particuliere
	      ++nbLignes;
	  }
	  
	  //LECTURE FICHIER FINIE
	  
	  
	  //affichage des valeurs ?
	  cout << "Capacite du sac : " << sizeKS << endl;
	  int i;
	  for(i = 0; i < nbItems; ++i){
	    cout << "Item " << tabItem[i].id << endl;
	  }
	  
	  
	} else {
	    cerr << "Impossible d'ouvrir le fichier";
	}
}//fin main*/

struct item{
    int id;
    int a;
    int c;
};
typedef struct item item;



int get_file_size(char *file_name)
{
   FILE *fp;
   int file_size;
   file_size = 0;
   if ((fp = fopen(file_name, "rb" )) == NULL) {
      fprintf(stderr, "Cannot open %s.\n", file_name);
      return(file_size);
   }
   char ligne[30];
   while(fgets(ligne, 30,fp) != NULL)
    {
	    file_size++;
    }
   fclose(fp);
   return(file_size);
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result =(char**) malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }

    return result;
}


void loadFile(char* filename, int *n, int *b, item **it)
{
    
    
    int size=get_file_size(filename);	
	FILE *fichier;
    fichier=fopen(filename,"r");
	
	if (fichier != NULL)
	{		
		char ** text=(char**)malloc(sizeof(char*)*size);
		char ligne[30];
		int num_ligne;
		for(num_ligne=0; fgets(ligne, 30,fichier) != NULL; ++num_ligne)
		{
			text[num_ligne]=(char*)malloc(sizeof(char)*(strlen(ligne)+1));
			strcpy(text[num_ligne],ligne);
		}
		
		char **ligne1=str_split(text[0],' ');
        
		int nb_noeuds=atoi(ligne1[0]);
        int capacity=atoi(ligne1[1]);
        
        printf("Fichier avec les caractéristiques : %d %d\n",nb_noeuds,capacity);
        
        *it=(item*)malloc(sizeof(item)*nb_noeuds);
		
		free(ligne1);
		
		int i;
		for(i=1;i<nb_noeuds+1;i++)
		{
			char **ligne1=str_split(text[i],' ');
            
            unsigned id=(unsigned)atoi(ligne1[0]);
			int size=atoi(ligne1[1]);
			int cost=atoi(ligne1[2]);
			
            (*it)[i-1].id=id;
            (*it)[i-1].a=size;
            (*it)[i-1].c=cost;
			free(ligne1);
		}
		
		for (i= 0; i < size; ++i){
		    free(text[i]);
		}
		free(text);
		fclose(fichier);
        
        *n=nb_noeuds;
        *b=capacity;
	}
	else
	{
	  // On affiche un message d'erreur si on veut
	  fprintf(stderr, "%s\n","Impossible d'ouvrir le fichier \n");
	}
}

int main(int argc, char* argv[])
{
    int n,b;
    item *it;
    char c[60]="./txtfiles/";
    if(argc>1)
    {
        strcat(c,argv[1]);
        strcat(c,".txt");
    }
    else
    {
        strcat(c,"GARNIER_Antoine.txt");
    }
    
    
    loadFile(c,&n,&b,&it);
}

