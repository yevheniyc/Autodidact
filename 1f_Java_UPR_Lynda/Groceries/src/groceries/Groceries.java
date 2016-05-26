/*
Grocery list challenge:
- Create and ArrayList
- Fill it with the names of grocery items (with .add method)
- Ask the user for a random item name
- search the list for that name: use Linear Search
- Use it for both cases: for existing item and non-existing item
- if it is not found, then add to the end of the list
- When the user done entering items, print the final grocerry list
 */
package groceries;
import java.util.Scanner;
import java.util.ArrayList;


public class Groceries {

    public static void main(String[] args) {
        String[][] groceries = {{"apples", "fruit"}, {"oranges", "fruit"},
            {"tomatoes", "vegg"}};
        ArrayList<Item> items = new ArrayList<Item>();
        Item item;
        Scanner in = new Scanner(System.in);
        String search_item;
        // enhanced for-loop
        for (String[] grocerie : groceries) {
            // Item(name, type)
            item = new Item(grocerie[0], grocerie[1]);
            items.add(item);
        }
        System.out.println("Enter a grocery item to search for in the list: ");
        search_item = in.next();
        
        linearSearch(search_item, items);
        printFinalGroceryList(items);
    }
    
    public static void linearSearch(String search_item, ArrayList<Item> items) {
        for (int i = 0; i < items.size(); i++) {
            
            if (items.get(i).getItemName().equals(search_item)) {
                System.out.println("The item " + search_item + " was found!");
                break;
            } else {
                System.out.println("The item " + search_item + 
                        " was not found - adding to the grocery list");
                Item new_item = new Item(search_item, "undefined");
                items.add(new_item);
            }
        }
    }
    
    public static void printFinalGroceryList(ArrayList<Item> final_items) {
        // Use below looping if the list is not modified, otherwise, use above
        for (Item i_item : final_items) {
            System.out.println("name: " + i_item.getItemName() + 
                    " type: " + i_item.getItemType());
        }
    }
}
