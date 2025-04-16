#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sorting(float *no, int len, short int opt);

int main()
{
    int i, n=0, lmt=1;
    short int opt;

    float *ptr = (float*) malloc(lmt*sizeof(float));
    
    printf("\n|> Enter any Character to end the program! <|\n");
    printf("\nEnter no%2d =>",n+1);
    
    while(scanf("%f",&ptr[n])==1)
    {   
        n++;
        if(n == lmt) {
            lmt = lmt+1;
            ptr = realloc(ptr, sizeof(float)*lmt);
            // printf("\n-- N=%d, lmt=%d --\n", n, lmt);
        }
        printf("Enter no%2d =>",n+1);
    }
    while(getchar()!='\n');
    
    if(n==0) {
        printf("\n*No numbers are saved!");
        printf("\n- Enter atleast 2 Numbers.\n");
        return 1;
    }
    else if(n==1){
        printf("\n- There is no need to sort a single number!");
        return 1;
    }

    int isfloat = 0;    //Check is numbers are in float or not
    for(i=0; i<n; i++){
        if(ptr[i] - (int)ptr[i] != 0){
            isfloat = 1;
            break;
        }
    }
    
    
    char type[15];
    restart:
    printf("\nSelect Sorting type :-");
    printf("\n1. Ascending order");
    printf("\n2. Descending order");
    
    printf("\n\nEnter option =>");
    scanf("%d",&opt);
    while(getchar()!='\n');

    if(opt==1){
        strcpy(type, "Ascending");
    }
    else if(opt==2){
        strcpy(type, "Descending"); 
    }
    else {
        printf("\nInvalid option!\n");
        printf("\nDo you want to Continue?");
        printf("\n1. Yes");
        printf("\n2. No");
        
        printf("\nOption =>");
        scanf("%d",&opt);
        
        if(opt==1){
            printf("\n- Restarted!");
            goto restart;
        }
        else {
            free(ptr);
            printf("\n- Program ended!");
            return 1;
        }
    }


    printf("\n\n<--- Sorted in %s order --->\n",type);

    sorting(ptr, n, opt);
    for(i=0; i<n; i++) {
        if(isfloat) {
            printf("\nNo%2d => %.2f", i+1, ptr[i]);
        }
        else {
            printf("\nNo%2d => %.f", i+1, ptr[i]);
        }
    }

    free(ptr);
    return 0;
}


void sorting(float *no, int len, short int opt) {
    int i, j;
    float temp;
    short int inc=0, inc2=0;
    
    (opt == 1) ? (inc2 = 1) : (inc = 1);
    
    for(i=0; i<len-1; i++)
    {
        for(j=0; j<len-i-1; j++) {

            if(no[j+inc] > no[j+inc2]) {
                temp = no[j+1];
                no[j+1] = no[j];
                no[j] = temp;
            }
        }
    }
    
}