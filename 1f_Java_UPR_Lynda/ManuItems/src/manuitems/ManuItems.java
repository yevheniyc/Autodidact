/*
Practice with reading to/writing from files

1. Read manu items from a file
2. include error-handling when reading from file
3. Read each item from a file and ask a user to give name for each item
4. Write each item with its price to a separate file
 */
package manuitems;
import java.util.Scanner;
import java.io.*;

public class ManuItems {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String item;
        double price;
        File outputFile = new File("menuprices.txt");
        File inputFile = new File("menuitems.txt");
        
        try {
            // create scanner obj that reads from a file
            Scanner input = new Scanner(inputFile);
            // use PrintWriter to write to a file
            PrintWriter output = new PrintWriter(outputFile);
            while (input.hasNextLine()) {
                item = input.nextLine();
                System.out.println("Enter the price for item : " + item);
                price = in.nextDouble();
                output.println(item + " : " + price);
            }
            output.close();
            
        } catch (Exception e) {
            System.out.println("Error when writing or reading to a file: " + e.toString());
        }
        printAllItems(outputFile);
    }
    
    public static void printAllItems(File fileObj) {
        // Print all items in the file object
        try {
            Scanner printFileLines = new Scanner(fileObj);
            while (printFileLines.hasNextLine()) {
                System.out.println(printFileLines.nextLine());
            }
        } catch (Exception e) {
            System.out.println("Error when reading from a file: " + e.toString());
        }
        
    }
    
}
