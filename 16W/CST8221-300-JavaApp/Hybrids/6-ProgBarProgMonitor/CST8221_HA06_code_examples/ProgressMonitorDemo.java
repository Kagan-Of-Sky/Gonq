/*  CST8221-JAP: HA#06
    File name: ProgressMonitorDemo.java 
*/
import java.awt.*;
import java.awt.event.*;
import javax.swing.Timer;
import javax.swing.*;

/**
* This class demonstrates how to use a ProgressMonitor dialog. 
* An object of class Timer is used to simulate a task and its progress
* This example also shows how to use the UIManager to change some of the default UI properties.
* @author Sv. Ranev
* @version 1.16.2
* @see ProgressMonitor
*/
public class ProgressMonitorDemo extends JFrame /*implements ActionListener */{

  private static final long serialVersionUID = 2123394408772484219L;
  private ProgressMonitor pbar;
  private static int counter = 0;
  private Activity task;
  private JButton startButton;
  
  /** Default constructor - creates GUI */
  public ProgressMonitorDemo() {
    super("Progress Monitor Demo");
    
    // set up a button panel
      JPanel panel = new JPanel();
      startButton = new JButton("Start");
      panel.add(startButton);
      add(panel);
      //You can use the UIManager class to set some of the properties of the progress monitor.
      //This line changes the default text "Cancel" of the Cancel button to "Stop it!"
      UIManager.put("OptionPane.cancelButtonText", "Stop it!");
      //This line changes the default dialog title from "Progress..." to "Tracking Task Progress"
      UIManager.put("ProgressMonitor.progressText", "Tracking Task Progress");
      // set up the button event handler
        startButton.addActionListener(new ActionListener()
         {
            public void actionPerformed(ActionEvent event)
            {
               startButton.setEnabled(false);
                                                             
               // create progress dialog
               // it will launch after 500 millisecond
               pbar = new ProgressMonitor(null, "Monitoring Progress",
                                      "Initializing . . .", 0, 100);
               // Try this. The dialog box will pop-up over the applicatio frame
/* 
               pbar = new ProgressMonitor(ProgressMonitorDemo.this, "Monitoring Progress",
                                       "Initializing . . .", 0, 100);
*/
               // Fire a timer every once in a while to update the progress.              
               // create and start a task 
               task = new Activity();
               task.getActivity().start();

            }
         });
   }// end constructor  
 
 /** This class simulates activity using a Timer object
 */
 private class Activity implements ActionListener{
    Timer activity;
    public Activity(){
      //creates a Timer object.
      //Note:  The ActionListener is implemented in the ProgressMonitorDemo class
      activity = new Timer(500, this);
    }
    
    public Timer getActivity(){
      return activity;
    } 
  /** Event handler for the Timer. Invoked by the timer every half second.
  */
  public void actionPerformed(ActionEvent e) {
   // Place the progress monitor update on the event queue.
    SwingUtilities.invokeLater(new Update());
  } 
 }// end Activity
 
 /** This is the progress update class 
 */
 private class Update implements Runnable {
    public void run() {
      if (pbar.isCanceled()) {
        task.getActivity().stop();
        pbar.close();
        return;
      }
    pbar.setProgress(counter);
    pbar.setNote("Operation is "+counter+"% complete");
    counter += 2;
    }
  }
 /**
  * Starts the application.
  * @param args an array of command-line arguments
  */
 public static void main(String args[]) {

    EventQueue.invokeLater(new Runnable()  {
        public void run(){
         JFrame appFrame = new ProgressMonitorDemo();
         appFrame.setSize(450,100);
         appFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
         //show frame in the center of the screen
         appFrame.setLocationRelativeTo(null);
         appFrame.setVisible(true);
        }
     });   
  }//end main
}
