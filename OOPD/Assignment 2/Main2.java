import java.util.Scanner;

class Student {
    float english, physics, chemistry, maths, compsci;

    public Student(float english, float physics, float chemistry, float maths, float compsci) {
        this.english = english;
        this.physics = physics;
        this.chemistry = chemistry;
        this.maths = maths;
        this.compsci = compsci;
    }
}

public class Main2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int num;
        float english, physics, chemistry, maths, compsci;
        System.out.println("Enter the number of students: ");
        num = sc.nextInt();
        sc.nextLine();

        Student[] arr = new Student[num];

        for(int i = 0; i < num; i++) {
            System.out.println("Enter the marks of Student " + (i + 1));
            System.out.print("English: ");
            english = sc.nextFloat();
            sc.nextLine();
            System.out.print("Physics: ");
            physics = sc.nextFloat();
            sc.nextLine();
            System.out.print("Chemistry: ");
            chemistry = sc.nextFloat();
            sc.nextLine();
            System.out.print("Mathematics: ");
            maths = sc.nextFloat();
            sc.nextLine();
            System.out.print("Computer Science: ");
            compsci = sc.nextFloat();
            sc.nextLine();

            arr[i] = new Student(english, physics, chemistry, maths, compsci);
        }

        for(int i = 0; i < num; i++) {
            System.out.println("Marks of Student " + (i + 1) + ": ");
            System.out.println("English: " + arr[i].english);
            System.out.println("Physics: " + arr[i].physics);
            System.out.println("Chemistry: " + arr[i].chemistry);
            System.out.println("Mathematics: " + arr[i].maths);
            System.out.println("Computer Science: " + arr[i].compsci);
        }
    }
}