#include <stdio.h>

static char months_no_leap[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char months_leap[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char* daytab[2] = {months_no_leap, months_leap};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
    int month, day, yearday, year, ret;

    day = 15;
    month = 13;
    year = 1981;
    ret = day_of_year(year, month, day);
    printf("13th month exists? %d\n", ret);

    day = 32;
    month = 6;
    ret = day_of_year(year, month, day);
    printf("32nd day exists? %d\n", ret);

    day = 15;
    month = 1;
    ret = day_of_year(year, month, day);
    printf("15th of January 1981 valid? Day of year = %d\n", ret);

    yearday = 370;
    month_day(year, yearday, &month, &day);
    printf("370th yearday in 1981 exists? day = %d, month = %d\n", day, month);

    yearday = 15;
    month_day(year, yearday, &month, &day);
    printf("15th yearday in 1981 is on %d/%d/%d\n", day, month, year);


    return 0;
}

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int leap;
    char *p;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    p = daytab[leap];

    if (month < 1 || month > 12)
        return -1;
    else {
        if (day < 1 || day > p[month])
            return -1;
    }

    for ( ;--month; )
        day += *++p;

    return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap, days;
    char *p, *q;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    days = 0;
    q = daytab[leap];
    for (; *++q;)
        days += *q; 

    if (yearday > days) {
        *pmonth = 0;
        *pday = 0;
        return;
    }

    p = daytab[leap];
    for (; yearday > *++p; )
        yearday -= *p;

    *pmonth = p - *(daytab + leap);
    *pday = yearday;
}
