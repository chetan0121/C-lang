#include <stdio.h>
#include <time.h>
#define century 20    //21st Century - 1, for better understanding

int Psec, Pmin, Phour, Pday, Pmonth, Pyear;
void Ptime();
int askTime();

int checkTime(int *hour, int *min);
int check1(int d, int m, int y);
int check2(int y[2], int m[2], int d[2], int h[2], int min[2], short int isTime);

int Tdays_finder(int day[2], int month[2], int year[2]);


int main()
{
    Ptime();

    short int calcuTime = askTime();   //if 1 then find only days, if 2 then calculate it with time also.
    int hour[2]= {0};
    int min[2]= {0};

    int day[2], month[2], year[2];
    short int i=0;

    while(i<=1)
    {
        if(i==0) {
            printf("\n*Tip: You can enter any character to Autofill current date OR time.");
            printf("\n\nFROM (DD/MM/YYYY) =>");
        }
        else {
            printf("\n\nTO (DD/MM/YYYY) =>");
        }

        if(scanf("%2d/%2d/%4d",&day[i],&month[i],&year[i])!=3) {     //Getting days from user
            while(getchar()!='\n'); //Cleaning other invalid characters until '\n'
            
            day[i]=Pday;
            month[i]=Pmonth;
            year[i]=Pyear;
        }
        if(year[i]<=(Pyear-century*100) && year[i]>=1) {      //Auto guess the year if not in format(4 digit)
            year[i] = year[i]+century*100;
        }
        else if(year[i]<=99 && year[i]>0) {         //Auto guess the year if not in format(4 digit)
            year[i] = year[i]+(century-1)*100;
        }

        if(calcuTime==2){       //Getting time as an input from User
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

        if(calcuTime==2 && checkTime(&hour[i], &min[i])){     //Check for Valid Time (in hour and minutes)
            return 1;
        }
        i++;
    }
    
    if(check2(year, month, day, hour, min, calcuTime)){        //Lastly, Check all details for 'Proper Range-validation'
        printf("\n\n*Error: Date and Time can't be the same as or earlier than the FROM!\n");
        return 1;
    }
    
    int mDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   //Pre-defined the days for each months
    int ageY = year[1]-year[0];
    int ageM = month[1]-month[0];
    int ageD = day[1]-day[0];

    int ageH = hour[1]-hour[0];
    int ageMin = min[1]-min[0];

    if(ageMin<0){
        ageMin = 60 + ageMin;   //ex. 60 + (-10)
        ageH--;
    }
    if(ageH<0){
        ageH = 24 + ageH;   //ex. 24 + (-21)
        ageD--;
    }
    if(ageD<0){
        ageD = mDay[month[1]] + ageD;   //ex. 31 + (-13)
        ageM--;
    }
    if(ageM<0){
        ageM = 12 + ageM;   //ex. 12 + (-3)
        ageY--;
    }
    
    //No need to find Tyear, because AgeY will work as Tyear
    int Tmonth = (ageY*12)+ageM;    //Total months
    int Tday = Tdays_finder(day, month, year);   //finding the Total days
    int Thour = Tday*24 + ageH;    //Total hours
    int Tmin = Thour*60 + ageMin;    //Total minutes
    
      
    printf("\n\nCalculated Date & Time :\n\n");
    short int pass=0;
    i=1;
    
    while(1)    //Loop to Print the Calculations
    {
        if(ageY>0 && i==1){
            if(calcuTime==2){
                printf("%d Years, %d Months, %d days and %d Hours",ageY, ageM, ageD, ageH);
            }
            else {
                printf("%d Years, %d Months and %d days",ageY, ageM, ageD);
            }
            pass=1;
        }
        if(Tmonth>0 && i==2){
            if(calcuTime==2){
                printf("%d Months, %d Days, %d Hours",Tmonth, ageD, ageH);
            }
            else {
                printf("%d Months and %d Days",Tmonth, ageD);
            }
            pass=1;
        }
        if(i==3 && Tday>0){
            if(calcuTime==2){
                printf("%d Days and %d Hours",Tday, ageH);
            }
            else {
                printf("%d Days",Tday);
            }
            pass=1;
        }
        if(i==4 && Thour>0){
            if(calcuTime==2){
                printf("%d Hours and %d Minutes", Thour, ageMin);
            }
            else {
                printf("%d Hours", Thour);
            }
            pass=1;
        }
        if(i==5){
            printf("%d Minutes", Tmin);
            break;   //Break the loop after printing Last row(Minutes)
        }
        if(pass==1){
            printf("\nOR ");
        }
        i++;
    }
    
    printf("\n\n");
    return 0;
}



//--------------Functions Used in this program---------------

void Ptime() {  //The only thing done by the help of Ai
    time_t current_time = time(NULL);

    struct tm *local = localtime(&current_time);

    Psec = local->tm_sec;
    Pmin = local->tm_min;
    Phour = local->tm_hour;
    Pday = local->tm_mday;
    Pmonth = local->tm_mon+1;
    Pyear = local->tm_year+1900;

    printf("Time: %02d:%02d\n", Phour, Pmin);
    printf("Date: %02d-%02d-%04d\n", Pday, Pmonth, Pyear);
}

int askTime(){      //Ask user, what type of calculation needed
    short int opt=0;

    printf("\n\nChoose your options :");
    printf("\n1. Normal (only days)");
    printf("\n2. Advanced (with time)");

    printf("\n\nEnter option =>");
    if(scanf("%d",&opt)==0){
        printf("Invalid option, Auto selected Normal.\n");
        opt=1;
    }
    if(opt!=1 && opt!=2){
        printf("Invalid option, Auto selected Normal.\n");
        opt=1;
    }
    while(getchar()!='\n');

    return opt;
}

int is_leap(int year) {     //check if the year is Leap year or not
    int leap = 0;
    
    if(year%100==0){
        if((year/100) % 4 == 0){
            leap = 1;
        }
    }
    else if(year%4 == 0){
        leap = 1;
    }
    // printf("\n%d is Leap.",year);
    return leap;
}


int checkTime(int *hour, int *min){     //Validating Time, entered by user

    if (*hour>24 || *hour<0){
        printf("\nInvalid Hour!");
        printf(" ");
        return 1;
    }
    if (*min<0 || *min>=60){
        printf("\nInvalid Minutes!");
        return 1;
    }

    printf("You entered: %02d:%02d\n", *hour, *min);
    return 0;
}

int check1(int day, int month, int year) {      //Validating Date, entered by user

    if(month>12 || month<1) {
        printf("\nInvalid Month!\n");
        return 1;
    }
    if(year>Pyear+200 || year<Pyear-199) {
        printf("\nInvalid Year!");
        printf("\n*Please ensure that the year you entered is between %d and %d.\n",Pyear-199, Pyear+200);
        return 1;
    }

    int monthType=0;
    int leap = is_leap(year);

    switch(month) {
    case 1 :
    case 3 :
    case 5 :
    case 7 :
    case 8 :
    case 10:
    case 12:
        if(day>=1 && day<=31) {
            monthType = 31;
        }
        break;
        
    case 2 :
        if(leap==1 && day<=29 && day>=1) {
            monthType = 29;
        }
        else if(day<=28 && day>=1) {
            monthType = 28;
        }
        break;
        
    case 4 :
    case 6 :
    case 9 :
    case 11:
        if(day>=1 && day<=30) {
            monthType = 30;
        }
        break;
        
    default :
        printf("\nInvalid month in Case statement!\n");
        monthType = 1;
    }

    if(monthType == 0) {
        printf("\nInvalid Day!\n");
        return 1;
    }

    printf("\nYou entered: Day %02d, Month %02d, Year %4d\n",day, month, year);
    return 0;
}

int check2(int y[2], int m[2], int d[2], int h[2], int min[2], short int isTime){

    if(y[1]<y[0]){
        return 1;
    }
    else if(y[1]==y[0] && m[1]<m[0]){
        return 1;
    }
    else if(y[1]==y[0] && m[1]==m[0] && d[1]<d[0]){
        return 1;
    }

    if(isTime==1){       //All the date should not be same if user selected only days
        if(y[1]==y[0] && m[1]==m[0] && d[1]==d[0]){   
            return 1;
        }
    }
    else {
        if(y[1]==y[0] && m[1]==m[0] && d[1]==d[0] && h[1]<h[0]){
            return 1;
        }
        else if(y[1]==y[0] && m[1]==m[0] && d[1]==d[0] && h[1]==h[0] && min[1]<=min[0]){  
            return 1;
        }
    }

    return 0;
}
  

int Tdays_finder(int day[2], int month[2], int year[2]){        //function that finds total days

    int days=0; 
    int i, j;
    int d, d2, m, m2;
    int mDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    for(i=year[0]; i<=year[1]; i++)
    {
        m = 0;
        m2 = 11;
        mDay[1] = 28 + is_leap(i);   //Every time(year) check that the february has 28 days OR 29 days, so mDay[1] is the index of february.
        
        if(i==year[0]){
            m = month[0]-1;     //Did -1 because Array index starts from 0
        }
        if(i==year[1]){
            m2 = month[1]-1;     //Did -1 because Array index starts from 0
        }
        
        for(j=m; j<=m2; j++){
            d = 0;
            d2 = mDay[j];
            
            if(j==m && i==year[0]){
                d = day[0];
            }
            if(j==m2 && i==year[1]){
                d2 = day[1];
            }
            
            days = days+d2-d;   
            //printf("\nY=%4d, M=%02d, Days=%2d",i,j+1,days);
        }
    }
    
    return days;
}    