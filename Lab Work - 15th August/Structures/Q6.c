#include <stdio.h>

typedef struct Date{
    int day;
    int month;
    int year;
}Date;

int is_leap_year(int year) {
    if(year % 100 == 0) {
        if(year % 400 == 0)
            return 1;
        else
            return 0;
    }
    else if(year % 4 == 0)
        return 1;
    else
        return 0;
}

int is_valid_date(Date date) {
    if(date.month <= 7) {
        if(date.month == 2) {
            if(is_leap_year(date.year)) {
                if(date.day > 29)
                    return 0;
            }
            else if(date.day > 28)
                return 0;
        }
        else {
            if(date.month % 2 && date.day > 31)
                return 0;
            else if(date.month % 2 == 0 && date.day > 30)
                return 0;
        }
    }
    else {
        if(date.month % 2 && date.day > 30)
            return 0;
        else if(date.month % 2 == 0 && date.day > 31)
            return 0;
    }

    return 1;
}

int main () {
    Date date;
    printf("Enter the day: ");
    scanf("%d", &date.day);
    printf("Enter the month: ");
    scanf("%d", &date.month);
    printf("Enter the year: ");
    scanf("%d", &date.year);

    printf("The date you entered is %02d/%02d/%d\n", date.day, date.month, date.year);
    if(is_valid_date(date))
        printf("It is a valid date");
    else
        printf("It is an invalid date");

    return 0;
}