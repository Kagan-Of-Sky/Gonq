/* File name:   Calculator.java
 * Author:      Mark Kaganovsky
 * Course:      CST8221 - JAP, Lab Section: 302
 * Assignment:  1
 * Date:        Feb 24 2016
 * Professor:   Svillen Ranev
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
 * @see     CalculatorSplashScreen
 *          CalculatorView
 * @since   1.8.0_20
 */
public class Calculator {
	
	/**
	 * First creates a splash screen for a certain duration, and then creates the {@link CalculatorView}.
	 * 
	 * @param args Not used
	 */
	public static void main(String[] args) {
		long splashScreenDuration = 5000; // The duration of the splash screen in milliseconds.
		
		// Minimum calculator dimensions.
		int calculatorMinWidth  = 276;
		int calculatorMinHeight = 460;
		
		// Display splash screen.
		(new CalculatorSplashScreen(splashScreenDuration)).showSplashWindow();
		
		// Run main calculator application.
		EventQueue.invokeLater(new Runnable() {
			@Override
			public void run() {
				JFrame frame = new JFrame("Calculator");
				
				frame.setMinimumSize(new Dimension(calculatorMinWidth, calculatorMinHeight));
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setContentPane(new CalculatorView());
				frame.setLocationByPlatform(true);
				
				frame.setVisible(true);
			}
		});
	}

}
