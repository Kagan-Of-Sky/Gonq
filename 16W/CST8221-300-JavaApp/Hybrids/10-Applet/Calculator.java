/* File name:   Calculator.java
 * Author:      Mark Kaganovsky
 * Course:      CST8221 - JAP, Lab Section: 302
 * Assignment:  2
 * Date:        Mar 10 2016
 * Professor:   Svillen Ranev
 * 
 * Purpose:     Launch the calculator application. First it displays the splash
 *              screen and then it launches the actual calculator application.
 */

import java.awt.Dimension;
import java.awt.EventQueue;

import javax.swing.JFrame;




/**
 * The launcher for this calculator application.
 * 
 * @author  Mark Kaganovsky
 * @version 1.2
 * 
 * @see     CalculatorSplashScreen
 * @see     CalculatorView
 * 
 * @since   1.8.0_20
 */
public class Calculator {
	/** Duration of splash screen in milliseconds. */
	private static final int SPLASH_SCREEN_DURATION = 5000;
	
	/** Minimum calculator width */
	private static final int CALCULATOR_MIN_WIDTH  = 276;
	
	/** Minimum calculator height */
	private static final int CALCULATOR_MIN_HEIGHT = 460;
	
	/**
	 * First creates a splash screen for a certain duration, and then creates the {@link CalculatorView}.
	 * 
	 * @param args Not used
	 */
	public static void main(String[] args) {
		// Display splash screen.
		(new CalculatorSplashScreen(SPLASH_SCREEN_DURATION)).showSplashWindow();
		
		// Run main calculator application.
		EventQueue.invokeLater(() -> { 
			JFrame frame = new JFrame("Calculator");
			
			frame.setMinimumSize(new Dimension(CALCULATOR_MIN_WIDTH, CALCULATOR_MIN_HEIGHT));
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setContentPane(new CalculatorView());
			frame.setLocationByPlatform(true);
			
			frame.setVisible(true);
		});
	}

}
