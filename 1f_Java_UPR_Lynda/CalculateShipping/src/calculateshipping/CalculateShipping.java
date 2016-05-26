/*
This program uses decision logic to determine shipping costs
 */
package calculateshipping;
import java.util.Scanner;

/**
 *
 * @author whitehat
 */
public class CalculateShipping {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        double totalSale = 0;
        Scanner in = new Scanner(System.in);
        System.out.println("Enter total for sale: ");
        totalSale = in.nextDouble();
        if (totalSale < 25) {
            totalSale = totalSale + 15;
        } else if (totalSale < 50) {
            totalSale = totalSale + 10;
        } else if (totalSale <= 75) {
            totalSale = totalSale + 5;
        }
        System.out.println("Total cost for your sale is: " + totalSale);
    }
    
}
