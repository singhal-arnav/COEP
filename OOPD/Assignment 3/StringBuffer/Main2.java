public class Main2 {
    public static void main(String[] args) {
        System.out.println("Demonstrating StringBuffer methods\n");

        StringBuffer sb = new StringBuffer("Object Oriented Programming");

        System.out.println("Current contents: " + sb);
        //Appending text
        System.out.println("Appending text");
        sb.append(" in Java");
        System.out.println("Updated contents: " + sb);
        //Inserting text
        System.out.println("Inserting text");
        sb.insert(27, " and Design");
        System.out.println("Updated contents: " + sb);
        //Replacing texts
        System.out.println("Replacing part of the text");
        sb.replace(28, 38, "Principles");
        System.out.println("Updated contents: " + sb);
        //Deleting a portion of the text
        System.out.println("Deleting 'Principles'");
        sb.delete(28, 39);
        System.out.println("Updated contents: " + sb);
        //Reversing the contents
        System.out.println("Reversing the text");
        sb.reverse();
        System.out.println("Updated contents: " + sb);
        //Displaying length and capacity
        System.out.println("Length: " + sb.length());
        System.out.println("Capacity: " + sb.capacity());
        //Setting a character at a specific index
        System.out.println("Updating character at index 5 to 'X'");
        sb.setCharAt(5, 'X');
        System.out.println("Updated contents: " + sb);
        //Ensuring minimum capacity
        System.out.println("Setting minimum capacity to 100");
        sb.ensureCapacity(100);
        System.out.println("Updated capacity: " + sb.capacity());
    }
}