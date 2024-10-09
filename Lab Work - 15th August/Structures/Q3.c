#include <stdio.h>
#include <stdlib.h>

typedef struct hotel {
    char name[50];
    char address[100];
    int grade;
    int rooms;
    int charges;
}hotel;

void printHotelsByGrade(hotel hotels[], int num, int grade) {
    int i, flag = 0;
    for(i = 0; i < num; i++) {
        if(hotels[i].grade == grade) {
            flag = 1;
            printf("%s\n", hotels[i].name);
        }
    }
    if(!flag)
        printf("No hotels in this grade / Invalid grade\n");
    return;
}

void printHotelsByRoomCharges(hotel hotels[], int num, int charges) {
    int i, flag = 0;
    for(i = 0; i < num; i++) {
        if(hotels[i].charges < charges) {
            flag = 1;
            printf("%s\n", hotels[i].name);
        }
    }
    if(!flag)
        printf("No hotels with room charges below this limit\n");
    return;
}

int main() {
    int num_hotels = 3, grade, charges;

    hotel hotels[] = {
        {"Hotel A", "123 Main St, City A", 3, 50, 2000},
        {"Hotel B", "456 Oak St, City B", 4, 75, 8000},
        {"Hotel C", "789 Pine St, City C", 5, 60, 20000}
    };

    printf("Enter the required grade: ");
    scanf("%d", &grade);
    printHotelsByGrade(hotels, num_hotels, grade);

    printf("Enter the limit for room charges: ");
    scanf("%d", &charges);
    printHotelsByRoomCharges(hotels, num_hotels, charges);

    return 0;
}