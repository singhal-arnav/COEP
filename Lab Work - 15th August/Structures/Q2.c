#include <stdio.h>
#include <string.h>

typedef struct name {
    char first_name[20];
    char middle_name[20];
    char last_name[20];
}Name;

typedef struct marks {
    float english;
    float mathematics;
    float comp_sci;
}Marks;

typedef struct date {
    int day;
    int month;
    int year;
}Date;

typedef struct student{
    int roll_no;
    Name name;
    char gender;
    Date dob;
    Marks marks;
}Student;

int main() {
    Student students[] = {
        {12, {"Amit", "Ranjeet", "Agarwal"}, 'M', {25, 7, 2004}, {91, 77.5, 90}},
        {22, {"Bhumi", "Rajiv", "Bansode"}, 'F', {22, 4, 2004}, {57, 72, 80}},
        {35, {"Kirti", "Sachin", "Jadhav"}, 'F', {2, 10, 2004}, {95, 97, 90}},
        {45, {"Ninad", "Ashish", "Mehta"}, 'M', {15, 6, 2004}, {35, 47.5, 30}}
    };
    int i, flag = 0;
    char fname[20], mname[20], lname[20];

    printf("Enter the name to be searched: ");
    scanf("%s %s %s", fname, mname, lname);

    for(int i = 0; i < 4; i++) {
        if(!strcmp(fname, students[i].name.first_name) && !strcmp(mname, students[i].name.middle_name) && !strcmp(lname, students[i].name.last_name)) {
            flag = 1;
            printf("Name: %s %s %s\n", students[i].name.first_name, students[i].name.middle_name, students[i].name.last_name);
            printf("Roll No: %d\n", students[i].roll_no);
            printf("Gender: %c\n", students[i].gender);
            printf("Date of Birth: %02d/%02d/%d\n", students[i].dob.day, students[i].dob.month, students[i].dob.year);
            printf("Marks: English: %.2f | Mathematics: %.2f | Computer Science: %.2f\n\n", students[i].marks.english, students[i].marks.mathematics, students[i].marks.comp_sci);
            break;
        }
    }

    if(!flag)
        printf("Student not found\n\n");
    
    float aggregate;
    flag = 0;
    printf("Students who have secured less than 40%% of the aggregate:\n");
    for(int i = 0; i < 4; i++) {
        if((aggregate = (students[i].marks.english + students[i].marks.mathematics + students[i].marks.comp_sci) / 3.0) < 40) {
            flag = 1;
            printf("%s %s %s\t Aggregate = %.2f%%\n", students[i].name.first_name, students[i].name.middle_name, students[i].name.last_name, aggregate);
        }
    }
    if(!flag)
        printf("Nil");

    return 0;
}