#ifndef PART2
#define PART2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/timeb.h>

struct item{
    int id;
    int a;
    int c;
};
typedef struct item item;

int n,b;
item *it;

//initialisation of the variables used in the DP for 0-1 KP
// k and alpha have to be modified by each file
int k;
int alpha;

//TODO recuperer les vraies valeurs du fichier txt lu !!
//total profit of solving the 0-1 KP on the N first items with capacity B
int **z;
//corresponding decision variable associated with the item N
int **x;


//CPU TIME
struct timeb t0, t1;    /* Timers */
double cpu_time;        /* Time */


int get_file_size(char *file_name);
char** str_split(char* a_str, const char a_delim);
void loadFile(char* filename, int *n, int *b, item **it);
int initZ(int k, int alpha);
int initX(int k, int alpha);
int max(int a, int b);
void computeProfit();
int getOptimalProfit();

#endif
