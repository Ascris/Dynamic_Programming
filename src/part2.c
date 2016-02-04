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

int computeZ(int k, int alpha){
    if(tabItem[k].a <= alpha) return tabItem[k].c;
    else if(alpha < 0) return -1;
    else return 0;
}

int computeX(int k, int alpha){
    if(tabItem[k].a <= alpha) return 1;
    else return 0;
}

//return the total profit if the item k is selected (select = 1) or not (select = 0)
int selectItem(int k, int select){
    //how to compute the total profit ?
    return 0;
}

//strange function, maybe... no to keep it
void chooseBestOption(int k, int alpha){
    int k;
    for(k=1; k<N; ++k){
	if(selectItem(k, 1) > selectItem(k, 0)){
	    chooseBestOption(k-1, alpha-tabItem[k].a);
	} else {
	    chooseBestOption(k-1, alpha);
	}
    }
    
}

//recursive function which choose the best option (put item k in the KS or not) to increase the profit
int getProfit(int k, int alpha){
    //to select or not to select k, that is the question
    
    return 0;
}


//building of the final array which will contain all the optimal values
void computeProfit(){
    int k, alpha, max = -1;
    for(k=0; k<N; ++k){
	for(alpha=0; alpha<B; ++alpha){
	    if(k==0){
		z[k][alpha] = computeZ(k, alpha);
		x[k][alpha] = computeX(k, alpha);
	    } else {
		int c = tabItem[k].c;
		int a = tabItem[k].a;
		int x = x[k][alpha];
		
		if(c*x + z[k-1][alpha-(a*x)] > max){
		    z[k][alpha] = getTotalProfit(k, alpha);
		}
	    }
	}
    }
}












int main(){
    
    
}