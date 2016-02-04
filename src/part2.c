#include <stdio.h>
#include <sys/select.h>
#define N 596 //Number of items
#define B 3203 //Capacity of the Knapsack

/*
 * k and alpha have to be modified by each file
 */
int k = N;
int alpha = B;

//total profit of solving the 0-1 KP on the N first items with capacity B
int z[N][B];
//corresponding decision variable associated with the item N
int x[N][B];


/*
 * ITEMS GET FROM THE FILE 
 * 
 */
struct item{
    int id;
    int c;
    int a;
};
typedef struct item item;

//array of items
item* tabItem;

/*
 * TO DELETE
 */

/*
 * FUNCTIONS
 */
//initialization of Z
int initZ(int k, int alpha){
    if(tabItem[k].a <= alpha) return tabItem[k].c;
    else if(alpha < 0) return -1;
    else return 0;
}
//initialization of X
int initX(int k, int alpha){
    if(tabItem[k].a <= alpha) return 1;
    else return 0;
}

//recursive function which choose the best option (put item k in the KS or not) to increase the profit
int getProfit(int k, int alpha){
    //to select or not to select k, that is the question
    int c = tabItem[k].c;
    int a = tabItem[k].a;
    int x = x[k][alpha];
    
    if(c*x + z[k-1][alpha-(a*x)] > z[k-1][alpha] ){
	return (c*x + getProfit(k-1, (alpha-(a*x))));
    } else {
	return (getProfit(k-1, alpha));
    }
    
    return 0;
}


//building of the final array Z which will contain all the optimal values
void computeProfit(){
    int k, alpha, max = -1;
    for(k=0; k<N; ++k){
	for(alpha=0; alpha<B; ++alpha){
	    if(k==0){
		z[k][alpha] = initZ(k, alpha);
		x[k][alpha] = initX(k, alpha);
	    } else {
		z[k][alpha] = getProfit(k, alpha);
		if(getProfit(k, alpha) > getProfit(k-1, alpha)){
		    x[k][alpha] = 1;
		} else {
		    x[k][alpha] = 0;
		}
	    }
	}
    }
}


int getOptimalProfit(){
    return z[N-1][B-1];
}









int main(){
    
    
}