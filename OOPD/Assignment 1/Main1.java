import java.util.Scanner;

class Car {
    String make, model, colour;
    int year;

    public Car(String make, String model, int year, String colour) {
        this.make = make;
        this.model = model;
        this.year = year;
        this.colour = colour;
    }

    public void displayCar() {
        System.out.println("Car Details:");
        System.out.println("Make: " + this.make);
        System.out.println("Model: " + this.model);
        System.out.println("Year: " + this.year);
        System.out.println("Colour: " + this.colour);
    }

    public void changeColour(String newColour) {
        this.colour = newColour;
    }
}

public class Main1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String make, model, colour;
        int year;

        System.out.print("Enter Make of Car 1: ");
        make = sc.nextLine();
        System.out.print("Enter Model of Car 1: ");
        model = sc.nextLine();
        System.out.print("Enter Launch Year of Car 1: ");
        year = sc.nextInt();
        colour = sc.nextLine();
        System.out.print("Enter Colour of Car 1: ");
        colour = sc.nextLine();
        Car car1 = new Car(make, model, year, colour);

        System.out.print("Enter Make of Car 2: ");
        make = sc.nextLine();
        System.out.print("Enter Model of Car 2: ");
        model = sc.nextLine();
        System.out.print("Enter Launch Year of Car 2: ");
        year = sc.nextInt();
        colour = sc.nextLine();
        System.out.print("Enter Colour of Car 2: ");
        colour = sc.nextLine();
        Car car2 = new Car(make, model, year, colour);

        car1.displayCar();
        car2.displayCar();

        System.out.print("Enter new colour for Car 1:");
        colour = sc.nextLine();
        car1.changeColour(colour);
        car1.displayCar();
    }
}