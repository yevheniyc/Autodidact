/*
    #3 U&R JAVA

Data Conversion:
    - Java is a strictly data-type language - each variable needs explicit 
    declaration
    - Imlicit conversion vs Explicit conversion (casting)
        >> (double)(3 + 5 + 8)/3 - temperoraly conversion
 */
package dataconversion;

/**
 *
 * @author whitehat
 */
public class DataConversion {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        System.out.println((3 + 5 + 8)/3);
        System.out.println((3 + 5 + 8)/3.0);
        double volume = 4/3 * Math.PI * 10*10*10;
        double real_volume = 4/3.0 * Math.PI * 10*10*10;
        System.out.println("The volume is: " + volume);
        System.out.println("The real volue is: " + real_volume);
    }
    
}
