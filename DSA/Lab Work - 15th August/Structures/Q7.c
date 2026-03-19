#include <stdio.h>

typedef struct time {
    int hours;
    int minutes;
    int seconds;
}time;

time get_struct(int hours, int minutes, int seconds) {
    time t;
    t.hours = hours;
    t.minutes = minutes;
    t.seconds = seconds;
    return t;
}

time add_time(time t1, time t2) {
    time t;
    int carry = 0;
    t.seconds = t1.seconds + t2.seconds;
    if(t.seconds >= 60) {
        carry = 1;
        t.seconds = t.seconds % 60;
    }
    t.minutes = t1.minutes + t2.minutes + carry;
    carry = 0;
    if(t.minutes >= 60) {
        carry = 1;
        t.minutes = t.minutes % 60;
    }
    t.hours = t1.hours + t2.hours + carry;
    return t;
}

time subtract_time(time t1, time t2) {
    time t;
    int borrow = 0;
    t.seconds = t1.seconds - t2.seconds;
    if(t.seconds <= 0) {
        borrow = 1;
        t.seconds = 60 + t.seconds;
    }
    t.minutes = t1.minutes - t2.minutes - borrow;
    borrow = 0;
    if(t.minutes <= 0) {
        borrow = 1;
        t.minutes = 60 + t.minutes;
    }
    t.hours = t1.hours - t2.hours - borrow;
    return t;
}

void display_time(time t) {
    printf("%dhrs %dmins %dsec\n", t.hours, t.minutes, t.seconds);
    return;
}

int main() {
    time t1, t2, sum, diff;
    t1 = get_struct(10, 20, 50);
    t2 = get_struct(5, 30, 40);
    sum = add_time(t1, t2);
    diff = subtract_time(t1, t2);
    display_time(sum);
    display_time(diff);
    return 0;
}