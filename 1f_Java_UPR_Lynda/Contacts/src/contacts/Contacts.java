/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package contacts;
import javax.swing.JFrame;

/**
 *
 * @author whitehat
 */
public class Contacts {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        JFrame frame = new ContactUI();
        // gui title
        frame.setTitle("GUI Test");
        // what happens when clicked on window's "x"
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        // open the frame!
        frame.setVisible(true);
    }
    
}
