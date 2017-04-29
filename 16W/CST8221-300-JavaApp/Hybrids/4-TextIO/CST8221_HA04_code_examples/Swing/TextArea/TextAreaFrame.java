// Fig. 14.47: TextAreaFrame.java
// Copying selected text from one text area to another.
// Removing text from text area
// Modified by S. Ranev 
// version: 1.16.1
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.*;
import java.awt.*;

public class TextAreaFrame extends JFrame {  
   /** serial version */
   private static final long serialVersionUID = -1691651597945213555L;
   /** displays demo string */
   private JTextArea textArea1; 
   /** highlighted text is copied here */
   private JTextArea textArea2; 
   /** initiates copying of text */
   private JButton copyJButton; 
   /** initiates removing of text */
   private JButton removeJButton; 
   
   /** no-argument constructor */
   public TextAreaFrame(){
      super( "TextArea Demo" );
      createGUI(); 
   }
   private void createGUI(){   
      Box box = Box.createHorizontalBox(); // create box
      String demo = "This is a demo string to\n" + 
         "illustrate copying text\nfrom one textarea to \n" +
         "another text area using an\nexternal event\n";

      textArea1 = new JTextArea( demo, 10, 15 ); // create textarea1
      textArea1.setMargin(new Insets(0,5,5,0)); //set text area margins
      box.add( new JScrollPane( textArea1 ) ); // add scrollpane to text area

      JPanel buttonPane = new JPanel(); // create a panel to hold buttons
      buttonPane.setLayout(new BorderLayout());// change layout
      buttonPane.setBackground(Color.BLUE);
      copyJButton = new JButton( "Copy >>>" ); // create copy button
      removeJButton = new JButton( "Remove <<<" );// create remove button
      buttonPane.add(copyJButton,BorderLayout.NORTH); //add to panel
      buttonPane.add(removeJButton,BorderLayout.SOUTH);// add to panel
      box.add( buttonPane); // add copy button to box
      
      textArea2 = new JTextArea( 10, 15 ); // create second textarea
      textArea2.setEditable( false ); // disable editing
      textArea2.setMargin(new Insets(0,5,5,0)); //set text area margins
      box.add( new JScrollPane( textArea2 ) ); // add scrollpane to text area

      add( box ); // add box to frame
      //add event handler to copy button
      copyJButton.addActionListener(

         new ActionListener() // anonymous inner class
         {   
            // set text in textArea2 to selected text from textArea1
            public void actionPerformed( ActionEvent event )
            {
               textArea2.setText( textArea1.getSelectedText() );
            } // end method actionPerformed
         } // end anonymous inner class
      ); // end call to addActionListener

     //add event handler to remove button
      removeJButton.addActionListener(

         new ActionListener() // anonymous inner class
         {   
            // set text in textArea2 to selected text from textArea1
            @Override
            public void actionPerformed( ActionEvent event )
            {
               textArea2.setText("");
            } // end method actionPerformed
         } // end anonymous inner class
      ); // end call to addActionListener
      
   } // end TextAreaFrame constructor

} // end class TextAreaFrame

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
