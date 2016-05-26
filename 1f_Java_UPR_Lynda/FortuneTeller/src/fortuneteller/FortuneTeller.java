/*
Reading from a file - read possible replies to questions
 */
package fortuneteller;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.*; // read, write, create a new file
import java.util.Random;


public class FortuneTeller {

    public static void main(String[] args) {
        File inputFile = new File("answers.txt");
        ArrayList<String> answers = new ArrayList<String>();
        String answer, response = "y";
        Random rand = new Random();
        // try/catch required when working with files
        try {
            // create a scanner object that reads from a file, and not std.in
            Scanner input = new Scanner(inputFile);
            // while there is text in a file, read it and put it into arraylist
            while (input.hasNextLine()) {
                answer = input.nextLine();
                answers.add(answer);
            }
        } catch (Exception e) { // if file can't be read, explain why
            System.out.println("The input file \"answers.txt\" was not found");
            System.out.println(e.toString());
        }
        Scanner in = new Scanner(System.in);
        while (response.equalsIgnoreCase("y")) {
            System.out.println("The fortune teller is ready for you \n" +
                    "Please think about your question in your mind\n" +
                    "and hit enter for your reply.");
            in.nextLine();
            // answers.get(10) <- rand.nextInt(10) <- answers.size() == 10
            System.out.println("The fortune teller says: \n"
            + answers.get(rand.nextInt(answers.size())) + "\"\n");
            System.out.println("Do you have another question? (y/n)");
            response = in.nextLine();
        }
    }
    
}
