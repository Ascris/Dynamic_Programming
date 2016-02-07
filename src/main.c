#include "../include/part2.h"
#include "../include/part1.h"


/*
 * FUNCTION MAIN
 */

int main(int argc, char* argv[])
{
    //begining of timer
    int loop;
    
    if(argc==1)
    {
        printf("\tPlease give the number of the part, 1 for part 1 and 2 for part 2.\n\tYou can give the name of the file you want to use, on default it uses the file of GARNIER_Antoine. \n\tYou just need to give the name, like \"GARNIER_Antoine\"\n");
        printf("\tFor exemple : \n\t\t './bin/ks.exe 1'\n\t\t'./bin/ks.exe 2 GARNIER_Antoine'\n");
    }
    else
    {
        //execute the part 1
        if(argv[1][0]=='1')
        {
            init();
            run();
            display('z');
            printf("\n");
            display('x');
            result();
        }
        //Execute the part 2
        else if(argv[1][0]=='2')
        {
            char c[60]="./txtfiles/";
            if(argc==3)
            {
                strcat(c,argv[2]);
                strcat(c,".txt");
            }
            else
            {
                strcat(c,"GARNIER_Antoine.txt");
            }
            
            loadFile(c,&n,&b,&it);
            ftime(&t0);

            
            //variables initialization
            k = n;
            alpha = b;
            
            
            computeProfit();
            
            printf("\nThe Optimal Profit is %d", getOptimalProfit());
            

            ftime(&t1);
            //end of timer
            cpu_time = (double)(t1.time - t0.time) + (double)(t1.millitm-t0.millitm)/1000.0;
            printf("\nCPU time : %f seconds.\n", cpu_time);
            
            //It's free time !
            for(loop=0;loop<n;loop++)
            {
                free(z[loop]);
                free(x[loop]);
            }
            free(it);
            free(z);
            free(x);
        }
    }
}

