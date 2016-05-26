/*
Randomly generate to die values 100 times and count
how many time we roll doubles
 */
package randomnumbers;
import java.util.Random;

/**
 *
 * @author whitehat
 */
public class RandomNumbers {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int die1, die2, countDoubles = 0;
        Random rand = new Random();
        for (int i = 0; i < 100; i++) {
            die1 = rand.nextInt(6)+1; // range of numbers 1 - 6
            die2 = rand.nextInt(6)+1;
            if (die1 == die2) {
                countDoubles++;
            }
        }
        System.out.println("I roled " + countDoubles + " doubles");
    }
}
