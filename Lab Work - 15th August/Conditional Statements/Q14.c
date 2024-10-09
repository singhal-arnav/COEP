#include <stdio.h>

int main() {
    float phy, chem, bio, math, comp, per;
    printf("Enter marks scored in Physics: ");
    scanf("%f", &phy);
    printf("Enter marks scored in Chemistry: ");
    scanf("%f", &chem);
    printf("Enter marks scored in Biology: ");
    scanf("%f", &bio);
    printf("Enter marks scored in Mathematics: ");
    scanf("%f", &math);
    printf("Enter marks scored in Computer: ");
    scanf("%f", &comp);

    per = (phy + chem + bio + math + comp) / 5;
    printf("Percentage = %f%%\n", per);
    printf("Grade = ");

    if(per >= 90)
        printf("A");
    else if(per >= 80)
        printf("B");
    else if(per >= 70)
        printf("C");
    else if(per >= 60)
        printf("D");
    else if(per >= 40)
        printf("E");
    else
        printf("F");
    
    return 0;
}