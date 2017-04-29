// CardLayoutDemo.java
// Demonstrates the CardLayout Manager
// Author: Svillen Ranev
import java.awt.CardLayout;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

public class CardLayoutDemo implements MouseListener {
   private JPanel p1, p2, p3, p4; // panels to be used as cards
   private JLabel l1, l2, l3, l4; // labels to display text in panels
   private CardLayout myCard; // card layout
   private JFrame frame; // application frame
   private JPanel pane; // panel to add to the frame content pane
   private Border thickLine; //panel's border
  // Set up the GUI 
  public void setAndLaunch() {
	// Create the application frame
	frame = new JFrame ("CardLayout Demo");
	// Create a Card Layout manager
	myCard = new CardLayout();
	// Create a panel to be added to the content pane of the frame
	pane = new JPanel();
	// Set the pane layout
	pane.setLayout(myCard);
	// Create a border aropund the pane
	thickLine = new LineBorder(Color.RED,10,true);
	pane.setBorder(thickLine);

	// Create the panels to be used as cards
	p1 = new JPanel();
	p2 = new JPanel();
	p3 = new JPanel();
	p4 = new JPanel();

	// Create a label to attach to each panel, and
	// change the color of each panel

	l1 = new JLabel("This is the first Panel - Press a mouse button");
	p1.setBackground(Color.YELLOW);
	p1.add(l1);
 	
	l2 = new JLabel("This is the second Panel");
	p2.setBackground(Color.GREEN);
	p2.add(l2);

	l3 = new JLabel("This is the third Panel");
	p3.setBackground(Color.MAGENTA);
	p3.add(l3);

	l4 = new JLabel("This is the fourth Panel");
	p4.setBackground(Color.CYAN);
	p4.add(l4);

	// Set up the event handling.
	p1.addMouseListener(this);
	p2.addMouseListener(this);
	p3.addMouseListener(this);
	p4.addMouseListener(this);
	
	// Add each panel to the CardLayout
	// Name the panels so they can be called by name
	pane.add(p1, "First");
	pane.add(p2, "Second");
	pane.add(p3, "Third");
	pane.add(p4, "Fourth");

	// Display the first panel.
	myCard.show(pane, "First");
   frame.add(pane);
	frame.setSize(300,300);
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setVisible(true);
  }
   // process the mouse pressed evente
    public void mousePressed(MouseEvent e) {
	    // Switch to the next card
	    myCard.next(pane);
    }
    //implement the rest of the MouseListener metods with NOP
    public void mouseReleased(MouseEvent e) { }
    public void mouseClicked(MouseEvent e) { }
    public void mouseEntered(MouseEvent e) { }
    public void mouseExited(MouseEvent e) { }
   
   // the main method
   public static void main (String args[]) {
   	 // Make all components to configured by the event dispatch thread.
     // This is the thread that passes user provoked events such as mouse clicks to 
     // the GUI components which have registered listeners for the events.
     // The following code fragment forces the statements in the run() method to be executed in the
     // event dispatch thread. 
     EventQueue.invokeLater(new Runnable()
         {
            public void run()
            {
              CardLayoutDemo cld = new CardLayoutDemo();
	          cld.setAndLaunch(); 
            }
         });
   	
   	
   	
   	
	 
    }
}
