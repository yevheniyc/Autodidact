/*
Define Item constructor
 */
package groceries;


public class Item {
    private String name;
    private String i_type;
    
    public Item(String name, String i_type) {
        this.name = name;
        this.i_type = i_type;
    }
    
    public String getItemName() {
        return name;
    }
    
    public String getItemType() {
        return i_type;
    }
}
