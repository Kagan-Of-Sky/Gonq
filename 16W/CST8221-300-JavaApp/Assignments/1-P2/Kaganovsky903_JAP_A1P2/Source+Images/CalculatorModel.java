/* File name:   CalculatorModel.java
 * Author:      Mark Kaganovsky
 * Course:      CST8221 - JAP, Lab Section: 302
 * Assignment:  2
 * Date:        Mar 10 2016
 * Professor:   Svillen Ranev
 * Purpose:     A model for calculating the sum, difference,
 *              product, or quotient of 2 numbers.
 * 
 * Class list:  CalculatorModel
 * 
 *              Enumerations: OPERATIONS
 *                            DISPLAY_MODES
 *                            ERROR_STATES
 */

import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.util.HashMap;




/**
 * A model for calculating the sum, difference, product, or quotient of 2 numbers.<br>
 * 
 * Uses a {@link BigDecimal} to represent the numbers so overflow is not an issue.
 * 
 * @author  Mark Kaganovsky
 * @version 1.5
 * @since   1.8.0_20
 */
public class CalculatorModel {
	/**
	 * Enum representing the different operations this model supports.
	 * @version 1.0
	 * @author  Mark Kaganovsky
	 * @since   1.8.0_20
	 */
	public static enum OPERATIONS {
		/** Addition */
		ADD,
		/** Subtraction */
		SUBTRACT,
		/** Multiplication */
		MULTIPLY,
		/** Division */
		DIVIDE
	}
	
	
	
	
	/**
	 * Enum representing the different display modes this model supports.
	 * @version 1.0
	 * @author  Mark Kaganovsky
	 * @since   1.8.0_20
	 */
	public static enum DISPLAY_MODES {
		/** Integer display mode, 5/6 will be 0. */
		INTEGER,
		/** One decimal place. */
		ONE_DECIMAL_PLACE,
		/** Two decimal places. */
		TWO_DECIMAL_PLACES,
		/** Scientific display mode. */
		SCIENTIFIC
	}
	
	
	
	
	/**
	 * Enum representing the error states that this model can be in.
	 * @version 1.0
	 * @author  Mark Kaganovsky
	 * @since   1.8.0_20
	 */
	public static enum ERROR_STATES {
		/** No error state. */
		NO_ERROR_STATE,
		/** A non zero number divided by zero. */
		INFINITY,
		/** Zero divided by zero. */
		NAN
	}
	
	
	
	
	/** The first number (left operand). */
	private BigDecimal num1;
	
	/** The second number (right operand). */
	private BigDecimal num2;
	
	/** The current operator (+ - * /) */
	private OPERATIONS operation;
	
	/** Holds the current error state. */
	private ERROR_STATES errorState;
	
	/** Holds the current display mode. */
	private DISPLAY_MODES displayMode;
	
	/** Maps Display modes to their proper DecimalFormatter. */
	private HashMap<DISPLAY_MODES, DecimalFormat> displayFormatters;
	
	
	
	
	/**
	 * Default constructor.<br><br>
	 * 
	 * Initializes both numbers to 0.0,<br>
	 * sets the operation to add,<br>
	 * clears the error state,<br>
	 * sets the display mode to 2 decimal places.<br>
	 */
	public CalculatorModel() {
		num1        = BigDecimal.ZERO;
		num2        = BigDecimal.ZERO;
		operation   = OPERATIONS.ADD;
		errorState  = ERROR_STATES.NO_ERROR_STATE;
		displayMode = DISPLAY_MODES.TWO_DECIMAL_PLACES;
		
		// Fill the display formatters table.
		displayFormatters = new HashMap<>();
		
		DecimalFormat oneDecimalPlaceFormatter = new DecimalFormat("0.0");
		oneDecimalPlaceFormatter.setRoundingMode(RoundingMode.HALF_UP);
		displayFormatters.put(DISPLAY_MODES.ONE_DECIMAL_PLACE, oneDecimalPlaceFormatter);
		
		DecimalFormat twoDecimalPlacesFormatter = new DecimalFormat("0.00");
		twoDecimalPlacesFormatter.setRoundingMode(RoundingMode.HALF_UP);
		displayFormatters.put(DISPLAY_MODES.TWO_DECIMAL_PLACES, twoDecimalPlacesFormatter);
		
		DecimalFormat scientificModeFormatter = new DecimalFormat("0.######E00");
		scientificModeFormatter.setRoundingMode(RoundingMode.HALF_UP);
		displayFormatters.put(DISPLAY_MODES.SCIENTIFIC, scientificModeFormatter);
	}
	
	
	
	
	/**
	 * Set the first number (left operand) in this model.
	 * @param num String representing the first number (left operand).
	 * @return <code>true</code> if the number was successfully set. Otherwise <code>false</code>.
	 */
	public boolean setNum1(String num){
		try{
			num1 = new BigDecimal(num);
			return true;
		}
		catch(NumberFormatException e){
			errorState = ERROR_STATES.NAN;
			return false;
		}
	}
	
	
	
	
	/**
	 * Set the second number (right operand) in this model.
	 * @param num String representing the second number (right operand).
	 * @return <code>true</code> if the number was successfully set. Otherwise <code>false</code>.
	 */
	public boolean setNum2(String num){
		try{
			num2 = new BigDecimal(num);
			return true;
		}
		catch(NumberFormatException e){
			errorState = ERROR_STATES.NAN;
			return false;
		}
	}
	
	
	
	
	/**
	 * Set the operation of this model.
	 * @param operation The operation you want this model to perform to the left and right operands.
	 */
	public void setOperation(OPERATIONS operation){
		this.operation = operation;
	}
	
	
	
	
	/**
	 * Set the display mode of this model.
	 * @param displayMode The display mode.
	 */
	public void setDisplayMode(DISPLAY_MODES displayMode){
		this.displayMode = displayMode;
	}
	
	
	
	
	/**
	 * The calculation which is carried out is: (first number) (operation) (second number)
	 * @return A formatted String representing the result of the calculation.
	 *         Or null if there was in error in the calculation, in which case the error state is set.
	 */
	public String performCalculation(){
		if (ERROR_STATES.NO_ERROR_STATE != errorState) {
			return null;
		}
		
		// Do calculations in integer mode.
		if(DISPLAY_MODES.INTEGER == displayMode){
			MathContext integerMathContext = new MathContext(0, RoundingMode.DOWN);
			switch(operation){
				case ADD:      return num1.add(num2, integerMathContext).toPlainString();
				case SUBTRACT: return num1.subtract(num2, integerMathContext).toPlainString();
				case MULTIPLY: return num1.multiply(num2, integerMathContext).toPlainString();
				
				default: // Division
					if(isIllegalDivision()){ return null; }
					
					return num1.divide(num2, 0, RoundingMode.DOWN).toPlainString();
			}
		}
		
		//Do calculations in one of the float modes.
		BigDecimal result;
		
		switch(operation){
			case ADD:
				result = num1.add(num2);
				break;
			
			case SUBTRACT:
				result = num1.subtract(num2);
				break;
			
			case MULTIPLY:
				result = num1.multiply(num2);
				break;
			
			// Divide
			default:
				if(isIllegalDivision()){ return null; }
				
				// Try to divide the numbers without truncating.
				try{
					result = num1.divide(num2);
				}
				catch(ArithmeticException e){ // Need to truncate the repeating series (example 1/3).
					result = num1.divide(num2, new MathContext(7));
				}
		}
		
		// Format the result.
		String formattedResult = displayFormatters.get(displayMode).format(result);
		
		/* The following code ensures that there is always either a leading + or - for the
		 * exponent when using scientific notation. Kind of a hack, but DecimalFormat seems
		 * to be unable to display leading + (plus) signs in the exponent field.
		 * 
		 * It is taken from: http://stackoverflow.com/questions/3424792/java-decimalformat-creates-error-when-enforcing-exponent-sign
		 */
		if(DISPLAY_MODES.SCIENTIFIC == displayMode && !formattedResult.contains("E-")){
			formattedResult = formattedResult.replace("E", "E+");
		}
		
		return formattedResult;
	}
	
	
	
	
	/** @return The error state that this model is in. */
	public ERROR_STATES getErrorState(){
		return errorState;
	}
	
	
	
	
	/** Set the error state to no error. */
	public void clearErrorState(){
		errorState = ERROR_STATES.NO_ERROR_STATE;
	}
	
	
	
	
	/** @return Zero formatted to the current display format. */
	public String getFormattedZero(){
		return DISPLAY_MODES.INTEGER == displayMode ? "0" : "0.0";
	}
	
	
	
	
	/**
	 * Helper function which checks if the division of (num1 / num2) is valid.<br>
	 * Sets the error state to the proper value in {@link ERROR_STATES} depending on the type of illegal division.
	 * 
	 * @return <code>true</code> if attempting to do (non-Zero-Number/0) or (0/0). <code>false</code> otherwise.
	 */
	private boolean isIllegalDivision(){
		if(num2.compareTo(BigDecimal.ZERO) == 0){ // Something divided by  0
			if(num1.compareTo(BigDecimal.ZERO) == 0){ // Dividing 0 by 0
				errorState = ERROR_STATES.NAN;
			}
			else{
				errorState = ERROR_STATES.INFINITY;
			}
			
			return true;
		}
		
		return false;
	}
}
