/* CST8221-JAP: HA 02, Example 1
   File name: OpacityDemo.java
*/
import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
/**
Demonstrates how the JPanel works
and how the opaque property of JPanel (and JLabel)
affects the visibility of the other components.
@version 1.16.1
@author Svillen Ranev
*/
public class OpacityDemo extends JFrame {
	/* Swing components are serializable and require serialVersionUID */
	private static final long serialVersionUID = -4646210293427650879L;
/**
  Default constructor. Sets the GUI.
*/ 
  public OpacityDemo() {
    super("Opaque JPanel Demo");
    setSize(600, 150); 
    JPanel opaque = createTwoNestedPanels(true,"Opaque Inner Panel and Label");
    JPanel transparent = createTwoNestedPanels(false,"Transparent Inner Panel and Label");

    // Put it all together
//    getContentPane().setLayout(new FlowLayout());
//    getContentPane().add(opaque);
//    getContentPane().add(transparent);
    // faster implementation of the above lines
       // Get the Content Pane of the frame
       Container content = getContentPane();
       // change the default Layout Manager 
       content.setLayout(new FlowLayout());
       // add the first set of nested components to the content 
       content.add(opaque);
       // add the second set of nested components to the content
       content.add(transparent);
  }

/**  
   Creates a JPanel containing another JPanel containing a JLabel. 
   The inner JPanel's opacity property is set according to the value of the first parameter.
   A JLabel is placed inside the inner JPanel to give it some content.
   The JLabel's opacity property is set according to the value of the first parameter,
   and the JLabel's text is set according to the value of the second parameter.
   @param isOpaque if true, sets the opacity of the JLabel to true;
                   if false, sets the opacity of the inner JPanel to false.
   @return a set of nested components - a JLabel into JPanel into JPanel
*/
  public JPanel createTwoNestedPanels(boolean isOpaque, String labelText) {
    // create the outer panel
    JPanel outer = new JPanel();
    // create the inner panel
    JPanel inner = new JPanel();
    //set the background color,the borders, and the tooltips
    outer.setBackground(Color.yellow);
//  outer.setBorder(BorderFactory.createLineBorder(Color.blue));
    outer.setBorder(new CompoundBorder(BorderFactory.createLineBorder(Color.blue),
    new EmptyBorder(10,10,10,10)));
    outer.setToolTipText("Outer JPanel with yellow background");
    inner.setBackground(Color.gray);
    inner.setToolTipText("Inner JPanel with gray background");
//  inner.setBorder(BorderFactory.createLineBorder(Color.red));
    inner.setBorder(new CompoundBorder(BorderFactory.createLineBorder(Color.red),
    new EmptyBorder(10,10,10,10)));
    // change the opacity of the inner panel.
    if(!isOpaque)inner.setOpaque(isOpaque);
    // create and set the label
    JLabel label = new JLabel(labelText);
    label.setToolTipText("Label");
    label.setBorder(new CompoundBorder
      (BorderFactory.createRaisedBevelBorder(),
       new EmptyBorder(10,10,10,10)));
    //change the opacity of the label
    if(isOpaque) label.setOpaque(isOpaque);
    // stack the components
    inner.add(label);
    outer.add(inner);

    return outer;
  }
/** 
  The main method. Starts the application.
  @param args not used
*/ 
  public static void main(String[] args) {
   //Schedule a job for the event-dispatching thread:
   //creating and showing this application's GUI.
    EventQueue.invokeLater(new Runnable()
         {
            public void run()
            {
               OpacityDemo frame = new OpacityDemo();
               // set up the Close button (X) of the frame
               // no need to use explicitly a WindowListener. The line below will generate one for you. 
               frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
               // make the GUI visible
               frame.setVisible(true);	
            }
         });
  }
}
