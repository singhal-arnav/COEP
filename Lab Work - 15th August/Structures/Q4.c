#include <stdio.h>

typedef struct time {
    int hr;
    int min;
    int sec;
}time;

int cmp_time(time start_time, time end_time) { //return 0 if equal and 1 otherwise, assuming start_time < end_time
    if(start_time.hr < end_time.hr)
        return 1;
    else if(start_time.hr == end_time.hr) {
        if(start_time.min < end_time.min)
            return 1;
        else if(start_time.min == end_time.min) {
            if(start_time.sec < end_time.sec)
                return 1;
            else
                return 0;
        }
    }
}

void increment_time(time *t) {
    t -> sec += 1;
    if(t -> sec == 60) {
        t -> sec = 0;
        t -> min += 1;
        if(t -> min == 60) {
            t -> min = 0;
            t -> hr += 1;
            if(t -> hr == 24) { //assuming 24 hour time format
                t -> hr = 0;
            }
        }
    }
    return;
}

int main() {
    time start_time, end_time;

    printf("Enter the start time: ");
    scanf("%2d:%2d:%2d", &start_time.hr, &start_time.min, &start_time.sec);

    printf("Enter the end time: ");
    scanf("%2d:%2d:%2d", &end_time.hr, &end_time.min, &end_time.sec);

    while(cmp_time(start_time, end_time)) {
        printf("GOOD DAY\n");
        increment_time(&start_time);
    }

    return 0;
}