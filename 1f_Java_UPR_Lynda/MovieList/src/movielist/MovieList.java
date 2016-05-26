/*
1. Create a Movie Class:
    - instance data:
        - name of the movie
        - movie rating - "G", "PG", "PG13"
        - the year movie was made
        - runtime
    - public interface:
        - accessor and mutator methods for each data mentioned above

2. Main:
    - Ask user the information about their favorite movie:
        - title
        - rating
        - year
        - runtime
    - Create the movie instance
    - Print out the instance info using toString() method
 */
package movielist;
import java.util.Scanner;

/**
 *
 * @author whitehat
 */
public class MovieList {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        String title = "";
        String rating = ""; // G, PG
        int year = 0;
        double runtime = 0;
        Movie movie;
        // init scanner
        Scanner in = new Scanner(System.in);
        // ask for all info
        System.out.println("Enter moview title: ");
        title = in.next();
        System.out.println("Enter movie rating: ");
        rating = in.next();
        System.out.println("Enter the year: ");
        year = in.nextInt();
        System.out.println("Enter runtime: ");
        runtime = in.nextDouble();
        
        movie = new Movie(title, rating, year, runtime);
        System.out.println(movie.toString());
        
        movie.setMovieTitle("Rambo");
        System.out.println(movie.toString());
    }
    
}
