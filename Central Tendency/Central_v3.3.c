#include <stdio.h>
#include <stdlib.h>

#define tableMode 1     // 1 = On , 0 = Off.....It is advisable to turn off if running on Smartphone

/* Other meanings :
   CTtype = Central tendency type
   mtype/Methodtype = types of Methods __ class&fi==1 __ xi&fi==2 __ only xi==3
*/

int YorN();
int get_input(int ctype);
float MaxfromArray(float arr[], int len, short int* imax);
void sortingArray(float no[], int len);
char* needSpace(int target, int lmt);
int countMax(float target[], int len, short int *imax);

int getMeanType();

int findMean(int n, float classRange[][2], float fi[], float xi[], int mtype);
int findMedian(int n, float ClassInterval[][2], float fi[], float xi[], int MethodType);
int findMode(int n, float ClassInterval[][2], float fi[], float xi[], int MethodType);


int main() {
    int opt;

    printf("\n----- MEASURES OF CENTRAL TENDENCY -----");
    printf("\n1. Mean");
    printf("\n2. Median");
    printf("\n3. Mode");
    
    printf("\n\nEnter option =>");
    scanf("%d",&opt);
    
    if(opt==1){
        printf("\n\n---- Arithmetic Mean ----");
        get_input(1);
    }
    else if(opt==2){
        printf("\n\n---- Median ----");
        get_input(2);
    }
    else if(opt==3){
        printf("\n\n---- Mode ----");
        get_input(3);
    }
    else {
        printf("\nInvalid Option! You have to enter numbers from 1 to 3.");
        return 1;
    }

    // printf("\n\n**Process Done in Main!");
    printf("\n");
    return 0;
}



int YorN(){
    int opt;
    printf("\n1. Yes");
    printf("\n2. No");
    printf("\n\nEnter Option ->");
    if(scanf("%d",&opt)==0){
        return -1;
    }

    return opt;
}
int getMeanType(){
    int mType=0;
    printf("\n\nTypes of Mean :");
    printf("\n1. Direct Method");
    printf("\n2. Assumed Mean");
    printf("\n3. Step Deviation");
    printf("\nPress any Key to select Auto...");

    printf("\n\nEnter your choice =>");
    if(scanf("%d",&mType)==0){
        return -1;
    }
    if(mType<1 || mType>3){
        printf("*Invalid option, Auto selected.\n");
        return -1;
    }
    return mType;
}
void sortingArray(float no[], int len) {
    int i, j;
    float temp;
    
    for(i=0; i<len-1; i++)
    {
        for(j=0; j<len-i-1; j++) {

            if(no[j] > no[j+1]) {
                temp = no[j+1];
                no[j+1] = no[j];
                no[j] = temp;
            }
        }
    }
}
float MaxfromArray(float arr[], int len, short int *imax){
    int i;
    float max = arr[0];
    for (i=1; i<len; i++){
        if (arr[i] > max){
            max = arr[i];
            if(imax!=NULL){
                *imax = i;
                // printf("\nimax is not null: %d",*imax);
            }
        }
    }
    return max;
}
char* needSpace(int target, int lmt){
    int digit=1;

    while(1){
        target = target/10;
        if(target<=0){
            break;
        }
        digit++;
    }

    char *space = (char*) malloc(2*sizeof(char));
    space[0] = ' ';
    int i=1;

    while(digit>lmt){
        space = (char*)realloc(space, (i+1)*sizeof(char));

        space[i] = ' ';
        i++;
        digit--;
    }
    space[i] = '\0';
    //printf("\nNeedspace is '%s' ",space);

    return space;
}
int countMax(float target[], int len, short int *imax){
    int count=0, i;

    for(i=0; i<len; i++){
        if(target[i]==target[*imax]){
            count++;
            // printf("\nGot count2 = %d",count2);
        }
    }

    if(count==1){
        return 0;
    }
    else if(count==2){
        printf("\n\n-> The data set is Bimodal, there are two modes that appear with the same Highest frequency.");
        return 1;
    }
    else if(count>2 && count<len-1){
        printf("\n\n-> The data set is Multimodal, there are more than two modes that share the Highest frequency.");
        return 1;
    }
    else {
        printf("\n\n-> There is No mode because, all values appear with the same frequency.");
        return 1;
    }
}


int get_input(int CTtype) {   //CTtype == Central tendency type
    int opt, len, check=1, i;

    printf("\nEnter N (Number of elements) =>");
    check = scanf("%d",&len);
    if(len<=0 || check==0){
        printf("\nYou can only enter natural numbers.");
        return -1;
    }

    float xi[len];
    printf("\nIs your data grouped into Class intervals?");
    opt = YorN();
    

    if(opt==1){
        float class[len][2], fi[len];
        char sign;

        printf("\n\nEnter class intervals (e.g. 10-20 OR 10 20) :\n");
        for(i=0; i<len; i++){
            restart:
            printf("Class %d =>", i+1);

            check = scanf("%f%c%f", &class[i][0], &sign, &class[i][1]);
            if((check==2 && (sign==' ' || sign=='-')) || check!=3){
                printf("\nInvalid input!\n");
                while(getchar()!='\n');
                goto restart;
            }
            if(class[i][0]>=class[i][1]){
                printf("\nLower limit can't be greater than or same as Upper limit.\n");
                goto restart;
            }
            if(sign!=' ' && sign!='-'){
                printf("\nInvalid Sign!\n");
                goto restart;
            }
            if(i>0 && class[i-1][1]!=class[i][0]){
                printf("\nInvalid Class, see the Upper limit of last one(class %d).\n", i);
                goto restart;
            }
            while(getchar()!='\n');
        }
        
        printf("\n\nEnter Frequency (fi):\n");
        for(i=0; i<len; i++){
            restart2:
            printf("No%2d =>",i+1);
            if(scanf("%f",&fi[i])==0){
                printf("Invalid input in Frequency!\n\n");
                goto restart2;
            }
            if(fi[i]<0){
                printf("Frequency can't be Negative.\n\n");
                goto restart2;
            }
        }

        if(CTtype==1){
            findMean(len, class, fi, xi, 1);  //Mean method 1
        }
        else if(CTtype==2){
            findMedian(len, class, fi, xi, 1);   //Medium method 1
        }
        else {
            findMode(len, class, fi, xi, 1);    //Mode method 1
        }  

    }
    else if(opt==2){
        printf("\nDoes your distribution have frequency(Fi)?");
        opt = YorN();

        if(opt==1){
            float fi[len];

            printf("\n\nEnter the value of Xi :\n");
            for(i=0; i<len; i++){
                restart3:
                printf("No%2d =>",i+1);
                if (scanf("%f", &xi[i]) == 0){
                    printf("Invalid input for Xi.\n\n");
                    while(getchar()!='\n');
                    goto restart3;
                }
            }

            printf("\n\nEnter frequency (Fi) :\n");
            for (i = 0; i<len; i++){
                restart4:
                printf("No%2d =>", i + 1);
                if (scanf("%f", &fi[i]) == 0){
                    printf("Invalid input in Frequency!\n\n");
                    while(getchar()!='\n');
                    goto restart4;
                }
                if(fi[i]<0){
                    printf("Frequency can't be Negative.\n\n");
                    goto restart4;
                }
            }

            if(CTtype==1){
                findMean(len, NULL, fi, xi, 2);  //Mean Method 2
            }
            else if(CTtype==2){
                findMedian(len, NULL, fi, xi, 2);  //Medium method 2
            }
            else {
                findMode(len, NULL, fi, xi, 2);   //Mode method 2
            }

        }
        else if(opt==2) {
            printf("\n\nEnter the value of Xi :\n");

            for(i = 0; i<len; i++){
                restart5:
                printf("No%2d =>",i+1);
                if (scanf("%f", &xi[i]) == 0){
                    printf("Invalid input for Xi.\n\n");
                    while(getchar()!='\n');
                    goto restart5;
                }
            }

            if(CTtype==1){
                findMean(len, NULL, NULL, xi, 3);  //Mean Method 3
            }
            else if(CTtype==2){
                findMedian(len, NULL, NULL, xi, 3);  //Medium method 3
            }
            else {
                findMode(len, NULL, NULL, xi, 3);   //Mode method 3
            }

        }
        else {
            printf("\nInvalid Option!");
            return -1; //error
        }
    }
    else {
        printf("\nInvalid Option!");
        return -1; //error
    }
    return 0;
}


int findMean(int n, float classRange[][2], float fi[], float xi[], int mtype){  //mtype == Mean Method type
    int i, j, meanType=0;
    float ans=0;

    char *space1 = NULL;
    char *space2 = NULL;
    char *space3 = NULL;
    char *space4 = NULL;
    char *space5 = NULL;

    if(mtype==1){    //method type == Class and fi
        float Sfi=0;
        
        for(i=0; i<n; i++){
            xi[i] = (classRange[i][0]+classRange[i][1])/2;
            Sfi+=fi[i];
        }

        meanType = getMeanType(); //Getting Mean type from user
        if(meanType==-1){
            float maxFi = MaxfromArray(fi, n, NULL);
            float maxXi = (classRange[n-1][0]+classRange[n-1][1])/2;
            float maxDi = maxXi - (classRange[n/2-1][0]+classRange[n/2-1][1])/2;

            if(maxFi*maxDi>=150000){
                // printf("\nBecause, maxFi*maxDi(%.f)>=300000.",maxFi*maxDi);
                meanType = 3;
            }
            else if(maxFi*maxXi>=50000){
                // printf("\nBecause, maxFi*maxXi(%.f)>=100000.",maxFi*maxXi);
                meanType = 2;
            }
            else {
                meanType = 1;
            }
        }

        if(meanType==1){

            printf("\n\n<-- Direct Method -->");
            float fixi[n], Sfixi=0;
            for(i=0; i<n; i++){
                fixi[i] = xi[i]*fi[i];
                Sfixi+=fixi[i];
            }

            //Print Class, fi, xi, fixi
            if(tableMode){
                space1 = needSpace(classRange[n-1][0], 4);
                space2 = needSpace(classRange[n-1][1], 4);
                space3 = needSpace(MaxfromArray(fi, n, NULL), 6);
                space4 = needSpace(MaxfromArray(xi, n, NULL), 6);

                printf("\n\n%s--Class--%s  --Fi--%s  --Xi--%s  --Fixi--", space1, space2, space3, space4);
                for (i = 0; i < n; i++){
                    printf("\n %4.f-%-4.f   %6.f   %6.f   %8.f", classRange[i][0], classRange[i][1], fi[i], xi[i], fixi[i]);
                }
            }

            printf("\n\n=> Mean = Efixi/Efi");
            printf("\n\n        = %.2f/%.2f", Sfixi, Sfi);

            ans = Sfixi/Sfi;
        }
        else if(meanType==2) {
            printf("\n\n<-- Assumed Mean(Shortcut) Method -->");
            float di[n], fidi[n], Sfidi=0;
            
            float A = xi[n/2];
            for(i=0; i<n; i++){
                di[i] = xi[i]-A;
                fidi[i] = (float)fi[i]*di[i];
                Sfidi+=fidi[i];
            }

            //Print Class, fi, xi, di, fidi
            if(tableMode){
                space1 = needSpace(classRange[n-1][0], 4);
                space2 = needSpace(classRange[n-1][1], 4);
                space3 = needSpace(MaxfromArray(fi, n, NULL), 6);
                space4 = needSpace(MaxfromArray(xi, n, NULL), 6);
                space5 = needSpace(MaxfromArray(di,n, NULL), 6);
    
                printf("\n\n%s--Class--%s  --Fi--%s  --Xi--%s  --di--%s   --Fidi--",space1,space2,space3,space4,space5);
                for (i = 0; i < n; i++){
                    printf("\n %4.f-%-4.f   %6.f   %6.f   %6.f    %8.f", classRange[i][0],classRange[i][1], fi[i], xi[i], di[i], fidi[i]);
                }
            }

            printf("\n\n=> Mean = A + Efidi/Efi");
            printf("\n\n        = %.0f + (%.2f/%.2f)", A, Sfidi, Sfi);
            ans = (A + (Sfidi/Sfi));
        }
        else if(meanType==3){
            printf("\n\n<-- Step Deviation Method -->");
            float ui[n], fiui[n], Sfiui=0;
            float h = classRange[n/2][1]-classRange[n/2][0];
            
            float A = xi[n/2];
            for(i=0; i<n; i++){
                ui[i] = (xi[i]-A)/h;
                fiui[i] = fi[i]*ui[i];
                Sfiui+=fiui[i];
            }
            
            //Print Class, fi, xi, ui, fiui
            if(tableMode){
                space1 = needSpace(classRange[n-1][0], 4);
                space2 = needSpace(classRange[n-1][1], 4);
                space3 = needSpace(MaxfromArray(fi, n, NULL), 6);
                space4 = needSpace(MaxfromArray(xi, n, NULL), 6);
                space5 = needSpace(MaxfromArray(ui,n, NULL), 6);
    
                printf("\n\n%s--Class--%s  --Fi--%s  --Xi--%s  --ui--%s   --Fiui--",space1,space2,space3,space4,space5);
                for (i = 0; i < n; i++){
                    printf("\n %4.f-%-4.f   %6.f   %6.f   %6.f    %8.f", classRange[i][0],classRange[i][1], fi[i], xi[i], ui[i], fiui[i]);
                }
            }

            printf("\n\n=> Mean = A + (Efiui/Efi) x h");
            printf("\n\n        = %.0f + (%.2f/%.2f) x %.0f", A, Sfiui, Sfi, h);
            ans = (A + (Sfiui/Sfi)*h);
        }
        
    }
    else if(mtype==2){    //Method type = xi & fi
        float Sfi=0;

        for(i=0; i<n; i++){
            Sfi+=fi[i];
        }

        meanType = getMeanType(); //Getting Mean type from user
        if(meanType==-1){
            float maxFi = MaxfromArray(fi, n, NULL);
            float maxXi = MaxfromArray(xi, n, NULL);
            float maxDi = maxXi - xi[n/2-1];

            if(Sfi*maxDi*0.2>=300000){
                // printf("\nSfi x maxDi x 0.2 = %.f x %.f x 0.2 = %.f >= 300000.",Sfi,maxDi, Sfi*maxDi*0.2);
                meanType = 3;
            }
            else if(Sfi*maxDi*0.2>=100000){
                // printf("\nSfi x maxDi x 0.2 = %.f x %.f x 0.2 = %.f >= 100000.",Sfi,maxDi, Sfi*maxDi*0.2);
                meanType = 2;
            }
            else {
                meanType = 1;
            }
        }

        if(meanType==1){
            float fixi[n], Sfixi;

            printf("\n\n<-- Direct Method -->");
            for(i=0; i<n; i++){
                fixi[i] = xi[i]*fi[i];
                Sfixi += fixi[i];
            }

            //Print Xi, fi, fixi
            if(tableMode){
                space1 = needSpace(MaxfromArray(xi,n, NULL), 6);
                space2 = needSpace(MaxfromArray(xi,n, NULL), 6);
                space3 = needSpace(MaxfromArray(fi,n, NULL), 6);
    
                printf("\n\n%s--Xi--%s  --Fi--%s  --Fixi--",space1,space2,space3);
                for (i = 0; i < n; i++){
                    printf("\n %6.f   %6.f   %8.f",xi[i], fi[i], fixi[i]);
                }
            }
            

            printf("\n\n=> Mean = Efixi/Efi");
            printf("\n\n        = %.2f/%.2f", Sfixi, Sfi);

            ans = Sfixi/Sfi;
        }
        else if(meanType==2){
            printf("\n\n<-- Assumed Mean(Shortcut) Method -->");
            float di[n], A = xi[n/2], fidi[n], Sfidi=0;
            
            for(i=0; i<n; i++){
                di[i] = xi[i]-A;
                fidi[i] = (float)fi[i]*di[i];
                Sfidi+=fidi[i];
            }

            //Print Xi, fi, di, fidi
            if(tableMode){
                space1 = needSpace(MaxfromArray(xi,n, NULL), 6);
                space2 = needSpace(MaxfromArray(xi,n, NULL), 6);
                space3 = needSpace(MaxfromArray(fi,n, NULL), 6);
                space4 = needSpace(MaxfromArray(di,n, NULL), 6);
    
                printf("\n\n%s--Xi--%s  --Fi--%s  --di--%s  --Fidi--",space1,space2,space3,space4);
                for (i = 0; i < n; i++){
                    printf("\n %6.f   %6.f   %6.f   %8.f",xi[i], fi[i], di[i], fidi[i]);
                }
            }

            printf("\n\n=> Mean = A + Efidi/Efi");
            printf("\n\n        = %.0f + %.2f/%.2f", A, Sfidi, Sfi);
            ans = (A + (Sfidi/Sfi));
        }
        else if(meanType==3){
            printf("\n\n<-- Step Deviation Method -->");
            float ui[n], fiui[n], Sfiui=0;
            int h = xi[(n/2)+1]-xi[n/2];
            
            float A = xi[n/2];
            for(i=0; i<n; i++){
                ui[i] = (xi[i]-A)/h;
                fiui[i] = fi[i]*ui[i];
                Sfiui+=fiui[i];
            }

            //Print Xi, fi, ui, fiui
            if(tableMode){
                space1 = needSpace(MaxfromArray(xi,n, NULL), 6);
                space2 = needSpace(MaxfromArray(xi,n, NULL), 6);
                space3 = needSpace(MaxfromArray(fi,n, NULL), 6);
                space4 = needSpace(MaxfromArray(ui,n, NULL), 6);
    
                printf("\n\n%s--Xi--%s  --Fi--%s  --ui--%s  --Fiui--",space1,space2,space3,space4);
                for (i = 0; i < n; i++){
                    printf("\n %6.f   %6.f   %6.f   %8.f", xi[i], fi[i], ui[i], fiui[i]);
                }
            }
            
            printf("\n\n=> Mean = A + (Efiui/Efi) x h");
            printf("\n\n        = %.0f + (%.2f/%.2f) x %d", A, Sfiui, Sfi, h);
            ans = (A + (Sfiui/Sfi)*h);
        }

    }
    else if(mtype==3) {  //Method type == Only Xi
        float Sxi=0;
        for(i=0; i<n; i++){
            Sxi+=xi[i];
        }

        if(tableMode){
            char* space1 = needSpace(MaxfromArray(xi,n, NULL),8);
    
            printf("\n\n%s---Xi---",space1);
            for(i=0; i<n; i++){
                printf("\n %5.f",xi[i]);
            }
            free(space1);
        }

        printf("\n\n=> Mean = Exi/N");
        printf("\n\n        = %.2f/%d", Sxi, n);
        ans = (float)Sxi/n;

    }
    else {
        printf("\n\nUnknown Error!");
        return -1;
    }
    free(space1);
    free(space2);
    free(space3);
    free(space4);
    free(space5);

    printf("\n\n        = %.4f",ans);
    return 0;
}


int findMedian(int n, float ClassInterval[][2], float fi[], float xi[], int MethodType){
    int i, j;
    float ans=0;

    char* space1 = NULL;
    char* space2 = NULL;
    char* space3 = NULL;

    if(MethodType==1){
        float Cfi[n], Sfi=0;
        float l, f, cf, h; 

        printf("\n\n<-- Median from Class interval -->");

        for(i=0; i<n; i++){
            if(i==0){
                Cfi[0] = fi[0];
            }
            else {
                Cfi[i] = Cfi[i-1] + fi[i];
            }
            Sfi+=fi[i];
        }

        for(i=0; i<n; i++){
            if(Cfi[i]>Sfi/2){
                l = ClassInterval[i][0];
                cf = (i == 0) ? 0 : Cfi[i-1];
                f = fi[i];
                h = ClassInterval[i][1]-ClassInterval[i][0];
                break;
            }
        }

        //print Class, fi, cfi
        if(tableMode){
            space1 = needSpace(ClassInterval[n-1][0], 4);
            space2 = needSpace(ClassInterval[n-1][1], 4);
            space3 = needSpace(MaxfromArray(fi,n,NULL), 5);
    
            printf("\n\n%s--Class--%s    --Fi--%s    --Cfi--", space1, space2, space3);
            for(i=0; i<n; i++){
                if(Cfi[i]==cf){
                    printf("\n %4.f-%-4.f     %4.f       %4.f  <- Cf", ClassInterval[i][0], ClassInterval[i][1], fi[i], Cfi[i]);
                }
                else {
                    printf("\n %4.f-%-4.f     %4.f       %4.f", ClassInterval[i][0], ClassInterval[i][1], fi[i], Cfi[i]);
                }
            }
        }


        printf("\n\n=> Median = l + (n/2 - Cf)/f X h");
        printf("\n\n          = %.f + (%.f-%.f)/%.f X %.f", l, Sfi/2, cf, f, h);
        printf("\n\n          = %.f + %.2f", l, ((Sfi/2) - cf)/f*h);

        ans = l + ((Sfi/2) - cf)/f*h;
    }
    else if(MethodType==2){
        float Cfi[n], Sfi=0;
        float l, f, cf, h, temp; 
        int j;

        printf("\n\n<-- Median from Xi and Fi -->");

        for(i=0; i<n-1; i++)
        {
            for(j=0; j<n-i-1; j++){       //Arranging Data in ascending order
                if(xi[j]>xi[j+1]){
                    temp = xi[j];
                    xi[j] = xi[j+1];
                    xi[j+1] = temp; 

                    temp = fi[j];
                    fi[j] = fi[j+1];
                    fi[j+1] = temp; 
                }
            }
        }

        for(i=0; i<n; i++){
            if(i==0){
                Cfi[0] = fi[0];
            }
            else {
                Cfi[i] = Cfi[i-1] + fi[i];  //Calculating Cfi
            }
            Sfi+=fi[i];
        }
        for(i=0; i<n; i++){     //Find Cf from Cfi
            if(Cfi[i] > (Sfi+1)/2){
                cf = Cfi[i];
                ans = xi[i];
                break;
            }
        }

        //print Xi, fi, cfi
        if(tableMode){
            space1 = needSpace(MaxfromArray(xi,n, NULL), 6);
            space2 = needSpace(MaxfromArray(xi,n, NULL), 6);
            space3 = needSpace(MaxfromArray(fi,n, NULL), 6);
    
            printf("\n\n%s--Xi--%s   --Fi--%s   --Cfi--", space1, space2,space3);
            for(i=0; i<n; i++){
                if(Cfi[i] == cf){
                    printf("\n %6.f    %6.f    %7.f  <- Cf", xi[i], fi[i], Cfi[i]);
                }
                else {
                    printf("\n %6.f    %6.f    %7.f", xi[i], fi[i], Cfi[i]);
                }
            }
        }


        printf("\n\n=> Median = Xi of (N+1/2) in Cfi,");
        printf("\n\n          = (%.f+1/2) in Cfi,", Sfi);
        printf("\n\n          = %.f value in Cfi,",(Sfi+1)/2);

        printf("\n\n          = Since the %.f falls under the Cf(%.f),", (Sfi+1)/2, cf);
        printf("\n\n          = The median value is the corresponding of Cf(%.f)",cf);

    }
    else if(MethodType==3){

        sortingArray(xi, n);
        printf("<--- Median from raw data --->");

        // Printing Xi
        if(tableMode){
            space1 = needSpace(MaxfromArray(xi,n, NULL),6);

            printf("\n\n%s--Xi--",space1);
            for(i=0; i<n; i++){
                printf("\n %4.f",xi[i]);
            }
        }

        if(n%2==0){     //Checking, even OR odd
            printf("\n\n=> Median = [(n/2) th + (n/2)+1 th]/2  Term");
            printf("\n\n          = [(%d/2)th + (%d/2 +1)th]/2  Term", n, n);
            printf("\n\n          = [%.0f + %.0f]/2", xi[(n/2)-1], xi[(n/2)]);

            ans = (xi[(n/2)-1] + xi[(n/2)])/2;
        }
        else {
            printf("\n\n=> Median = (n+1)/2 th Term");
            printf("\n\n          = %dth Term", (n+1)/2);

            ans = xi[((n+1)/2)-1];
        }
    }
    else {
        return -1;
    }

    free(space1);
    free(space2);
    free(space3);

    printf("\n\n          = %.4f",ans);
    return 0;
}


int findMode(int n, float ClassInterval[][2], float fi[], float xi[], int MethodType){
    float ans =0;
    char* space1 = NULL;
    char* space2 = NULL;
    
    if(MethodType==1){
        short int imax=0;
        float f1 = MaxfromArray(fi, n, &imax);
        float f0 = fi[imax-1];
        float f2 = fi[imax+1];

        if(countMax(fi, n, &imax)==1){
            return 1;
        }

        if(imax==0){
            printf("\n*Unable to find f0 for MODE because f1(Modal Class) is the 1st value of the data.");
            printf("\n\nDo you want to continue as f0=0 ?");
            if(YorN()==1){
                f0 = 0;
            }
            else {
                return 1;
            }
        }
        else if(imax==n-1){
            printf("\n*Unable to find f2 for MODE because f1(Modal Class) is the Last value of the data.");
            printf("\n\nDo you want to continue as f2=0 ?");
            if(YorN()==1){
                f2 = 0;
            }
            else {
                return 1;
            }
        }

        printf("\n\n<-- Mode from Grouped Data -->");

        //Print Class and Fi
        if(tableMode){
            int i;
            char *sign;
            space1 = needSpace(ClassInterval[n-1][0], 4);
            space2 = needSpace(ClassInterval[n-1][1], 4);

            printf("\n\n%s--Class--%s  --Fi--", space1, space2);

            for (i=0; i<n; i++){
                if(i == imax-1){
                    sign = "<-- f0";
                }
                else if(i == imax){
                    sign = "<-- f1 (Modal class)";
                }
                else if(i == imax+1){
                    sign = "<-- f2";
                }
                else {
                    sign = " ";
                }
                printf("\n %4.f-%-4.f    %4.f    %s", ClassInterval[i][0], ClassInterval[i][1], fi[i], sign);
            }
        }    

        float l = ClassInterval[imax][0];
        float h = ClassInterval[imax][1] - ClassInterval[imax][0];

        printf("\n\n=> Z = l + (F1-F0)/(2F1-F0-F2) x h");
        printf("\n\n     = %.f + (%.f-%.f) / 2(%.f)-%.f-%.f  X  %.f", l, f1, f0, f1, f0, f2, h);
        printf("\n\n     = %.2f + %.2f", l, (f1-f0)/(2*f1-f0-f2)*h);

        ans = l + (f1-f0)/(2*f1-f0-f2) * h;
    }
    else if(MethodType==2){
        short int imax=0;
        float f1 = MaxfromArray(fi, n, &imax);

        if(countMax(fi, n, &imax)==1){
            return 1;
        }

        printf("\n\n<-- Mode from Xi and Fi -->");

        //print Xi and Fi
        if(tableMode){
            int i;
            char *sign;
            space1 = needSpace(MaxfromArray(xi,n, NULL), 8);
            space2 = needSpace(MaxfromArray(xi,n, NULL), 8);

            printf("\n\n%s---Xi---%s   ---Fi---",space1,space2);
            for(i=0; i<n; i++){
                if(i == imax){
                    sign = "<-- Mode";
                }
                else {
                    sign = " ";
                }
                printf("\n %8.f   %8.f  %s",xi[i], fi[i], sign);
            }
        }

        printf("\n\n=> Z = The value(Xi) with the highest frequency");
        printf("\n\n     = The highest frequency is %.f, which corresponds to the value %.f", f1, xi[imax]);

        ans = xi[imax];
    }
    else if(MethodType==3){
        short int i, j, len=0, imax=0;
        float value[n];
        int count[n];
        printf("\n\n<-- Mode for Raw data -->");

        sortingArray(xi, n);  //sorting Array/Values       
        for(i=0; i<n; i++){    //Counting the same numbers (Which is frequently appearing)
            if(xi[i]!=value[len-1] || i==0){
                value[len]=xi[i];
                count[len]=0;

                for(j=i; j<n; j++){       
                    if(value[len]==xi[j]){
                        count[len]++;
                    }
                    else {
                        break;
                    }
                }
                len++;
            }
        }

        MaxfromArray((float*)count, len, &imax);

        if(tableMode){
            space1 = needSpace(MaxfromArray(xi,n, NULL),9);

            printf("\n\n --Value--%s   --Count--",space1);
            for(i=0; i<len; i++){
                printf("\n %8.f    %8d",value[i], count[i]);
            }
        }

        if(countMax((float*)count, len, &imax)==1){
            return 1;
        }

        ans = value[imax];
    }
    else {
        printf("\nUnknown Error!");
        return -1;
    }

    free(space1);
    free(space2);

    printf("\n\n     = %.4f",ans);
    return 0;
}
