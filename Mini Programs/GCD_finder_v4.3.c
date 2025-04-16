#include <stdio.h>

int gcd_finder(int a, int b);

int main()
{
    int a, b, no[4];
    int i=0, gcd=0, count=0, n=0;
    char comma;
    
    printf("\n-----: GCD FINDER :-----");
    
    printf("\n\n*Enter 2 or 3 numbers, Separated by comma(,)");
    printf("\n  e.g. 252,396,468");
    
    printf("\n\nEnter numbers =>");
    
    while(1){
        if(scanf("%d%c",&no[count], &comma)==0){
            goto end;
        }
        
        if(count>=2 || comma == '\n'){
            break;
        } 
        
        if(comma != ','){
            printf("\nInvalid sign! Please use comma only.");
            return 1;
        }
        count++;
    }

    for(i=0; i<=count; i++){
         if(count == 0){
             printf("\n*Please enter at least 2 positive numbers.");
             return 1;
         }
         if(no[i]<=0){
             end:
             printf("\nInvalid input! Use only Natural numbers.");
             return 1;
         }
    }
    
    if(0){
        restart:
        count = -1;
        no[3] = gcd;
        n = 2;
    } 
    
    if(no[n] <= no[n+1]) {
        a = no[n+1];
        b = no[n];
    }
    else {
        a = no[n];
        b = no[n+1];
    }
    
    
    printf("\nGCD process for %d and %d :",a,b);
    
    gcd = gcd_finder(a, b);
    printf("\n\n--> GCD(%d,%d) = %d\n",no[0], no[1], gcd);
    
    if(count == 2){
        goto restart;
    }
    else if(count == -1){
        printf("\n\nFINAL => GCD(%d,%d,%d) = %d\n", no[0], no[1], no[2], gcd);
    }
    
    return 0;
} 


int gcd_finder(int a, int b){

    int r, q;
    int i=0;
    
    while (b!=0) {
    
        q = a/b;
        r = a % b;
        
        if(i==0) {
            printf("\n=>%4d = %d(%d) + %d",a,b,q,r);
        }
        else {
            printf("\n  %4d = %d(%d) + %d",a,b,q,r);
        }
        
        a = b;
        b = r;
        i++;
    }
    
    return a;
}