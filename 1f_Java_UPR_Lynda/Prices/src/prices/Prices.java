/*
Use 2-D array to represent prices and discounts
 */
package prices;
import java.util.Scanner;
/**
 *
 * @author whitehat
 */
public class Prices {

    public static void main(String[] args) {
        // 2-D array: original prices (1st col) and discounted prices (2nd col)
        double[][] prices = new double[5][2];
        Scanner in = new Scanner(System.in);
        for (int i = 0; i < 5; i++) {
            System.out.println("Enter the original: ");
            prices[i][0] = in.nextDouble();
            prices[i][1] = prices[i][0] * .7;
        }
        
        for (int i = 0; i < 5; i++) {
            System.out.println("original price $" + prices[i][0] + 
                    "\tdiscounted price $" + prices[i][1]);
        }
    }
    
}
