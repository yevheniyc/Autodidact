/*
Below is a class constructor with two features:
- method overloading (creating a constructor for different types of property)
- mutator method - a setter

Encapsulation:
- hiding methods from the user

Inheritance uses words such as:
- extends
- implements

Polymorphism:
    - Two implementations of the same method
    - Allows for the same object act differently in different circumstances
    - Bug
        - moves - crawls
        - LadyBug
            - moves -> flies
        - GrassHopper
            - moves -> jumps
 */
package realestatelistings;

/**
 *
 * @author whitehat
 */
public class Property {
    private double askingPrice;
    private String propertyType;
    private double lotSize;
    private int numBaths;
    private int numBeds;
    
    public Property(double askingPrice, String propertyType, double lotSize) {
        this.askingPrice = askingPrice;
        this.propertyType = propertyType;
        this.lotSize = lotSize;
        numBaths = 0;
        numBeds = 0;
    }
    
    // method overloading
    public Property(double askingPrice, String propertyType, double lotSize,
            int numBaths, int numBeds) {
        this.askingPrice = askingPrice;
        this.propertyType = propertyType;
        this.lotSize = lotSize;
        this.numBaths = numBaths;
        this.numBeds = numBeds;
    }
    
    // print nicely
    public String toString() {
        return "Asking price: $" + askingPrice +
                "\nProperty Type: " + propertyType +
                "\nLot Size: " + lotSize +
                "\nNumber of baths: " + numBaths +
                "\nNumber of bedrooms" + numBeds;
    }
    
    // mutator method - setters
    public void setAskingPrice(double newValue) {
        askingPrice = newValue;
    }
}
