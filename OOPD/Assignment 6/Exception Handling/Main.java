import java.util.Scanner;

class ShoppingCart {
    private String[] products = {"Laptop", "Smartphone", "Headphones", "Smartwatch"};
    private int[] prices = {50000, 20000, 5000, 15000};

    public void addToCart(int productIndex, int quantity, String discountCode) {
        productIndex--;
        if(productIndex < 0 || productIndex >= products.length) {
            throw new ArrayIndexOutOfBoundsException("Invalid product selection.");
        }
        if(quantity <= 0) {
            throw new IllegalArgumentException("Quantity must be greater than zero.");
        }
        if(discountCode == null) {
            throw new NullPointerException("No discount code provided.");
        }

        int totalPrice = prices[productIndex] * quantity;
        int discount = 0;

        if(discountCode.equals("SAVE50"))
            discount = totalPrice / 0; // This will cause ArithmeticException
        else if(discountCode.equals("BIG2000"))
            discount = 2000;

        int finalPrice = totalPrice - discount;
        System.out.println("Added to cart: " + products[productIndex] + " x " + quantity + " \nTotal: Rs. " + finalPrice);
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ShoppingCart cart = new ShoppingCart();

        try {
            System.out.println("Products: \n1 - Laptop\n2 - Smartphone\n3 - Headphones\n4 - Smartwatch");
            System.out.print("Enter product number: ");
            int productIndex = Integer.parseInt(sc.nextLine());

            System.out.print("Enter quantity: ");
            int quantity = Integer.parseInt(sc.nextLine());

            System.out.print("Enter discount code (or press Enter to skip): ");
            String discountCode = sc.nextLine();
            if(discountCode.isEmpty())
                discountCode = null;

            cart.addToCart(productIndex, quantity, discountCode);
        }
        catch(ArrayIndexOutOfBoundsException | IllegalArgumentException | ArithmeticException e) {
            System.out.println("Error: " + e.getMessage());
        }
        catch(NullPointerException e) {
            System.out.println("Error: No discount applied.");
        }
        finally {
            System.out.println("Shopping session ended.");
        }
    }
}
