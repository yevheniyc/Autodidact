/*
Constructor representing a movie object with:
- title
- rating
- year
- runtime
 */
package movielist;


public class Movie {
    // instance data == global variables == insure data integrity
    private String title;
    private String rating;
    private int year;
    private double runtime;
    
    public Movie(String title, String rating, int year, double runtime) {
        this.title = title;
        this.rating = rating;
        this.year = year;
        this.runtime = runtime;
    }
    
    public String toString() {
        return "Title: " + title +
                "\nRating: " + rating +
                "\nYear: " + year + 
                "\nRuntime: " + runtime;
    }
    
    public void setMovieTitle(String newTitle) {
        title = newTitle;
    }
}
