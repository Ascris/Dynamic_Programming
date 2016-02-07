#include "../include/part1.h"

//myz and myx from the algorithm
int myz[NC][NR];
int myx[NC][NR];

//The matrix, initiliase here with some values
int data[NC][NR]={0,3,4,4,4,4,4,
                0,4,6,7,8,8,8,
                0,2,4,6,7,8,9};

/**
*Used to display a matrix of int, designed to be quick for debug
*
*Need a char, which is the name of the matrix ('c','z' or 'myx')
*/
void display(char car)
{
    
    int columns;
    int rows;
    printf("J'affiche %c\n    ",car);
    for(columns=0;columns<NC;columns++)
    {
        printf("%2d|",columns);
    }
    printf("\n");
    for(rows=0;rows<NR*3+4;rows++)
    {
        printf("-");   
    }
    printf("\n");
    for(rows=0;rows<NR;rows++)
    {
        printf("%2d->",rows);
        for(columns=0;columns<NC;columns++)
        {
            switch(car)
            {
                case 'd':
                    printf("%2d|",data[columns][rows]);
                    break;
                case 'z':
                    printf("%2d|",myz[columns][rows]);
                    break;
                case 'x':
                    printf("%2d|",myx[columns][rows]);
                    break;
            }
            
        }
        printf("\n");
    }
}
/**
* Is used to initialise the matrix. Put all to myzero and initialise the first column of myz and x after data
*
*
*/
void init()
{
    int loop1,loop2,loop3;
    for(loop1=1;loop1<NC;loop1++)
    {
        for(loop2=0;loop2<NR;loop2++)
        {
            myz[loop1][loop2]=0;
            myx[loop1][loop2]=0;
        }
    }
    
    for(loop1=0;loop1<NR;loop1++)
    {
        myz[0][loop1]=data[0][loop1];
        myx[0][loop1]=loop1;
    }
}

/**
* Run the algorithm on the matrix data
* Fill matrixx and myz
*
* First loop is used to see each column
* Second is used to browse through the rows
* The third lets us calculate the value for each myz and myx
*/
void run()
{
    int loop1,loop2,loop3;
    for(loop1=1;loop1<NC;loop1++)
    {
        for(loop2=1;loop2<NR;loop2++)
        {
            int temp=0;
            
            for(loop3=0;loop3<=loop2;loop3++)
            {
                //To understand this, go see your document. The principle is get the mamyx value from the loop, i did this with an if condition
                temp=data[loop1][loop3]+myz[loop1-1][loop2-loop3];
                //printf("I found %d with c=%d and myz[%d][%d]=%d | ",temp,c[loop2][loop3],loop1-1,loop2-loop3,myz[loop1-1][loop2-loop3]);
                if(temp>=myz[loop1][loop2])
                {
                   myz[loop1][loop2]=temp;
                   myx[loop1][loop2]=loop3; 
                }
            }
            //printf("\n");
        }
    }
}

/**
* Let us see the results from the myz and x, and calculate the total profit and the optimal solution based on the two matrix
*
*
*/

void result()
{
    int res[NC],loop1;
    int total=NR-1;
    for(loop1=NC-1;loop1>=0;loop1--)
    {
        res[loop1]=myx[loop1][total];
        total=total-res[loop1];
    }
    
    
    printf("The total profit is : %d\n",myz[NC-1][NR-1]);
    printf("The optimal solution is : [");
    for(loop1=0;loop1<NC;loop1++)
    {
        printf("%d",res[loop1]);
        if(loop1!=NC-1)
        {
            printf(",");
        }
    }
    printf("]\n");
}

