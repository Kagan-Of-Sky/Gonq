// HBoxWithStrut.java
// Another test of the box layout manager using the Box utility class.
// This version separates several components with a fixed width gap.
//
import java.awt.*;
//import java.awt.event.*;
import javax.swing.*;

public class HBoxWithStrut extends JFrame {

  
	private static final long serialVersionUID = -6055666868065024584L;

  public HBoxWithStrut() {
    super("Box & Strut Frame");
    setSize(370, 80);
    Box box = Box.createHorizontalBox();
    setContentPane(box);
    for (int i = 0; i < 3; i++) {
      Button b = new Button("B" + i);
      box.add(b);
    }

    // Add a spacer between the first three buttons and the last three
    box.add(Box.createHorizontalStrut(10));
    for (int i = 3; i < 6; i++) {
      Button b = new Button("B" + i);
      box.add(b);
    }
    setDefaultCloseOperation(EXIT_ON_CLOSE);
    setVisible(true);
  }

  public static void main(String args[]) {
     // Make all components to configured by the event dispatch thread.
     // This is the thread that passes user provoked events such as mouse clicks to 
     // the GUI components which have registered listeners for the events.
     // The following code fragment forces the statements in the run() method to be executed in the
     // event dispatch thread. 
     EventQueue.invokeLater(new Runnable()
         {
            public void run()
            {
               new HBoxWithStrut(); 	
            }
         });
    

  }
}
