/*  CST8221-JAP: HA#06
    File name: ProgressMonitorInputDemo.java 
*/

import java.io.*;
import javax.swing.*;
/** Demonstrates the ProgressMonitorInputStream class.
 *  It updates the progress monitor automatically.
 *  In order to see the work of the progress monitor you must start the program at the command line
 *  The file must be greater than 1MB
 *  @author Sv. Ranev
 *  @version 1.16.2
 *  @see ProgressMonitorInputStream
 */
public class ProgressMonitorInputDemo {
    /** Default constructor - creates GUI */
    public ProgressMonitorInputDemo(String filename) {
        ProgressMonitorInputStream fileMonitor;
        
        try {
            fileMonitor = new ProgressMonitorInputStream(
                null, "Loading "+filename + ". Plese wait...", new FileInputStream(filename));
            while (fileMonitor.available() > 0) {
                byte [] line = new byte[30];
                fileMonitor.read(line);
                System.out.write(line);
            }
        } catch (FileNotFoundException e) {
            JOptionPane.showMessageDialog(null, "File not found: "
                + filename, "Error", JOptionPane.ERROR_MESSAGE); 
        } catch (IOException e) {;}
    }
    /**
     * Starts the application.
     * @param args an array of command-line arguments
     */
    public static void main(String args[]) {
       String fileName = JOptionPane.showInputDialog("Please enter a file name");
       new ProgressMonitorInputDemo(fileName); 
        
    }//end main
}
