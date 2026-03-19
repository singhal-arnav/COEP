import java.util.*;

public class Main4 {
    public static void main(String[] args) {
        System.out.println("Demonstrating Vector methods\n");

        Vector<String> cities = new Vector<>();

        //Adding elements
        System.out.println("Adding elements to vector");
        cities.add("Pune");
        cities.add("Mumbai");
        cities.add("New Delhi");
        System.out.println("Vector elements: " + cities);
        //Inserting at specified index
        System.out.println("Inserting Kolkata at index 1");
        cities.add(1, "Kolkata");
        System.out.println("Updated vector: " + cities);
        //Removing an element by value
        System.out.println("Removing Mumbai");
        cities.remove("Mumbai");
        //Removing an element by index
        System.out.println("Removing element at index 0");
        cities.remove(0);
        System.out.println("Updated vector: " + cities);
        //Displaying size of the vector
        System.out.println("Vector size: " + cities.size());
        //Accessing element at specified index
        System.out.println("First element: " + cities.get(0));
        //Updating element at specified index
        System.out.println("Updating element at index 0 to Chennai");
        cities.set(0, "Chennai");
        System.out.println("Updated vector: " + cities);
        //Checking if the vector is empty
        System.out.println("Is the vector empty? " + cities.isEmpty());
        //Checking if the vector contains a particular element
        System.out.println((cities.contains("Chennai")) ? "The vector contains Chennai" : "The vector does not contain Chennai");
        //Clearing the vector
        cities.clear();
        System.out.println("Vector after clearing: " + cities);
    }
}