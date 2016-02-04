#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct item{
    int id;
    int a;
    int c;
};
typedef struct item item;

int n,b;
item *it;
char c[60]="./txtfiles/";

//initialisation of the variables used in the DP for 0-1 KP
// k and alpha have to be modified by each file
int k;
int alpha;

//TODO recuperer les vraies valeurs du fichier txt lu !!
//total profit of solving the 0-1 KP on the N first items with capacity B
int z[596][3203];
//corresponding decision variable associated with the item N
int x[596][3203];

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

/*
 * FUNCTIONS PART 2
 */

/*
 * FUNCTIONS
 */
//initialization of Z
int initZ(int k, int alpha){
    if(it[k].a <= alpha) return it[k].c;
    else if(alpha < 0) return -1;
    else return 0;
}
//initialization of X
int initX(int k, int alpha){
    if(it[k].a <= alpha) return 1;
    else return 0;
}

/*
//recursive function which choose the best option (put item k in the KS or not) to increase the profit
int getProfit(int k, int alpha){
    //to select or not to select k, that is the question
    if(k > 1){
	int c = it[k].c;
	int a = it[k].a;
	int xk = x[k][alpha];
	
	int item1 = getProfit(k-1,alpha);
	int item2 = c+getProfit(k-1, alpha-a);
	
	int maxFinal = max(item1, item2);
	return maxFinal;
    } else {
	return z[k-1][alpha];
    }
    
    return 0;
}
*/

//building of the final array Z which will contain all the optimal values
void computeProfit(){
    int k, alpha;
    for(k=0; k<n; ++k){
	printf("\nk = %d", k);
	for(alpha=0; alpha<b; ++alpha){
	    if(0==k){
		z[k][alpha] = initZ(k, alpha);
		x[k][alpha] = initX(k, alpha);
	    } else if(it[k-1].a <= alpha){
		    z[k][alpha] = max(it[k-1].c + z[k-1][alpha-it[k-1].a],  z[k-1][alpha]);
	    } else {
		 z[k][alpha] = z[k-1][alpha];
	    }
	}
    }
}


int getOptimalProfit(){
    return z[n-1][b-1];
}

//easier to read
int max(int a, int b){
    if(a>b) return a;
    else return b;
}

/*
 * FUNCTION MAIN
 */

int main(int argc, char* argv[])
{
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

    
    //TODO test of the 2nd part
    //variables initialization
    k = n;
    alpha = b;
    
    
    computeProfit();
    
    printf("\nThe Optimal Profit is %d", getOptimalProfit());
    

}

