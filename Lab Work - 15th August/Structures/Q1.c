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
    Student student1;

    student1.roll_no = 45;
    strcpy(student1.name.first_name, "Arnav");
    strcpy(student1.name.middle_name, "Rajat");
    strcpy(student1.name.last_name, "Singhal");
    student1.gender = 'M';
    student1.dob.day = 26;
    student1.dob.month = 7;
    student1.dob.year = 2004;
    student1.marks.english = 85.5;
    student1.marks.mathematics = 90.0;
    student1.marks.comp_sci = 92.0;

    printf("Roll number: %d\n", student1.roll_no);
    printf("Name: %s %s %s\n", student1.name.first_name, student1.name.middle_name, student1.name.last_name);
    printf("Gender: %c\n", student1.gender);
    printf("Date of Birth: %02d/%02d/%d\n", student1.dob.day, student1.dob.month, student1.dob.year);
    printf("Marks:\tEnglish: %.2f\tMathematics: %.2f\tComputer Science: %.2f", student1.marks.english, student1.marks.mathematics, student1.marks.comp_sci);
    return 0;
}