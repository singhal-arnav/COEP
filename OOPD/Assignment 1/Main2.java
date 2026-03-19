import java.util.Scanner;

public class Main2 {
    public static void main(String[] args) {
        int a, b;
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the first integer: ");
        a = sc.nextInt();
        System.out.print("Enter the second integer: ");
        b = sc.nextInt();

        System.out.println("Value of a = " + a);
        System.out.println("Value of b = " + b);

        a = a + b;
        b = a - b;
        a = a - b;

        System.out.println("New value of a = " + a);
        System.out.println("New value of b = " + b);
    }
}