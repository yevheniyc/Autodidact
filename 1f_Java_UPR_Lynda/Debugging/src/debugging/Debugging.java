/*
   #4 UP&R JAVA
    This program is used to show how to find errors in your program
 */
package debugging;
import java.util.*;
/**
 *
 * @author Peggy Fisher
 */
public class Debugging {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        //declare variables
        int number;
        double average, value;
        // an array of strings
        String[] daysOfTheWeek = {"Sunday", "Monday", "Tuesday", "Wednesday", 
            "Thursday", "Friday", "Saturday"};
        //sample errors
        value = 3.75;      //example of syntax error, missing semi-colon
         //example of implicit conversion error - use casting
        number = (int)value;
        //average = (3 + 5 + 8) / 0;
        System.out.println("The first day of the week is: "+ daysOfTheWeek[0]);
        System.out.println("The last day of the week is: "+ daysOfTheWeek[6]);
        average = (3 + 5 + 8) / 3.0;  //example of logic error 
        System.out.println("expected value is 5.33, actual value is: " + average);
        }
    }
    
