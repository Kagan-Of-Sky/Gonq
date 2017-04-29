// Fig. 14.10: TextFieldDemo.java 
// Modified by S. Ranev
// version: 1.16.1
import javax.swing.JFrame;
import java.awt.*;

public class TextFieldDemo
{
   public static void main( String[] args )
   { 
     //Schedule a job for the event-dispatching thread:
        //creating and showing this application's GUI.
      javax.swing.SwingUtilities.invokeLater(new Runnable() {
      @Override
        public void run() {                

      // create the application frame
        JFrame frame = new JFrame("Swing Text Fields Demo");
        TextFieldPanel textFieldPanel = new TextFieldPanel(); 
        Container contentPane = frame.getContentPane();
        contentPane.add(textFieldPanel,BorderLayout.CENTER);
        frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        frame.setSize( 400, 130 ); // set frame size
 //       frame.setResizable(false);
        frame.setLocationByPlatform(true);
        frame.setVisible( true ); // display frame
       } 
    });
   } // end main
} // end class TextFieldDemo

