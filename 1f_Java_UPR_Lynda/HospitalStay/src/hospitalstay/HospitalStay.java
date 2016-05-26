/*
Calculate:
- total charges for a patient for the hospital stay
    - a patient might be admitted overnight:
        - ask the user for the hospital overnight stay
        - ask for the madication charges
        - ask for the lab service charges
    or
    - a patient might be admitted for not overnight:
        - ask for medication charges
        - ask for the lab services

    then
    - calculate the chanrges + print the final total
    then 
    - ask the user if they want to calculate charges for another patient

 */
package hospitalstay;
import java.util.Scanner;
import java.util.Arrays;
/**
 *
 * @author whitehat
 */
public class HospitalStay {

    public static void main(String[] args) {
        double[] chargesAll = new double[3];
        double totalCharges = 0;
        chargesAll = getAllCharges(chargesAll);
        totalCharges = getTotalCharges(chargesAll);
        printAllCharges(chargesAll);
        printTotalCharges(totalCharges);
        
        // ask if the user wants to calculate another patient
    }
    
    public static double[] getAllCharges(double[] charges) {
        double overnightCharges = 0, medicationCharges = 0, labCharges = 0;
        String overnight;
        Scanner in = new Scanner(System.in);
        
        System.out.println("Is the patient admitted overnight (yes/no)? ");
        overnight = in.next();
        if (overnight.equals("yes")) {
            System.out.println("Enter overnight charges: ");
            overnightCharges = in.nextDouble();
        }
        System.out.println("Enter medication charges: ");
        medicationCharges = in.nextDouble();
        System.out.println("Enter lab charges: ");
        labCharges = in.nextDouble();
        
        charges = new double[]{overnightCharges, medicationCharges, labCharges};
        return charges;
    }
    
    public static double getTotalCharges(double[] charges) {
        double totalCharges = 0;
        for (int i=0; i < charges.length; i++) {
            totalCharges += charges[i];
        }
        return totalCharges;
    }
    
    public static void printAllCharges(double[] charges) {
        // printing arrays
        System.out.println("All Charges are: " + Arrays.toString(charges));
    }
    
    public static void printTotalCharges(double totalCharges) {
        System.out.printf("Total charges are: $%5.2f", totalCharges);
        System.out.println();
    }
}
