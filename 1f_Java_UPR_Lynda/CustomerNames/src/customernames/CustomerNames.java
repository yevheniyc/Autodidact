/*
Writing to a file
 */
package customernames;
import java.util.Scanner;
import java.io.*;

public class CustomerNames {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        File output = new File("customers.txt");
        String name;
        System.out.println("Enter the first customer name: ");
        name = in.nextLine();
        try {
            // use PrintWriter to write to files
            PrintWriter out = new PrintWriter(output);
            while (name.equalsIgnoreCase("done") == false) {
                out.println(name);
                System.out.println("Enter the next name or \"done\" to exit");
                name = in.nextLine();
            }
            // if not closed, info will stay in buffer
            out.close();
        } catch (Exception e) {
            System.out.println("Error when writing to a file: " + e.toString());
        }
    }
}
