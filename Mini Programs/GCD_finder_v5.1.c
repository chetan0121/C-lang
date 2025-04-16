#include <stdio.h>

int gcd_finder(int a, int b);

int main()
{
    int no[3];
    int i=0, gcd=0, count=0;
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
             printf("\n*Invalid input! Use only Natural numbers.");
             return 1;
         }
    }
    
    i=0;
    while(i<count){
        
        if(i<1){
            printf("\n\nGCD process for %d and %d :", no[i], no[i+1]);
            gcd = gcd_finder(no[i], no[i+1]);
            printf("\n\n--> GCD(%d,%d) = %d\n",no[i], no[i+1], gcd);
        }
        else {
            printf("\n\nGCD process for %d and %d :", gcd, no[i+1]);
            gcd = gcd_finder(gcd, no[i+1]);
            printf("\n\nFINAL ==> GCD(%d,%d,%d) = %d\n", no[0], no[1], no[2], gcd);
        }
        i++;
    }
    
    return 0;
} 


int gcd_finder(int a, int b){
    if(a<b){
        int temp = a;
        a = b;
        b = temp;
    }
    int r, q;
    int i=0;
    
    while (b!=0) {
        q = a/b;
        r = a % b;
        
        if(i==0) {
            printf("\n->%4d = %d(%d) + %d",a,b,q,r);
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