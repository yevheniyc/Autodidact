/*
    #1 in U&R Java

    This program uses total distance of the trip,
    the mpg of vehicle, and the current price of
    gas to calculate the total cost of the trip
 */
package travelcosts;
import java.util.Scanner; // used to read and write from the console

/**
 *
 * @author whitehat
 */
public class TravelCosts { // camelCase

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) { // single main
        double distance, mpg, pricePerGallon, totalCost;
        String vehicleType;
        Scanner in = new Scanner(System.in);
        System.out.println("Enter the total distance in miles: ");
        distance = in.nextDouble();
        System.out.println("Enter the mpg for the vehicle: ");
        mpg = in.nextDouble();
        System.out.println("Enter the price of one gallon of gas: ");
        pricePerGallon = in.nextDouble();
        System.out.println("Please enter the vehicle type");
        vehicleType = in.next();
        
        // calculate total cost
        totalCost = (distance/mpg)*pricePerGallon;
        System.out.printf("The trip is going to cost %5.2f, you drive"
                + " a " + vehicleType,totalCost);
        System.out.println();
    }
    
}

/*
Characters:
    char letterA = 'a'; // single quotes

Boolean:
    bool result = true;

Primitive Data Types: stored directly in memory with their variable names
- Integers (no fractional part):
    byte (-127, 127; 0, 255), short, int, and long
- Rational Numbers (may have a fractional part)
    float, double

Structure Data Types: stored by reference or by the address of the location
                      in memory where the data exists

Strings: are not primitive data types, but often discussed with them
- Stored as an array of sequence of characters

Arrays: multiple values of the same data type?
>> double[] items = new double[4];
- each value in array is accessed using an index value (pointer), 
which indicates its position in memory
- watch out for "out of bounds" errors
*/