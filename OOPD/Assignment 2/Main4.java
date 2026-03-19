public class Main4 {
    public static void main(String[] args) {
        System.out.println("Pattern 1:");
        for(int i = 1; i <= 5; i++) {
            for(int j = 1; j <= i; j++)
                System.out.print(j);
            System.out.println();
        }

        System.out.println("\nPattern 2:");
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5 - i - 1; j++) {
                System.out.print(" ");
            }
            for(int j = 0; j <= 2 * i; j++) {
                System.out.print("*");
            }
            System.out.println();
        }
    }
}