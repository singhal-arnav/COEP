import java.util.Scanner;

public class Main3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        float pencil, pen, eraser, gst_rate = 0.18f, cost, gst, amount;

        System.out.print("Enter the price of the pencil: ");
        pencil = sc.nextFloat();
        System.out.print("Enter the price of the pen: ");
        pen = sc.nextFloat();
        System.out.print("Enter the price of the eraser: ");
        eraser = sc.nextFloat();

        cost = pencil + pen + eraser;
        System.out.println("Cost (without GST) = " + cost);
        gst = gst_rate * cost;
        System.out.println("GST = " + gst);
        amount = cost + gst;
        System.out.print("Total Amount (with GST) = " + amount);
    }
}