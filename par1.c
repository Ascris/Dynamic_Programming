#include <stdio.h>
#define NC 3 //Number of columns
#define NR 7 //Number of rows


//Z and x from the algorithm
int z[NC][NR];
int x[NC][NR];

//The matrix, initiliase here with some values
int c[NC][NR]={0,3,4,4,4,4,4,
                0,4,6,7,8,8,8,
                0,2,4,6,7,8,9};

/**
*Used to display a matrix of int
*
*Need a char, which is the name of the matrix ('c','z' or 'x')
*/
void display(char car)
{
    
    int columns;
    int rows;
    for(columns=0;columns<NC;columns++)
    {
        for(rows=0;rows<NR;rows++)
        {
            switch(car)
            {
                case 'c':
                    printf("c[%d][%d]=%d\n",columns,rows,c[columns][rows]);
                    break;
                case 'z':
                    printf("z[%d][%d]=%d\n",columns,rows,z[columns][rows]);
                    break;
                case 'x':
                    printf("x[%d][%d]=%d\n",columns,rows,x[columns][rows]);
                    break;
            }
            
        }
    }
}
/**
* Is used to initialise the matrix. Put all to zero and initialise the first column of z and x after c
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
            z[loop1][loop2]=0;
            x[loop1][loop2]=0;
        }
    }
    
    for(loop1=0;loop1<NR;loop1++)
    {
        z[0][loop1]=c[0][loop1];
        x[0][loop1]=loop1;
    }
}

/**
* Run the algorithm on the matrix c
* Fill matrixx and z
*
* First loop is used to see each column
* Second is used to browse through the rows
* The third lets us calculate the value for each z and x
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
                //To understand this, go see your document. The principle is get the max value from the loop, i did this with an if condition
                temp=c[loop1][loop3]+z[loop1-1][loop2-loop3];
                //printf("I found %d with c=%d and z[%d][%d]=%d | ",temp,c[loop2][loop3],loop1-1,loop2-loop3,z[loop1-1][loop2-loop3]);
                if(temp>=z[loop1][loop2])
                {
                   z[loop1][loop2]=temp;
                   x[loop1][loop2]=loop3; 
                }
            }
            //printf("\n");
        }
    }
}

/**
* Let us see the results from the z and x, and calculate the total profit and the optimal solution based on the two matrix
*
*
*/

void result()
{
    int res[NC],loop1;
    int total=NR-1;
    for(loop1=NC-1;loop1>=0;loop1--)
    {
        res[loop1]=x[loop1][total];
        total=total-res[loop1];
    }
    
    
    printf("The total profit is : %d\n",z[NC-1][NR-1]);
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

/**
* A simple main
*
*/
int main()
{
    init();
    run();
    display('z');
    printf("\n");
    display('x');
    result();
}
