/*
Sorting - Selection Sort Algorithm:
- compare the first number to the rest of the list
- once the list number is larger than the first, swap
- start over again
 */
package selectionsort;


public class SelectionSort {


    public static void main(String[] args) {
        int[] numbers = {67, 78, 4, 15, 57, 30, 99, 33};
        SelectionSort(numbers);
        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + "\t");
        }
    }
    
    public static void SelectionSort(int[] num) {
        int i, j, first, temp;
        for (i = num.length -1; i > 0; i--) {
            first = 0;
            for (j = 1; j <= i; j++) {
                if (num[j] < num[first])
                    first = j;
            }
            // swap
            temp = num[first];
            num[first] = num[i];
            num[i] = temp;
        }
    }
    
}
