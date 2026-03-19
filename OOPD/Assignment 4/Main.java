class Vehicle {
    private String licensePlate;
    private String model;
    private double rentalCost;

    public Vehicle(String licensePlate, String model, double rentalCost) {
        this.licensePlate = licensePlate;
        this.model = model;
        this.rentalCost = rentalCost;
    }

    public String getLicensePlate() {
        return licensePlate;
    }

    public void setLicensePlate(String licensePlate) {
        this.licensePlate = licensePlate;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public double getRentalCost() {
        return rentalCost;
    }

    public void setRentalCost(double rentalCost) {
        this.rentalCost = rentalCost;
    }

    public double calculateRentalCost(int days) {
        return rentalCost * days;
    }

    public double calculateRentalCost(int days, int discountPercentage) {
        return (rentalCost * days) * (1 - discountPercentage/100.0);
    }

    public void displayDetails() {
        System.out.println("License Plate: " + this.licensePlate);
        System.out.println("Model: " + this.model);
        System.out.println("Rental Cost: " + this.rentalCost);
    }
}

class Car extends Vehicle {
    private double fuelCharge;

    public Car(String licensePlate, String model, double rentalCost, double fuelCharge) {
        super(licensePlate, model, rentalCost);
        this.fuelCharge = fuelCharge;
    }

    public double calculateRentalCost(int days) {
        return super.calculateRentalCost(days) + (fuelCharge * days);
    }

    public double calculateRentalCost(int days, int discountPercentage) {
        return super.calculateRentalCost(days, discountPercentage) + ((fuelCharge * days) * (1 - discountPercentage/100.0));
    }
}

class Bike extends Vehicle {
    public Bike(String licensePlate, String model, double rentalCost) {
        super(licensePlate, model, rentalCost);
    }

    public double calculateRentalCost(int days) {
        return super.calculateRentalCost(days);
    }

    public double calculateRentalCost(int days, int discountPercentage) {
        return super.calculateRentalCost(days, discountPercentage);
    }
}

public class Main {
    public static void main(String[] args) {
        Car car = new Car("MH12ID9283", "Honda City", 1000, 900);
        Bike bike = new Bike("MH14OS1923", "Royal Enfield", 800);

        System.out.println("Details of car:");
        car.displayDetails();

        System.out.println("\nUpdating model of car to Honda Amaze");
        car.setModel("Honda Amaze");

        System.out.println("\nUpdated details of car:");
        car.displayDetails();

        System.out.println("\nDetails of bike:");
        bike.displayDetails();

        System.out.println("\nCar Rental Cost for 5 days: ₹" + car.calculateRentalCost(5));
        System.out.println("Bike Rental Cost for 5 days: ₹" + bike.calculateRentalCost(5));
        System.out.println("Car Rental Cost for 5 days with 20% discount: ₹" + car.calculateRentalCost(5, 20));
        System.out.println("Bike Rental Cost for 5 days with 10% discount: ₹" + bike.calculateRentalCost(5, 10));
    }
}