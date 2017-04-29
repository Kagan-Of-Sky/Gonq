// HBoxWithGlue.java
// A quick test of the box layout manager using the Box utility class.
//
import java.awt.*;
import javax.swing.*;

public class HBoxWithGlue extends JFrame {

  
	private static final long serialVersionUID = -479663885641904996L;

 public HBoxWithGlue() {
    super("Box & Glue Frame");
    setSize(350, 100);
    Box box = Box.createHorizontalBox();
    setContentPane(box);
    box.add(Box.createHorizontalGlue());
    for (int i = 0; i < 3; i++) {
      Button b = new Button("B" + i);
      box.add(b);
    }
    box.add(Box.createHorizontalGlue());
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
              new HBoxWithGlue();	
            }
         }); 
   
  }
}
