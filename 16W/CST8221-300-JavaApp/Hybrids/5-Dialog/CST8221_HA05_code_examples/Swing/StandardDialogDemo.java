/*  CST8221-JAP: HA 05
    File name: StandardDialogDemo.java 
*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
/**
 * This class demonstrates the standard dialogs provided by the Swing API.
 * @author S.Ranev
 * @version 1.16.1
 * @since 1.5
 * @see JOptionPane
 */

public class StandardDialogDemo extends JFrame implements ActionListener {
    private static final long serialVersionUID = 3810761338269038999L;
    public StandardDialogDemo() {
        // set frame title
        super("Standard JOptionPane Dialogs");
        // get the content pane
        Container pane = this.getContentPane();
        pane.setLayout(new GridLayout(4, 3,10,10));// change the layout
        // create buttons
        JButton aButton = new JButton("Plain Message Box");
        pane.add(aButton);
        aButton.addActionListener(this);

        aButton = new JButton("Warning Message Box");
        pane.add(aButton);
        aButton.addActionListener(this);

        aButton = new JButton("Error Message Box");
        pane.add(aButton);
        aButton.addActionListener(this);

        aButton = new JButton("Information Message Box");
        pane.add(aButton);
        aButton.addActionListener(this);

        aButton = new JButton("Confirmation Dialog Box");
        pane.add(aButton);
        aButton.addActionListener(this);

        aButton = new JButton("Confirmation Dialog Box with Cancel");
        pane.add(aButton);
        aButton.addActionListener(this);

        aButton = new JButton("Multiple Option Dialog Box");
        pane.add(aButton);
        aButton.addActionListener(this);

        aButton = new JButton("Input Dialog Box");
        pane.add(aButton);
        aButton.addActionListener(this);

        aButton = new JButton("Chooser Dialog Box");
        pane.add(aButton);
        aButton.addActionListener(this);
        
        aButton = new JButton("Custom Icon Message");
        pane.add(aButton);
        aButton.addActionListener(this);
        // set the frame
        this.setContentPane(pane);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocation(100, 100);
        this.pack();
    }
    //handle events
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("Plain Message Box")) {
            JOptionPane.showMessageDialog(this, "This is a plain message !!!", "Read This", JOptionPane.PLAIN_MESSAGE);
        } else if (e.getActionCommand().equals("Warning Message Box")) {
            JOptionPane.showMessageDialog(null, "Don't charge your iPhone in a microwave oven!", "Warning", JOptionPane.WARNING_MESSAGE);
        } else if (e.getActionCommand().equals("Error Message Box")) {
            JOptionPane.showMessageDialog(this, "Your program has stopped working !", "Error", JOptionPane.ERROR_MESSAGE);
        } else if (e.getActionCommand().equals("Information Message Box")) {
            JOptionPane.showMessageDialog(this, "You better work on your assignment...", "Information", JOptionPane.INFORMATION_MESSAGE);
        } else if (e.getActionCommand().equals("Confirmation Dialog Box")) {
            int result = JOptionPane.showConfirmDialog(this, "Do you want me to erase your hard drive ?", "Answer this Question", JOptionPane.YES_NO_OPTION);
            if (result == JOptionPane.YES_OPTION) {
                System.out.println("OK, I'm erasing it now ...");
            } else {
                System.out.println("Fine then, you clean it up!");
            }
        } else if (e.getActionCommand().equals("Confirmation Dialog Box with Cancel")) {
            int result = JOptionPane.showConfirmDialog(this, "Do you want to overwrite the file ?", "Answer this Question", JOptionPane.YES_NO_CANCEL_OPTION);
            switch (result) {
                case JOptionPane.YES_OPTION:
                    System.out.println("OK, but don't come crying to me once its gone.");
                    break;
                case JOptionPane.NO_OPTION:
                    System.out.println("Well you should pick a new name then.");
                    break;
                case JOptionPane.CANCEL_OPTION:
                    System.out.println("OK, I'll ask you again later.");
                    break;
                case JOptionPane.CLOSED_OPTION:
                    System.out.println("Do not play ostrich!");
                    break;
                default:
                  System.out.println("Sould never come here");  
            }
        } else if (e.getActionCommand().equals("Multiple Option Dialog Box")) {
            Object[] options = {"Outstanding", "Excellent", "Good", "Fair", "Poor"};
            int result = JOptionPane.showOptionDialog(this, "What do you think of this HybridAct ?", "Pick an Option", JOptionPane.DEFAULT_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[0]);
            if (result > 0 && result < options.length) {
                System.out.print("So,...,you think the HA5 is " + options[result] + " ...");
            }
            if (result < 3) {
                System.out.println("Thank you!");
            } else {
                System.out.println("but I put a lot of work into it !");
            }
        } else if (e.getActionCommand().equals("Input Dialog Box")) {
            String inputValue = JOptionPane.showInputDialog("Please input your name");
            System.out.println("Your name is " + inputValue);
        } else if (e.getActionCommand().equals("Chooser Dialog Box")) {
           Object[] options = {"Apple", "Orange", "Strawberry", "Bannana", "Cherry"};
//           Object[] options = {new Double(1.0),new Double(2.0),new Double(3.0),new Double(1.0)};
            Object selectedValue = JOptionPane.showInputDialog(null, "Choose your favorite fruit", "Fruit Information", JOptionPane.INFORMATION_MESSAGE, null, options, options[1]);
//           System.out.println(selectedValue + " is of type : " +selectedValue.getClass().getName());  
            System.out.println(selectedValue + "s sure do taste yummy.");     
       }else if (e.getActionCommand().equals("Custom Icon Message")) {
          JOptionPane.showMessageDialog(null, "Have a nice day.", "Custom Icon",
          JOptionPane.INFORMATION_MESSAGE, new ImageIcon(getClass().getResource("smile.gif")));
       }	
    }

    /**
     * Starts the application.
     * @param args an array of command-line arguments
     */
    public static void main(String[] args) {
        //Schedule a job for the event-dispatching thread:
        //creating and showing this application's GUI.
        //SwingUtilities.invokeLater() simply calls java.awt.EventQueue.invokeLater().
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new StandardDialogDemo().setVisible( true );
            }
        });
    }
}
