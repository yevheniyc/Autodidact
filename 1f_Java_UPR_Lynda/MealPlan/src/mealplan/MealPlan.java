/*
This program demonstrates the concepts of call by reference
and call by value

Methods:
- call by reference (pointer to the first value of an array) vs call by value
 */
package mealplan;
import java.util.Arrays;
import java.util.Scanner;
/**
 *
 * 
 */
public class MealPlan {

    public static void main(String[] args) {
        // call getTotalMealWeeks method, which returns the number of weeks
        int numWeeks = getTotalMealWeeks();
        double[] dailyMealCost = new double[7];
        // print array contents before calling the method, should be all 0z
        System.out.println("Before calling the method: " + 
                Arrays.toString(dailyMealCost));
        // call getDailyMealCost method - uses call by reference
        getDailyMealCost(dailyMealCost);
        // print array contents after calling the method
        System.out.println("After calling the method: " +
                Arrays.toString(dailyMealCost));
        // use the number of weeks and daily meal cost array to find the total
        // Note: the numweeks is a call by value, but the dailyMealCost is
        // an array, so it is passing the address of the variable to the method
        double totalCost = computeMealPlanCost(numWeeks, dailyMealCost);
        // use a method to print the total cost
        printTotalMealPlanCost(totalCost);
    }
    
    public static int getTotalMealWeeks() {
        Scanner in = new Scanner(System.in);
        System.out.println("How many weeks in your semester? ");
        int totalWeeks = in.nextInt();
        return totalWeeks;
    }
    
    public static void getDailyMealCost(double[] dailyCost) {
        Scanner in = new Scanner(System.in);
        // use the length of the array for looping
        for (int i = 0; i < dailyCost.length; i++) {
            System.out.println("Enter the estimated cost for day " + (i + 1));
            dailyCost[i] = in.nextDouble();
        }
    }
    
    public static double computeMealPlanCost(int numWeeks, double[] dailyCost) {
        double totalCost = 0, weeklyCost = 0;
        for (int i = 0; i < dailyCost.length; i++) {
            weeklyCost += dailyCost[i];
        }
        
        totalCost = weeklyCost * numWeeks;
        return totalCost;
    }
    
    public static void printTotalMealPlanCost(double totalCost) {
        System.out.printf("Total cost is: $%5.2f ", totalCost);
        System.out.println();
    }
}
