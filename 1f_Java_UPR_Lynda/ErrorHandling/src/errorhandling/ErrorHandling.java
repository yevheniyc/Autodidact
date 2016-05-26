/*
Demo error handling logic:
- avoiding my program to end abruptly.
 */
package errorhandling;

public class ErrorHandling {

    public static void main(String[] args) {
        int count = 0;
        int x = 5, y = 6, z = 7;
        try {
            double average = (x + y + z) / count;
            System.out.println("The average is: " + average);
        } catch (Exception e) {
            System.out.println(e.toString());
        }
        
    } 
}
