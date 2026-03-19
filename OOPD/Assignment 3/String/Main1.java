import java.util.Arrays;

public class Main1 {
    public static void main(String[] args) {

        System.out.println("Demonstrating String methods\n");

        String str = "Object Oriented Programming", str2 = "object";
        char[] a = {'c', 'o', 'e', 'p'};
        System.out.println("String 1: " + str);

        System.out.println("Character at index 3: " + str.charAt(3));
        System.out.println("Code point at index 4: " + str.codePointAt(4));
        System.out.println("Code point before index 4: " + str.codePointBefore(4));
        System.out.println("Code point count from index 3 to 7: " + str.codePointCount(3, 7));
        System.out.print("String 2: " + str2 + "\n");
        System.out.println("Comparing string 1 with string 2: " + str.compareTo(str2));
        System.out.println("Comparing string 1 with string 2 (ignoring case): " + str.compareToIgnoreCase(str2));
        System.out.println("Concatenating string 1 with string 2: " + str.concat(str2));
        System.out.println("Checking if string 1 contains string 2: " + str.contains(str2));
        System.out.println("Checking if the string contents are equal: " + str.contentEquals(str2));
        System.out.println("Converting character array to string: " + String.copyValueOf(a));
        System.out.println("Checking if string 1 ends with string 2: " + str.endsWith(str2));
        System.out.println("Checking if the strings are equal: " + str.equals(str2));
        System.out.println("Checking if the strings are equal (ignoring case): " + str.equalsIgnoreCase(str2));
        System.out.println("Formatted string: " + String.format("%s is powerful", str));
        System.out.println("String in bytes: " + Arrays.toString(str.getBytes()));
        char[] charArray = new char[10];
        str.getChars(0, 10, charArray, 0);
        System.out.println("Extracted characters: " + new String(charArray));
        System.out.println("Hash code of string: " + str.hashCode());
        System.out.println("Index of 'Oriented': " + str.indexOf("Oriented"));
        System.out.println("Interned string: " + str.intern());
        if(str.isEmpty())
            System.out.println("The string is empty");
        else
            System.out.println("The string is not empty");
        System.out.println("Joined string: " + String.join(" - ", "OOP", "Java", "Encapsulation"));
        System.out.println("Last index of 'o': " + str.lastIndexOf('o'));
        System.out.println("Length of string: " + str.length());
        System.out.println("Does it match regex '.*Programming'?: " + str.matches(".*Programming"));
        System.out.println("Offset by code points: " + str.offsetByCodePoints(2, 3));
        System.out.println("Region matches: " + str.regionMatches(0, str2, 0, 4));
        System.out.println("Replacing 'Object' with 'OOP': " + str.replace("Object", "OOP"));
        System.out.println("Replacing all spaces with hyphens: " + str.replaceAll(" ", "-"));
        System.out.println("Replacing first space with hyphen: " + str.replaceFirst(" ", "-"));
        System.out.println("Splitting string: " + Arrays.toString(str.split(" ")));
        System.out.println("Does it start with 'Object'?: " + str.startsWith("Object"));
        System.out.println("Substring from index 8: " + str.substring(8));
        System.out.println("Subsequence from index 8 to 18: " + str.subSequence(8, 18));
        System.out.println("String to char array: " + Arrays.toString(str.toCharArray()));
        System.out.println("String in lowercase: " + str.toLowerCase());
        System.out.println("String representation: " + str.toString());
        System.out.println("String in uppercase: " + str.toUpperCase());
        System.out.println("Trimmed string: " + str.trim());
        System.out.println("String value of 1234: " + String.valueOf(1234));
    }
}