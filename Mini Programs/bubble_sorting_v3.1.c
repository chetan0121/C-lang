#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sorting(float *no, int len, short int opt);

int main()
{
    int i, n=0, lmt=4;
    int opt;

    float *ptr = (float*) malloc(lmt*sizeof(float));
    
    printf("\n------< BUBBLE SORTING >------");
    printf("\n*Enter any character to end the program!\n");
    printf("\nEnter no%2d =>",n+1);
    
    while(scanf("%f",&ptr[n])==1)
    {   
        n++;
        if(n == lmt) {
            lmt = lmt + (lmt/2); //Grows 50% of the last limit
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
    
    int isfloat = 0;    //Check if numbers are in float or not
    for(i=0; i<n; i++){
        if((ptr[i] - (int)ptr[i]) != 0){
            isfloat = 1;
            // printf("\n*Float found %d, diff = %f\n", i+1, ptr[i] - (int)ptr[i]);
            break;
        }
    }
    
    char sortingType[15];
    restart:
    printf("\nSelect Sorting type :-");
    printf("\n1. Ascending order");
    printf("\n2. Descending order");    
    printf("\n\nEnter option =>");
    scanf("%d",&opt);
    while(getchar()!='\n');

    if(opt==1){
        strcpy(sortingType, "Ascending");
    }
    else if(opt==2){
        strcpy(sortingType, "Descending"); 
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

    printf("\n\n<--- Sorted in %s order --->\n",sortingType);
    sorting(ptr, n, opt);
    
    for(i=0; i<n; i++) {
        if(isfloat==1) {
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
    short int swapped;
    
    for(i=0; i<len-1; i++)
    {
        swapped = 0;
        for(j=0; j<len-i-1; j++) {

            if ((opt==1 && no[j] > no[j+1]) || (opt==2 && no[j] < no[j+1])) {
                temp = no[j];
                no[j] = no[j+1];
                no[j+1] = temp;
                swapped = 1;
            }
        }
        if(!swapped){
            // printf("\n*Output is same because the Array was already sorted.");
            break;
        } 
    }

}
