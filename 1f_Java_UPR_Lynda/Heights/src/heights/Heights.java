/*
Find average student height
 */
package heights;
import java.util.Scanner;

/**
 *
 * @author whitehat
 */
public class Heights {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int numStudents;
        double [] heights;
        System.out.println("how many students? ");
        numStudents = in.nextInt();
        heights = new double[numStudents];
        
        for (int i = 0; i < numStudents; i++) {
            System.out.println("Enter height: ");
            heights[i] = in.nextDouble();
        }
        
        // find the tallest
        double maxHeight = heights[0];
        for (int i = 1; i < heights.length; i++) {
            if (maxHeight < heights[i])
                maxHeight = heights[i];
        }
        // get the average
        double total = 0;
        for (int i = 0; i < heights.length; i++) {
            total += heights[i];
        }
        // print out results
        System.out.println("The tallest student is: " + maxHeight);
        System.out.println("The average height: " + total/heights.length);
    }
    
}
