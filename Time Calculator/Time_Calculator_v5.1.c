#include <stdio.h>
#include <time.h>

int Psec, Pmin, Phour, Pday, Pmonth, Pyear;
void Ptime();
int askTime();

int checkTime(int *hour, int *min);
int check1(int d, int m, int y);
int check2(int y[2], int m[2], int d[2], int h[2], int min[2], int isTime);

int Tdays_finder(int day[2], int month[2], int year[2]);


int main()
{
    Ptime();
    const int century = Pyear/100;

    int isTime = askTime();
    int hour[2]= {0};
    int min[2]= {0};

    int day[2], month[2], year[2];
    int i=0;

    while(i<=1)
    {
        if(i==0) {
            printf("\n*Tip: You can enter any character to Autofill current date OR time.");
            printf("\n\nFROM (DD/MM/YYYY) =>");
        }
        else {
            printf("\n\nTO (DD/MM/YYYY) =>");
        }

        if(scanf("%2d/%2d/%4d",&day[i],&month[i],&year[i])!=3) {    //Getting date from user
            while(getchar()!='\n'); //Cleaning other invalid characters until '\n'
            // Setting up default values
            day[i] = Pday;
            month[i] = Pmonth;
            year[i] = Pyear;
        }
        if(year[i]<=(Pyear-century*100) && year[i]>=1) {      //Auto guess the year if not in format(4 digit)
            year[i] = year[i]+century*100;
        }
        else if(year[i]<=99 && year[i]>0) {         //Auto guess the year if not in format(4 digit)
            year[i] = year[i]+(century-1)*100;
        }

        if(isTime==1){       //Getting time as an input from User
            printf("TIME (24-hour format in HH:MM) =>");
            if(scanf("%2d:%2d",&hour[i], &min[i])==0){
                while(getchar()!='\n');
                hour[i]=Phour;
                min[i]=Pmin;
            }
        }

        if(check1(day[i], month[i], year[i])){       //Check for valid date(in year, month and day)
            return 1;
        }

        if(isTime==1 && checkTime(&hour[i], &min[i])){     //Check for Valid Time (in hour and minutes)
            return 1;
        }
        i++;
    }
    
    if(check2(year, month, day, hour, min, isTime)){        //Lastly, Check all details for 'Proper Range-validation'
        printf("\n\n*Error: Date and Time can't be the same as or earlier than the FROM!\n");
        return 1;
    }
    
    int mDay[12] = {31, (28 + is_leap(year[1])), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   //Pre-defined days for each months
    int ageY = year[1]-year[0];
    int ageM = month[1]-month[0];
    int ageD = day[1]-day[0];

    int ageH = hour[1]-hour[0];
    int ageMin = min[1]-min[0];

    int Tday = Tdays_finder(day, month, year);   //find total days
    
    if(ageMin<0){
        ageMin = 60 + ageMin;   //ex. 60 + (-10)
        ageH--;
    }
    if(ageH<0){
        ageH = 24 + ageH;   //ex. 24 + (-21)
        ageD--;
        Tday--;
    }
    if(ageD<0){
        ageD = mDay[month[1]] + ageD;   //ex. 31 + (-13)
        ageM--;
    }
    if(ageM<0){
        ageM = 12 + ageM;   //ex. 12 + (-3)
        ageY--;
    }
    
    int Tmonth = (ageY*12) + ageM;    //Total months
    int Thour = Tday*24 + ageH;    //Total hours
    int Tmin = Thour*60 + ageMin;    //Total minutes

    printf("\n\nCalculated Date & Time :\n\n");
    short int pass=0;
    i=1;
    
    while(i <= 5)    //Loop to Print the Calculations
    {
        if(i==1 && ageY>0 ){
            if(isTime==1){
                printf("%d Years, %d Months, %d days and %d Hours", ageY, ageM, ageD, ageH);
            }
            else {
                printf("%d Years, %d Months and %d days", ageY, ageM, ageD);
            }
            pass=1;
        }
        if(i==2 && Tmonth>0){
            if(isTime==1){
                printf("%d Months, %d Days, %d Hours", Tmonth, ageD, ageH);
            }
            else {
                printf("%d Months and %d Days", Tmonth, ageD);
            }
            pass=1;
        }
        if(i==3 && Tday>0){
            if(isTime==1){
                printf("%d Days and %d Hours", Tday, ageH);
            }
            else {
                printf("%d Days", Tday);
            }
            pass=1;
        }
        if(i==4 && Thour>0){
            if(isTime==1){
                printf("%d Hours and %d Minutes", Thour, ageMin);
            }
            else {
                printf("%d Hours", Thour);
            }
            pass=1;
        }
        if(i==5){
            printf("%d Minutes", Tmin);
            break;   //Break the loop after printing Last row (Minutes)
        }
        if(pass==1){
            printf("\nOR ");
        }
        i++;
    }
    
    printf("\n\n\n*Note: Total days calculation follows business standard (end date is excluded).\n");
    return 0;
}



//--------------Functions Used in this program---------------

void Ptime() {  //The only thing done with the help of AI.
    time_t current_time = time(NULL);

    struct tm *local = localtime(&current_time);

    Psec = local->tm_sec;
    Pmin = local->tm_min;
    Phour = local->tm_hour;
    Pday = local->tm_mday;
    Pmonth = local->tm_mon+1; // To start index from 1 
    Pyear = local->tm_year+1900;

    printf("Time: %02d:%02d\n", Phour, Pmin);
    printf("Date: %02d-%02d-%04d\n", Pday, Pmonth, Pyear);
}

int askTime(){    //Ask user, if calculate with time
    int opt=0;

    printf("\n\nChoose your options :");
    printf("\n1. Normal (only days)");
    printf("\n2. Advanced (with time)");

    printf("\n\nEnter option =>");
    if(scanf("%d",&opt)==0){
        printf("Invalid option, Auto selected Normal.\n");
        opt=1;
    }
    while(getchar()!='\n');

    if(opt!=1 && opt!=2){
        printf("Invalid option, Auto selected Normal.\n");
        opt=1;
    }
    return opt-1;
}

int is_leap(int year) {     //If the year is Leap year
    
    if(year%400 == 0) {
        return 1;
    } 
    else if(year%4 == 0 && year%100 != 0){
        return 1;
    }
    
    return 0;
}


int checkTime(int *hour, int *min){     //Validating Time, entered by user

    if (*hour>23 || *hour<0){
        printf("\nInvalid Hour!");
        return 1;
    }
    if (*min<0 || *min>=60){
        printf("\nInvalid Minutes!");
        return 1;
    }

    printf("You entered: %02d:%02d\n", *hour, *min);
    return 0;
}

int check1(int day, int month, int year) {      //Validating Date

    if(month>12 || month<1) {
        printf("\nInvalid Month!\n");
        return 1;
    }
    if(year>Pyear+200 || year<Pyear-199) {
        printf("\nInvalid Year!");
        printf("\n*Please ensure that the year you entered is between %d and %d.\n", Pyear-199, Pyear+200);
        return 1;
    }

    int leap = is_leap(year);
    int mDay[12] = {31, (28+leap), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   //Pre-defined days for each months

    if(day < 1 || day > mDay[month-1]){
        printf("\nInvalid Day!");
        return 1;
    }

    printf("\nYou entered: Day %02d, Month %02d, Year %4d\n",day, month, year);
    return 0;
}

int check2(int y[2], int m[2], int d[2], int h[2], int min[2], int isTime){

    if(y[1]<y[0]){
        return 1;
    }
    else if(y[1]==y[0] && m[1]<m[0]){
        return 1;
    }
    else if(y[1]==y[0] && m[1]==m[0] && d[1]<d[0]){
        return 1;
    }
    else if(isTime==0 && y[1]==y[0] && m[1]==m[0] && d[1]==d[0]){
        return 1;
    }
    else {
        if(y[1]==y[0] && m[1]==m[0] && d[1]==d[0] && h[1]<h[0]){
            return 1;
        }
        else if(y[1]==y[0] && m[1]==m[0] && d[1]==d[0] && h[1]==h[0] && min[1]<=min[0]){  
            return 1;
        }
    }

    return 0; //Successful if passed all checks
}

int Tdays_finder(int day[2], int month[2], int year[2]){        // Calculates total days between two dates
    int days=0;
    int mDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int d, d2, m, m2;
    int i, j;
    
    for(i=year[0]; i<=year[1]; i++) {
        m = 1;
        m2 = 12;
        mDay[1] = 28 + is_leap(i);
        
        if(i==year[0]){
            m = month[0];
        }
        if(i==year[1]){
            m2 = month[1];
        }
        
        for(j=m; j<=m2; j++){
            d = 0;
            d2 = mDay[j-1];
            
            if(j==m && i==year[0]){
                d = day[0];
            }
            if(j==m2 && i==year[1]){
                d2 = day[1];
            }
            
            days = days+d2-d;
            //printf("\nY=%4d, M=%02d, Days=%2d", i, j, days);
        }
    }
    
    return days;
}    
