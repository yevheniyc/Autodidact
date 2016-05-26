/*
Method overloading:
- create a few methods with the same name but different parameters 
  or return values: for example, if average method needs to calculate
  averages of double and ints
- overloading methods is especially useful when working with classes and objects:
  - when we create a class to represent an instance of an object, we use a
    a constructor to build the object - the overloading is useful here, since
    we can allow user to create objects with default values, a partial list of 
    values or even the entire set of values.
 */
package overloading;

/**
 *
 * @author whitehat
 */
public class Overloading {

    public static void main(String[] args) {
        System.out.println("The average of three integers: " +
                average(3, 5, 8));
        System.out.println("The averages of three doubles: " +
                average(3.0, 4.5, 8.0));
    }
    
    public static double average(int x, int y, int z) {
        return (x + y + z)/3.0; // implicit converion
    }
    
    public static double average(double x, double y, double z) {
        return (x + y + z)/3;
    }
}
