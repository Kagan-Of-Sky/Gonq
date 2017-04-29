/* File name:   CalculatorView.java
 * Author:      Mark Kaganovsky
 * Course:      CST8221 - JAP, Lab Section: 302
 * Assignment:  2
 * Date:        Mar 10 2016
 * Professor:   Svillen Ranev
 * 
 * Purpose:     To build the GUI for the calculator view and to handle all events for
 *              this view (Controller class).
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

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.UIManager;




/**
 * Builds the calculators GUI.
 * 
 * @author  Mark Kaganovsky
 * @version 1.7
 * @see     JPanel
 * @since   1.8.0_20
 */
public class CalculatorView extends JPanel {
	/** Auto generated serialVersionUID */
	private static final long serialVersionUID = 7203708147985052199L;
	
	
	
	
	/** {@value} - The error labels Float value. */
	private static final String EL_TEXT_F = "F";
	
	/** {@value} - The error labels Integers value. */
	private static final String EL_TEXT_I = "I";
	
	/** {@value} - The error labels error value. */
	private static final String EL_TEXT_E = "E";
	
	/** {@value} - The display's initial value. */
	private static final String D_DEFAULT = "0.0";
	
	/** {@value} - Display's error text. */
	private static final String D_ERROR_TEXT = "--";
	
	/** {@value} - Backspace button display text and action command. */
	private static final String BSB_TAC = "\u21D0";
	
	/** {@value} - Backspace button mnemonic. */
	private static final char BSB_MNEMONIC = 'B';
	
	/** {@value} - Clear buttons text and action command. */
	private static final String CB_TAC  = "C";
	
	/** {@value} - Equal buttons text and action command. */
	private static final String EB_TAC = "=";
	
	
	
	
	// Below are display accuracy text and action commands.
		/** {@value} - Int checkbox text and action command. */
		private static final String IC_TAC = "Int";
		
		/** {@value} - Tenths radio button text and action command. */
		private static final String TRB_TAC = ".0";
		
		/** {@value} - Hundredths radio button text and action command. */
		private static final String HRB_TAC = ".00";
		
		/** {@value} - Scientific radio button text and action command. */
		private static final String SRB_TAC = "Sci";
	
	
	
	
	// Below are the text and action commands for the operators + - * and /
		/** {@value} - The text and action command of the divide button. */
		private static final String DIV_TAC = "\u2215";
		
		/** {@value} - The text and action command of the multiply button. */
		private static final String MUL_TAC = "\u2217";
		
		/** {@value} - The text and action command of the multiply button. */
		private static final String SUB_TAC = "\u2212";
		
		/** {@value} - The text and action command of the add button. */
		private static final String ADD_TAC = "+";
	
	
	
	
	// Below is data used for the keypad buttons.
		/** {@value} - The text and action command of the dot button. */
		private static final String DB_TAC = "\u2219";
		
		/** {@value} - The text and action command of the sign change button. */
		private static final String SC_TAC = "\u2213";
		
		/** keypad buttons text and action command. */
		private static final String[] KB_TAC = {"7",       "8",    "9",       DIV_TAC,
		                                        "4",       "5",    "6",       MUL_TAC,
		                                        "1",       "2",    "3",       SUB_TAC,
		                                        SC_TAC,    "0",    DB_TAC,    ADD_TAC};
		
		/** keypad buttons background color. */
		private static final Color[] KB_B_COLOR = {Color.BLUE, Color.BLUE, Color.BLUE, Color.BLUE,
		                                           Color.BLUE, Color.BLUE, Color.BLUE, Color.BLUE,
		                                           Color.BLUE, Color.BLUE, Color.BLUE, Color.BLUE,
		                                           Color.BLUE, Color.BLUE, Color.BLUE, Color.BLUE};
		
		/** keypad buttons foreground color. */
		private static final Color[] KB_F_COLOR = {Color.BLACK, Color.BLACK, Color.BLACK, Color.YELLOW,
		                                           Color.BLACK, Color.BLACK, Color.BLACK, Color.YELLOW,
		                                           Color.BLACK, Color.BLACK, Color.BLACK, Color.YELLOW,
		                                           Color.BLACK, Color.BLACK, Color.BLACK, Color.YELLOW};
	
	
	
	
	// Below are references to GUI components that the Controller needs.
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
				JButton clearButtonTop  = createButton(CB_TAC, CB_TAC, Color.BLACK, Color.RED, handler);
				JButton equalsButtonTop = createButton(EB_TAC, EB_TAC, Color.BLACK, Color.YELLOW, handler);
				
				JPanel clearEqualsPanel = new JPanel(new GridLayout(1, 2, 3, 0));
				clearEqualsPanel.add(clearButtonTop);
				clearEqualsPanel.add(equalsButtonTop);
			
			// Buttons below keypad
				JButton equalsButtonBottom = createButton(EB_TAC, EB_TAC, Color.BLACK, Color.YELLOW, handler);
				JButton clearButtonBottom  = createButton(CB_TAC, CB_TAC, Color.BLACK, Color.RED, handler);
				
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
		JPanel keypadPanel = new JPanel(new GridLayout(4, 4, 3, 3)); // 4 by 4 panel to hold the keypad buttons.
		
		for(int i=0; i<KB_TAC.length; ++i){
			JButton button = createButton(KB_TAC[i], KB_TAC[i], KB_F_COLOR[i], KB_B_COLOR[i], handler);
			
			// Check if the button created is the dot button.
			if(DB_TAC.equals(KB_TAC[i])){
				dotButton = button;
			}
			
			keypadPanel.add(button);
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
		JButton backspaceButton = createButton(BSB_TAC, BSB_TAC, Color.RED, Color.WHITE, handler);
		backspaceButton.setFont(UIManager.getDefaults().getFont("Button.font"));
		backspaceButton.setToolTipText("Backspace: ALT+B");
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
		JCheckBox intToggle = new JCheckBox(IC_TAC);
		intToggle.setActionCommand(IC_TAC);
		intToggle.addActionListener(handler);
		intToggle.setBackground(Color.GREEN);
		
		// Create the floating point precision radio buttons and the radio button group.
		JRadioButton tenthsRadioButton     = new JRadioButton(TRB_TAC);
		JRadioButton hundredthsRadioButton = new JRadioButton(HRB_TAC);
		JRadioButton scientificRadioButton = new JRadioButton(SRB_TAC);
		
		// Customize the tenths button
		tenthsRadioButton.setBackground(Color.YELLOW);
		tenthsRadioButton.setActionCommand(TRB_TAC);
		tenthsRadioButton.addActionListener(handler);
		
		// Customize the hundredths button
		hundredthsRadioButton.setBackground(Color.YELLOW);
		hundredthsRadioButton.setActionCommand(HRB_TAC);
		hundredthsRadioButton.addActionListener(handler);
		
		// Customize the sci button
		scientificRadioButton.setBackground(Color.YELLOW);
		scientificRadioButton.setActionCommand(SRB_TAC);
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
	 * Event handler for all events that the {@link CalculatorView} generates.<br>
	 * Links the {@link CalculatorView} to the {@link CalculatorModel}.
	 * 
	 * @author  Mark Kaganovsky
	 * @version 1.7
	 * @see     ActionListener
	 * @see     CalculatorModel
	 * @since   1.8.0_20
	 */
	private class Controller implements ActionListener {
		/** The model which handles calculations. */
		private CalculatorModel calculatorModel;
		
		/** True if the dot has been pressed. */
		private boolean dotPressed;
		
		/** True if the display needs to be cleared. */
		private boolean clearDisplay;
		
		/** True if in error state */
		private boolean inErrorState;
		
		private CalculatorModel.DISPLAY_MODES lastDisplayMode;
		
		/** Used to quickly check if the action command is a digit. */
		private HashSet<String> digitSet;
		
		/** Maps the operations (+, -, *, /) to the constants in {@link CalculatorModel} */
		private HashMap<String, CalculatorModel.OPERATIONS> operatorTable;
		
		/** Maps the Display precision buttons (Int, .0, .00, and Sci) to the constants in {@link CalculatorModel} */
		private HashMap<String, CalculatorModel.DISPLAY_MODES> displayPrecisionTable;
		
		
		
		
		/** Default constructor for this controller. */
		public Controller() {
			calculatorModel = new CalculatorModel();
			
			CalculatorModel.DISPLAY_MODES initDisplayMode = CalculatorModel.DISPLAY_MODES.TWO_DECIMAL_PLACES;
			calculatorModel.setDisplayMode(initDisplayMode);
			lastDisplayMode = initDisplayMode;
			
			dotPressed   = false;
			clearDisplay = true;
			inErrorState = false;
			
			// Initialize the digit set.
			digitSet = new HashSet<>(Arrays.asList("0", "1", "2", "3", "4", "5", "6", "7", "8", "9"));
			
			// Initialize the operator table.
			operatorTable = new HashMap<>();
			operatorTable.put(ADD_TAC, CalculatorModel.OPERATIONS.ADD);
			operatorTable.put(SUB_TAC, CalculatorModel.OPERATIONS.SUBTRACT);
			operatorTable.put(MUL_TAC, CalculatorModel.OPERATIONS.MULTIPLY);
			operatorTable.put(DIV_TAC, CalculatorModel.OPERATIONS.DIVIDE);
			
			// Initialize the display precision table
			displayPrecisionTable = new HashMap<>();
			displayPrecisionTable.put(IC_TAC, CalculatorModel.DISPLAY_MODES.INTEGER);
			displayPrecisionTable.put(TRB_TAC, CalculatorModel.DISPLAY_MODES.ONE_DECIMAL_PLACE);
			displayPrecisionTable.put(HRB_TAC, CalculatorModel.DISPLAY_MODES.TWO_DECIMAL_PLACES);
			displayPrecisionTable.put(SRB_TAC, CalculatorModel.DISPLAY_MODES.SCIENTIFIC);
		}
		
		/**
		 * Handle all events generated by the {@link CalculatorView}.
		 * 
		 * @param event The {@link ActionEvent} a gui component generated.
		 */
		@Override public void actionPerformed(ActionEvent event) {
			String actionCommand = event.getActionCommand();
			
			// Clear pressed.
			if(CB_TAC.equals(actionCommand)){
				inErrorState = false;
				clearDisplay = true;
				dotPressed   = false;
				
				calculatorModel.clearErrorState();
				display.setText(calculatorModel.getFormattedZero());
				
				if(dotButton.isEnabled()){
					setErrorLabelFloat();
				}
				else{
					setErrorLabelInteger();
				}
				
				return;
			}
			
			// Precision change.
			else if(displayPrecisionTable.containsKey(actionCommand)){
				CalculatorModel.DISPLAY_MODES displayMode = displayPrecisionTable.get(actionCommand);
				
				if(CalculatorModel.DISPLAY_MODES.INTEGER == displayMode){ // Integer button was toggled.
					if(dotButton.isEnabled()){ // Switching to integer mode.
						// Disable the dot button.
						dotButton.setEnabled(false);
						dotButton.setBackground(Color.GRAY);
						
						// Set calculator mode to integer.
						calculatorModel.setDisplayMode(displayMode);
						
						if(!inErrorState){
							setErrorLabelInteger();
							display.setText(display.getText().split("\\.")[0]);
							dotPressed = false;
						}
					}
					else{ // Switching to float mode.
						dotPressed = false;
						
						// Enable the dot button.
						dotButton.setEnabled(true);
						dotButton.setBackground(Color.BLUE);
						
						// Set the calculator model to the last precision the user used.
						calculatorModel.setDisplayMode(lastDisplayMode);
						
						if(!inErrorState){
							setErrorLabelFloat();
						}
					}
				}
				else{ // Float precision radio button clicked.
					lastDisplayMode = displayMode;
					if(dotButton.isEnabled()){ // If in float mode, update the calculators mode.
						calculatorModel.setDisplayMode(lastDisplayMode);
					}
				}
				
				return;
			}
			
			// If in error state do not continue.
			if(inErrorState){
				return;
			}
			
			// Digit
			if(digitSet.contains(actionCommand)){
				if(clearDisplay){
					display.setText("");
					clearDisplay = false;
				}
				display.setText(display.getText() + actionCommand);
			}
			
			// Operator
			else if(operatorTable.containsKey(actionCommand)){
				String displayText = display.getText();
				
				if(!calculatorModel.setNum1(displayText)){
					setErrorState();
					return;
				}
				calculatorModel.setOperation(operatorTable.get(actionCommand));
				clearDisplay = true;
			}
			
			// Equals
			else if(EB_TAC.equals(actionCommand)){
				// Could not set the number.
				if(!calculatorModel.setNum2(display.getText())){
					setErrorState();
					return;
				}
				
				String result = calculatorModel.performCalculation();
				if(null == result){
					inErrorState = true;
					setErrorState();
				}
				else{
					display.setText(result);
					clearDisplay = true;
				}
			}
			
			// Sign change
			else if(SC_TAC.equals(actionCommand)){
				if(clearDisplay){
					display.setText("-");
					clearDisplay = false;
				}
				else{
					String displayText = display.getText();
					if(displayText.startsWith("-")){
						display.setText(displayText.substring(1));
					}
					else{
						display.setText("-" + displayText);
					}
				}
			}
			
			// Dot button
			else if(DB_TAC.equals(actionCommand)){
				if(!dotPressed){
					if(clearDisplay){
						display.setText("0.");
						clearDisplay = false;
					}
					else{
						display.setText(display.getText() + ".");
					}
					dotPressed = true;
				}
			}
			
			// Backspace button
			else if(BSB_TAC.equals(actionCommand)){
				String displayText = display.getText();
				
				// A positive number with a single digit or a negative number with a single digit.
				if((displayText.length() == 1) ||
				   (displayText.length() == 2 && displayText.charAt(0) == '-'))
				{
					display.setText(calculatorModel.getFormattedZero());
					clearDisplay = true;
					dotPressed = false;
				}
				else{
					// Deleting a dot.
					if(displayText.endsWith(".")){
						dotPressed = false;
					}
					display.setText(displayText.substring(0, displayText.length()-1));
				}
			}
		}
		
		
		
		
		/** Helper function, sets the error state to true, sets the display text, styles the error label. */
		private void setErrorState(){
			inErrorState = true;
			display.setText(D_ERROR_TEXT);
			error.setText(EL_TEXT_E);
			error.setBackground(Color.RED);
		}
		
		/** Helper function, simply styles the error label for float mode. */
		private void setErrorLabelFloat(){
			error.setText(EL_TEXT_F);
			error.setBackground(Color.YELLOW);
		}
		
		/** Helper function, simply styles the error label for float mode. */
		private void setErrorLabelInteger(){
			error.setText(EL_TEXT_I);
			error.setBackground(Color.GREEN);
		}
	}
}
