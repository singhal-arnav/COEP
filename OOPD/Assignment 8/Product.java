import java.util.ArrayList;
import java.util.List;

class Store<T> {
    private List<T> items;

    public Store() {
        this.items = new ArrayList<>();
    }

    public void addItem(T item) {
        items.add(item);
    }

    public List<T> getItems() {
        return items;
    }

    public void displayAllItems() {
        for (T item : items) {
            Utils.displayDetails(item);
            System.out.println("-----");
        }
    }
}

class Utils {
    public static <T> void displayDetails(T item) {
        System.out.println(item.toString());
    }
}

class Book {
    private String title;
    private String author;
    private double price;

    public Book(String title, String author, double price) {
        this.title = title;
        this.author = author;
        this.price = price;
    }

    @Override
    public String toString() {
        return "Book: " + title + " by " + author + ", Price: $" + price;
    }
}

class Electronic {
    private String name;
    private String brand;
    private double price;

    public Electronic(String name, String brand, double price) {
        this.name = name;
        this.brand = brand;
        this.price = price;
    }

    @Override
    public String toString() {
        return "Electronic: " + name + " by " + brand + ", Price: $" + price;
    }
}

class Clothing {
    private String type;
    private String size;
    private double price;

    public Clothing(String type, String size, double price) {
        this.type = type;
        this.size = size;
        this.price = price;
    }

    @Override
    public String toString() {
        return "Clothing: " + type + ", Size: " + size + ", Price: $" + price;
    }
}

class Food {
    private String name;
    private String expiryDate;
    private double price;

    public Food(String name, String expiryDate, double price) {
        this.name = name;
        this.expiryDate = expiryDate;
        this.price = price;
    }

    @Override
    public String toString() {
        return "Food: " + name + ", Expires: " + expiryDate + ", Price: $" + price;
    }
}

class Furniture {
    private String type;
    private String material;
    private double price;

    public Furniture(String type, String material, double price) {
        this.type = type;
        this.material = material;
        this.price = price;
    }

    @Override
    public String toString() {
        return "Furniture: " + type + ", Material: " + material + ", Price: $" + price;
    }
}

class Toy {
    private String name;
    private int ageGroup;
    private double price;

    public Toy(String name, int ageGroup, double price) {
        this.name = name;
        this.ageGroup = ageGroup;
        this.price = price;
    }

    @Override
    public String toString() {
        return "Toy: " + name + ", Age Group: " + ageGroup + "+, Price: $" + price;
    }
}

public class Product {
    public static void main(String[] args) {
        Store<Book> bookStore = new Store<>();
        bookStore.addItem(new Book("1984", "George Orwell", 1360));
        bookStore.addItem(new Book("The Alchemist", "Paulo Coelho", 1240));

        Store<Electronic> electronicStore = new Store<>();
        electronicStore.addItem(new Electronic("Smartphone", "Pixel", 59500));
        electronicStore.addItem(new Electronic("Laptop", "ASUS", 72250));

        Store<Clothing> clothingStore = new Store<>();
        clothingStore.addItem(new Clothing("T-Shirt", "M", 1700));
        clothingStore.addItem(new Clothing("Jeans", "L", 3400));

        Store<Food> foodStore = new Store<>();
        foodStore.addItem(new Food("Milk", "2025-04-30", 45));
        foodStore.addItem(new Food("Bread", "2025-04-12", 30));

        Store<Furniture> furnitureStore = new Store<>();
        furnitureStore.addItem(new Furniture("Chair", "Wood", 5100));
        furnitureStore.addItem(new Furniture("Table", "Glass", 12000));

        Store<Toy> toyStore = new Store<>();
        toyStore.addItem(new Toy("Lego Set", 8, 5000));
        toyStore.addItem(new Toy("Action Figure", 5, 1250));

        bookStore.displayAllItems();
        System.out.println();
        electronicStore.displayAllItems();
        System.out.println();
        clothingStore.displayAllItems();
        System.out.println();
        foodStore.displayAllItems();
        System.out.println();
        furnitureStore.displayAllItems();
        System.out.println();
        toyStore.displayAllItems();
    }
}