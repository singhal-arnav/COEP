public class Main3 {
    public static void main(String[] args) {
        System.out.println("Demonstrating StringBuilder methods\n");

        StringBuilder sb = new StringBuilder("ObjectOriented");

        System.out.println("Current contents: " + sb);
        //Appending text
        sb.append(" Programming");
        System.out.println("After appending: " + sb);
        //Inserting text
        sb.insert(6, "-" );
        System.out.println("Inserting '-' between 'Object' and 'Oriented': " + sb);
        //Replacing text
        sb.replace(7, 15, "Driven");
        System.out.println("Replacing 'Oriented' with 'Driven': " + sb);
        //Deleting text
        sb.delete(7, 13);
        System.out.println("Deleting 'Oriented': " + sb);
        //Deleting a character at a specific index
        System.out.println("Deleting character at index 6");
        sb.deleteCharAt(6);
        System.out.println("Updated contents: " + sb);
        //Reversing the text
        sb.reverse();
        System.out.println("Reversing the text: " + sb);
        //Getting length
        System.out.println("Length: " + sb.length());
        //Getting a character at a specific index
        System.out.println("Character at index 2: " + sb.charAt(2));
        //Setting a character at a specific index
        System.out.println("Updating character at index 2 to 'X'");
        sb.setCharAt(2, 'X');
        System.out.println("Updated contents: " + sb);
        //Converting to String
        String finalString = sb.toString();
        System.out.println("Final string: " + finalString);
    }
}