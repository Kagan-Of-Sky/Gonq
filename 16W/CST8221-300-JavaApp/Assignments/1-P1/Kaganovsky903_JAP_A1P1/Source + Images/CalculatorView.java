/* File name:   CalculatorView.java
 * Author:      Mark Kaganovsky
 * Course:      CST8221 - JAP, Lab Section: 302
 * Assignment:  1
 * Date:        Feb 24 2016
 * Professor:   Svillen Ranev
 * Purpose:     To build the GUI for the calculator app.
 * 
 * Class list:  CalculatorView
 *              Controller
 */

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;




/**
 * Builds the calculators GUI.
 * 
 * @author  Mark Kaganovsky
 * @version 1.6
 * @see     JPanel
 * @since   1.8.0_20
 */
public class CalculatorView extends JPanel {
	/** Auto generated serialVersionUID */
	private static final long serialVersionUID = 1963356808069533934L;
	
	
	
	
	/** {@value} - The error labels 'F' value. */
	private static final String EL_TEXT_F = "F";
	
	/** {@value} - The display's initial value. */
	private static final String D_DEFAULT = "0.0";
	
	/** {@value} - Backspace button display text and action command. */
	private static final String BSB_TEXT_AC = "\u21D0";
	
	/** {@value} - Backspace button mnemonic. */
	private static final char BSB_MNEMONIC = 'B';
	
	/** {@value} - Int checkbox text and action command. */
	private static final String IC_TEXT_AC = "Int";
	
	/** {@value} - Tenths radio button text and action command. */
	private static final String TRB_TEXT_AC = ".0";
	
	/** {@value} - Hundredths radio button text and action command. */
	private static final String HRB_TEXT_AC = ".00";
	
	/** {@value} - Scientific radio button text and action command. */
	private static final String SRB_TEXT_AC = "Sci";
	
	/** {@value} - The text and action command of the dot button. */
	private static final String DB_TEXT_AC = "\u2219";
	
	/** An immutable list which contains the keypad buttons text and action command. 
	 *  Can not be modified, exception will be thrown at run time.
	 */
	private static final List<String> KB_TEXT_AC =
	  Collections.unmodifiableList(Arrays.asList("7",      "8",  "9",      "\u2215",
	                                             "4",      "5",  "6",      "\u2217",
	                                             "1",      "2",  "3",      "\u2212",
	                                             "\u2213", "0",  DB_TEXT_AC, "+"));
	
	/** {@value} - Clear buttons text and action command. */
	private static final String CB_TEXT_AC  = "C";
	
	/** {@value} - Equal buttons text and action command. */
	private static final String EB_TEXT_AC = "=";
	
	
	
	
	/** The calculator display field reference. */
	private JTextField display;
	
	/** The error display label reference. */
	private JLabel error;
	
	/** The decimal point (dot) button reference. */
	private JButton dotButton;
	
	
	
	
	/** Default constructor, creates the GUI. */
	public CalculatorView() {
		// Set the outermost border and color.
		setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));
		setBackground(Color.BLACK);
		setLayout(new BorderLayout());
		
		// Event handler
		Controller handler = new Controller();
		
		// Create the error label, the display, and the backspace button.
		JPanel errDisBackPanel = createErrDisBackPanel(handler);
		
		// Create the Integer toggle and the floating point precision radio button group.
		Box precisionBox = createPrecisionBox(handler);
		
		// Create the panel to hold the errorDisplayBackspacePanel and the precisionBox
		JPanel errDisBackPrecPanel = new JPanel(new BorderLayout());
		errDisBackPrecPanel.add(errDisBackPanel, BorderLayout.NORTH);
		errDisBackPrecPanel.add(precisionBox, BorderLayout.SOUTH);
		
		// Create keypad
		JPanel keypadPanel = createKeypad(handler);
		
		// Create C and = buttons
			// Buttons above keypad
				JButton clearButtonTop  = createButton(CB_TEXT_AC, CB_TEXT_AC, Color.BLACK, Color.RED, handler);
				JButton equalsButtonTop = createButton(EB_TEXT_AC, EB_TEXT_AC, Color.BLACK, Color.YELLOW, handler);
				
				JPanel clearEqualsPanel = new JPanel(new GridLayout(1, 2, 3, 0));
				clearEqualsPanel.add(clearButtonTop);
				clearEqualsPanel.add(equalsButtonTop);
			
			// Buttons below keypad
				JButton equalsButtonBottom = createButton(EB_TEXT_AC, EB_TEXT_AC, Color.BLACK, Color.YELLOW, handler);
				JButton clearButtonBottom  = createButton(CB_TEXT_AC, CB_TEXT_AC, Color.BLACK, Color.RED, handler);
				
				JPanel equalsClearPanel = new JPanel(new GridLayout(1, 2, 3, 0));
				equalsClearPanel.add(equalsButtonBottom);
				equalsClearPanel.add(clearButtonBottom);
		
		// Create the panel and layout for the keypad and the top clear equals buttons and the bottom equals clear buttons 
			JPanel keypadClrEqPanels = new JPanel(new BorderLayout(0, 2));
			
			keypadClrEqPanels.add(clearEqualsPanel, BorderLayout.NORTH);
			keypadClrEqPanels.add(keypadPanel, BorderLayout.CENTER);
			keypadClrEqPanels.add(equalsClearPanel, BorderLayout.SOUTH);
		
		// Add all panels.
			add(errDisBackPrecPanel, BorderLayout.NORTH);
			add(keypadClrEqPanels, BorderLayout.CENTER);
	}
	
	
	
	
	/**
	 * This method is responsible for creating buttons with the same basic properties. 
	 * 
	 * @param text     The text to be shown on the button.
	 * @param ac       The action command string for the button.
	 * @param fg       Foreground color of the button.
	 * @param bg       Background color of the button.
	 * @param handler  An event handler for this button.
	 * 
	 * @return The button created.
	 */
	private JButton createButton(String text, String ac, Color fg, Color bg, ActionListener handler){
		JButton button = new JButton(text);
		
		// Set button action command if necessary
		if(ac != null){
			button.setActionCommand(ac);
		}
		
		// Set button colors
		button.setForeground(fg);
		button.setBackground(bg);
		
		// Set button font
		Font defaultFont = button.getFont();
		button.setFont(new Font(defaultFont.getName(), defaultFont.getStyle(), 21));
		
		// Register action listener
		button.addActionListener(handler);
		
		return button;
	}
	
	
	
	
	/**
	 * Creates the keypad panel and returns a reference to it.
	 * 
	 * @param handler The event handler for all of the buttons on the keypad panel.
	 * @return A reference to the panel created.
	 */
	private JPanel createKeypad(ActionListener handler){
		JPanel keypadPanel  = new JPanel(new GridLayout(4, 4, 3, 3)); // 4 by 4 panel to hold the keypad buttons.
		
		int i = 0; // Used to detect whether we are in the 4th column (the column with the /*- and +).
		
		// Create and add all keypad buttons
		for(String string : KB_TEXT_AC){
			Color fg; // Foreground color.
			
			// Determine the foreground color of the button (if the button text is a /*- or + then it must have a yellow font).
			if(i == 3){    // Button text is one of /*- or +
				fg = Color.YELLOW;
				i = 0;
			}
			else{                  // Button is either 0-9, the positive/negative sign (u213) or the dot 
				fg = Color.BLACK;
				i++;
			}
			
			// Create the button.
			JButton newButton = createButton(string, string, fg, Color.BLUE, handler);
			
			// Check if the button is the dot button.
			if(string.equals(DB_TEXT_AC)){
				dotButton = newButton;
			}
			
			// Add the button
			keypadPanel.add(newButton);
		}
		
		return keypadPanel;
	}
	
	
	
	
	/**
	 * Creates the error, display, and backspace panel.
	 * 
	 * @param handler The handler for the backspace button.
	 * @return A reference to the panel created.
	 */
	private JPanel createErrDisBackPanel(ActionListener handler){
		// Create the error display.
		error = new JLabel(EL_TEXT_F);
		error.setHorizontalAlignment(JLabel.CENTER);
		error.setPreferredSize(new Dimension(25, 25));
		error.setBackground(Color.YELLOW);
		error.setOpaque(true);
		
		// Create the display.
		display = new JTextField(D_DEFAULT, 16);
		display.setEditable(false);
		display.setHorizontalAlignment(JTextField.RIGHT);
		display.setPreferredSize(new Dimension(display.getPreferredSize().width, 30));
		
		// Create the backspace button.
		JButton backspaceButton = createButton(BSB_TEXT_AC, BSB_TEXT_AC, Color.RED, Color.WHITE, handler);
		backspaceButton.setToolTipText("Backspace: ALT+B");
		backspaceButton.setOpaque(false);
		backspaceButton.setContentAreaFilled(false);
		backspaceButton.setBorder(BorderFactory.createLineBorder(Color.RED));
		backspaceButton.setMnemonic(BSB_MNEMONIC);
		backspaceButton.setPreferredSize(new Dimension(25, 25));
		
		// Create the panel and add the widgets.
		JPanel errorDisplayBackspacePanel = new JPanel();
		errorDisplayBackspacePanel.add(error);
		errorDisplayBackspacePanel.add(display);
		errorDisplayBackspacePanel.add(backspaceButton);
		
		return errorDisplayBackspacePanel;
	}
	
	
	
	
	/**
	 * Create the Box which holds the precision widgets (the integer toggle, .0, .00, and sci widgets).
	 * 
	 * @param handler The event handler for the radio buttons created and the integer toggle checkbox.
	 * @return A reference to the Box created.
	 */
	private Box createPrecisionBox(ActionListener handler){
		// Create the Integer check box
		JCheckBox intToggle = new JCheckBox(IC_TEXT_AC);
		intToggle.setActionCommand(IC_TEXT_AC);
		intToggle.addActionListener(handler);
		intToggle.setBackground(Color.GREEN);
		
		// Create the floating point precision radio buttons and the radio button group.
		JRadioButton tenthsRadioButton     = new JRadioButton(TRB_TEXT_AC);
		JRadioButton hundredthsRadioButton = new JRadioButton(HRB_TEXT_AC);
		JRadioButton scientificRadioButton = new JRadioButton(SRB_TEXT_AC);
		
		// Customize the tenths button
		tenthsRadioButton.setOpaque(false);
		tenthsRadioButton.setActionCommand(TRB_TEXT_AC);
		tenthsRadioButton.addActionListener(handler);
		
		// Customize the hundredths button
		hundredthsRadioButton.setOpaque(false);
		hundredthsRadioButton.setActionCommand(HRB_TEXT_AC);
		hundredthsRadioButton.addActionListener(handler);
		
		// Customize the sci button
		scientificRadioButton.setOpaque(false);
		scientificRadioButton.setActionCommand(SRB_TEXT_AC);
		scientificRadioButton.addActionListener(handler);
		
		// Add the radio buttons to a group and select one as the default.
		ButtonGroup floatPrecisionGroup = new ButtonGroup();
		floatPrecisionGroup.add(tenthsRadioButton);
		floatPrecisionGroup.add(hundredthsRadioButton);
		floatPrecisionGroup.add(scientificRadioButton);
		hundredthsRadioButton.setSelected(true);
		
		// Create the panel which holds the float precision radio buttons.
		JPanel floatPrecisionPanel = new JPanel(new BorderLayout());
		floatPrecisionPanel.add(tenthsRadioButton, BorderLayout.WEST);
		floatPrecisionPanel.add(hundredthsRadioButton, BorderLayout.CENTER);
		floatPrecisionPanel.add(scientificRadioButton, BorderLayout.EAST);
		
		floatPrecisionPanel.setBackground(Color.YELLOW);
		
		floatPrecisionPanel.setMaximumSize(new Dimension(floatPrecisionPanel.getPreferredSize().width,
		                                                 floatPrecisionPanel.getPreferredSize().height));
		
		// Create the Box to hold the int toggle checkbox and the float precision buttons.
		Box precisionBox = Box.createHorizontalBox();
		precisionBox.add(Box.createHorizontalGlue());
		precisionBox.add(intToggle);
		precisionBox.add(Box.createHorizontalStrut(20));
		precisionBox.add(floatPrecisionPanel);
		precisionBox.add(Box.createHorizontalGlue());
		
		precisionBox.setBorder(BorderFactory.createMatteBorder(10, 0, 10, 0, Color.BLACK));
		precisionBox.setBackground(Color.BLACK);
		precisionBox.setOpaque(true);
		
		return precisionBox;
	}
	
	
	
	
	/**
	 * Event handler for all events that the {@link CalculatorView} generates.
	 * 
	 * @author  Mark Kaganovsky
	 * @version 1.1
	 * @see     ActionListener
	 * @since   1.8.0_20
	 */
	private class Controller implements ActionListener {
		
		/**
		 * In this implementation all it does is display the action command string onto the CalculatorView display.
		 */
		@Override public void actionPerformed(ActionEvent e) {
			display.setText(e.getActionCommand());
		}
		
	}
}
