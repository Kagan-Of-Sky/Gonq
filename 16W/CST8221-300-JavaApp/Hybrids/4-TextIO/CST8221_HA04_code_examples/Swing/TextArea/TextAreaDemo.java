// Fig. 14.48: TextAreaDemo.java
// Copying selected text from one text area to another. 
// Modified by S.Ranev 
// version: 1.16.1
import java.awt.EventQueue;
import javax.swing.JFrame;

public class TextAreaDemo
{
   public static void main( String[] args )
   { 
      EventQueue.invokeLater(new Runnable()
         {
            public void run()
            {           
              TextAreaFrame textAreaFrame = new TextAreaFrame(); 
              textAreaFrame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
              textAreaFrame.setSize( 425, 200 ); // set frame size
              textAreaFrame.setLocationByPlatform(true);
              textAreaFrame.setVisible(true); // display frame
            }
         });     
   } // end main
} // end class TextAreaDemo


