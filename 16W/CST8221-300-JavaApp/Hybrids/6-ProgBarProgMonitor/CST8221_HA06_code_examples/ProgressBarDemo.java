/*  CST8221-JAP: HA#06
    File name: ProgressBarDemo.java 
*/

import java.awt.*;
import javax.swing.*;

/** Demonstrates the JProgressBar component.
 *  The progress bar shows the progres of a for loop.
 *  @author Sv. Ranev
 *  @version 1.16.2
 *  @see JProgressBar
 */
public class ProgressBarDemo extends JPanel {
 
  private static final long serialVersionUID = -3135342300079105820L;
  private JLabel current;
  private JProgressBar progressBar;
  public static final int PB_MINIMUM=0;
  public static final int PB_MAXIMUM=1000;

/** Default constructor - creates GUI */ 
  public ProgressBarDemo() {
     setLayout(new BorderLayout());
     progressBar = new JProgressBar();
     progressBar.setMinimum(PB_MINIMUM);
     progressBar.setMaximum(PB_MAXIMUM);
     progressBar.setPreferredSize(new Dimension(80,20));
     add(progressBar,BorderLayout.SOUTH);
     current = new JLabel("Current value: ");
     add(current,BorderLayout.NORTH);
     setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
  }
  /** Updates the progress bar. Switches different display modes.
   *  @param newValue the new progress value.
   */
  public void updateProgressBar(int newValue) {
    int currentValue = progressBar.getValue();
    current.setText("Current Value: " + currentValue);
    if(currentValue <100){
     // at the beginning switch to Indeterminate mode
     if(currentValue == 1){
       progressBar.setIndeterminate(true);
     }
     progressBar.setValue(newValue); 
     return; 
    }
    // switch to default mode
    progressBar.setIndeterminate(false);
    if(currentValue < 500){
      progressBar.setValue(newValue); 
      return;
    }    
    if (currentValue >= 500 && currentValue <= 900) {
      // switch to Painted String mode
      //at 500 start displaying percents "N%"
      if(currentValue == 500){
       progressBar.setStringPainted(true);
      }     
      progressBar.setValue(newValue); 
      return;       
    }
    
     progressBar.setValue(newValue);
     //change the displayed string
     progressBar.setString("The End is Coming...");  
      
  }
 /**
  * Starts the application.
  * @param args an array of command-line arguments
  */
     
  public static void main(String args[]) {
     // the demo variable must be final so that it can be accessed by the 
     // anonymous inner classes below
     final ProgressBarDemo demo = new ProgressBarDemo();
     // create the application frame and make the GUI visible
     SwingUtilities.invokeLater(new Runnable() {
             public void run() {
               JFrame frame = new JFrame("Progress Bar Demo");
               frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);   
               frame.setContentPane(demo);
               frame.setSize(350,100);
               //show frame in the center of the screen
               frame.setLocationRelativeTo(null);
               frame.setVisible(true);
             }
         });
    
    
     // this is the loop the progress of which is tracked
     for (int i = PB_MINIMUM; i <= PB_MAXIMUM; i++) {
       final int percent=i;
       //The lines below are required to keep the GUI responsive to the user
       //It will execute the code within the event dispatch thread
       try {
         SwingUtilities.invokeLater(new Runnable() {
             public void run() {
               demo.updateProgressBar(percent);
             }
         });
         //make the program inactive for a while so that the GUI thread can do its work
         java.lang.Thread.sleep(25);
       } catch (InterruptedException e) {;}
     } 
  }
}
