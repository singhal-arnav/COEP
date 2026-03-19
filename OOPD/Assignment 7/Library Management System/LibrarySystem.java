import java.util.ArrayList;
import java.util.List;

abstract class Item {
    private String name;
    public Item(String name) {
        this.name = name;
    }
    public String getName() {
        return name;
    }

    @Override
    public String toString() {                                  //Returns a type   of the object.
        return getClass().getSimpleName() + ": " + name;
    }
}

class Book extends Item {
    public Book(String name) {
        super(name);
    }
}

class Journal extends Item {
    public Journal(String name) {
        super(name);
    }
}

class Magazine extends Item {
    public Magazine(String name) {  
        super(name);
    }
}

class Library<T extends Item> {
    private List<T> collection = new ArrayList<>();
    public void addItem(T item) {
        collection.add(item);
    }
    public List<T> getItems() {
        return collection;
    }
}

public class LibrarySystem {
    public static void main(String[] args) {
        Library<Item> library = new Library<>();
        library.addItem(new Book("To Kill a Mockingbird"));
        library.addItem(new Book("The Alchemist"));
        library.addItem(new Journal("Scientific American"));
        library.addItem(new Magazine("Forbes"));
        library.addItem(new Magazine("The New Yorker"));

        System.out.println("Items Available: " + library.getItems());  //display all items
    }
}
