// Chapter 14: FlowLayoutDemo.java
// Testing FlowLayoutFrame.
// Modified by S. Ranev
import java.awt.EventQueue;
import javax.swing.JFrame;

public class FlowLayoutDemo 
{
   public static void main( String[] args )
   { 
     // Make all components to configured by the event dispatch thread.
     // This is the thread that passes user provoked events such as mouse clicks to 
     // the GUI components which have registered listeners for the events.
     // The following code fragment forces the statements in the run() method to be executed in the
     // event dispatch thread. 
     EventQueue.invokeLater(new Runnable()
         {
            public void run()
            {
              FlowLayoutFrame flowLayoutFrame = new FlowLayoutFrame(); 
              flowLayoutFrame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
              flowLayoutFrame.setSize( 300, 75 ); // set frame size
              flowLayoutFrame.setVisible( true ); // display frame	
            }
         });
      
   } // end main
} // end class FlowLayoutDemo


/**************************************************************************
 * (C) Copyright 1992-2010 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
