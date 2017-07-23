#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
    int month, day, yearday, ret;
    
    ret = day_of_year(2015, 13, 1);
    printf("13th month exists? %d\n", ret);
    
    ret = day_of_year(2015, 1, 32);
    printf("32nd day exists? %d\n", ret);
    
    month_day(2015, 370, &month, &day);
    printf("370th yearday exists? day = %d, month = %d\n", day, month);
 
    ret = day_of_year(1981, 1, 1);
    printf("1st day of 1st month exists? %d\n", ret);
    
    ret = day_of_year(2015, 12, 31);
    printf("31st of 12th month exists? %d\n", ret);
    
    month_day(2015, 90, &month, &day);
    printf("90th day of year exists? day = %d, month = %d\n", day, month);
    

    return 0; 
}

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (month < 1 || month > 12)
        return -1;
    else {
        if (day < 1 || day > daytab[leap][month])
            return -1;
    }

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap, days;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    days = 0;
    for (i = 1; daytab[leap][i]; i++)
        days += daytab[leap][i];

    if (yearday > days) {
        *pmonth = 0;
        *pday = 0;
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
