/*
Create instances of the House class for a real estate company.
 */
package realestatelistings;

/**
 *
 * @author whitehat
 */
public class RealEstateListings {


    public static void main(String[] args) {
        Property land = new Property(10000, "Land", 2.1);
        Property estate = new Property(25000, "Estate", 1.5, 3, 4);
        // lets print out info about both properties
        System.out.println(land.toString());
        System.out.println(estate.toString());
        estate.setAskingPrice((23000));
        System.out.println(estate.toString());
    }
    
}
