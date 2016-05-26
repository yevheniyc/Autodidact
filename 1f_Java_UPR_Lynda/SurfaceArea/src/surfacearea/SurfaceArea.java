/*
    Calculate surface area of the house to be painted
 */
package surfacearea;
import java.util.Scanner;

/**
 *
 * @author whitehat
 */
public class SurfaceArea {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // set the values front and sides
        double front_length, front_height, side_length, side_height;
        double all_area, pain_free_area, coverage_area;
 
        // Ask user for inputs
        Scanner in = new Scanner(System.in);
        // Coverage Area of 1 gallon of pain
        System.out.println("Enter front length: ");
        front_length = in.nextDouble();
        System.out.println("Enter front height: ");
        front_height = in.nextDouble();
        System.out.println("Enter side_length: ");
        side_length = in.nextDouble();
        System.out.println("Enter side height: ");
        side_height = in.nextDouble();
        
        all_area = (front_length * front_height * 2) + 
                   (side_length * side_height * 2);
        
        System.out.print(args);
        System.out.printf("The total area coverage is: %5.2f", all_area);
        
    }
    
}

/*
Expressions:
- add, concatenate, *, /, % (modular/remainder)
area = Math.PI * radius * radius
c = Math.sqrt(a*a + b*b)
- boolean - true/false

Desisions: 
- Relational operators: <, <=, >, >=, ==, !=
- Logical operators: &&, ||, if, else:
    >> if (outsideTemp < 32) {System.out.println("")} else {System.out.println()}
*/
