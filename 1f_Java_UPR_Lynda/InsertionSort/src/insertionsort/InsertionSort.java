/*
Insertion Sort algorithm
 */
package insertionsort;

public class InsertionSort {

    public static void main(String[] args) {
        int[] numbers = {67, 78, 4, 15, 57, 30, 99, 33};
        InsertionSort(numbers);
        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + "\t");
        }
    }
    
    public static void InsertionSort(int[] num) {
        int j, key, i;
        for (j = 1; j < num.length; j++) {
            key = num[j];
            for (i = j -1; (i >= 0) && (num[i] < key); i--) {
                num[i + 1] = num[i];
            }
            num[i + 1] = key;
        }
    }
    
}
