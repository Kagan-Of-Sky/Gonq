// HBox.java
// A quick test of the BoxLayout manager using the Box utility class.
//
import java.awt.*;
import javax.swing.*;

public class HBox extends JFrame {

  
	private static final long serialVersionUID = 6483680529739015493L;

 public HBox() {
    super("Horizontal Box Test Frame");
    setSize(200, 100);
    Panel box = new Panel();

    // Use BoxLayout.Y_AXIS below if you want a vertical box
    box.setLayout(new BoxLayout(box, BoxLayout.X_AXIS)); 
    setContentPane(box);
    for (int i = 0; i < 3; i++) {
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
               new HBox();
            }
         });
    
  }
}
