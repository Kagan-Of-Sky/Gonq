/* File name:   CalculatorSplashScreen.java
 * Author:      Mark Kaganovsky
 * Course:      CST8221 - JAP, Lab Section: 302
 * Assignment:  2
 * Date:        March 10 2016
 * Professor:   Svillen Ranev
 * Purpose:     Display the splash screen for this calculator.
 */

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JWindow;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.border.EmptyBorder;




/**
 * Displays a splash screen to the user before the actual calculator application launches.
 * 
 * @author  Mark Kaganovsky
 * @version 1.5
 * @see     JWindow
 * @since   1.8.0_20
 */
public class CalculatorSplashScreen extends JWindow {
	/** Auto generated serialVersionUID */
	private static final long serialVersionUID = -627472242799323201L;

	/** The duration (milliseconds) to keep this splash screen visible for. */
	private int duration;
	
	/** The amount of time that the progress bar has been active. */
	private int timeTaken;
	
	/** Progress bar at the top of the splash screen. */
	private JProgressBar progressBar;
	
	
	
	
	/**
	 * Use the method CalculatorSplashScreen.showSplashWindow() to show this window.
	 * 
	 * @param duration The duration (in milliseconds) to keep this splash screen visible for.
	 */
	public CalculatorSplashScreen(int duration){
		timeTaken = 0;
		this.duration  = duration;
	}
	
	
	
	
	/** Display this splash screen for the duration of milliseconds specified in the constructor. */
	public void showSplashWindow() {
		Font font = new Font(Font.MONOSPACED, Font.PLAIN, 18); // Font for the loading label and the name label.
		
		// Build the content panel.
			JPanel contentPanel = new JPanel(new BorderLayout());
			contentPanel.setBackground(Color.BLACK);
			contentPanel.setBorder(new EmptyBorder(10, 10, 10, 10));
			setContentPane(contentPanel);
			
		// Build the progress bar.
			UIManager.put("ProgressBar.background", Color.DARK_GRAY);
			UIManager.put("ProgressBar.foreground", Color.GRAY);
			UIManager.put("ProgressBar.selectionBackground", Color.WHITE);
			UIManager.put("ProgressBar.selectionForeground", Color.WHITE);
			progressBar = new JProgressBar(0, duration);
			progressBar.setStringPainted(true);
			progressBar.setString("Loading Calculator. Please wait...");
			
		
		// Build the icon label.
			JLabel iconLabel = new JLabel(new ImageIcon("splashScreenCalculatorIcon.png"));
			iconLabel.setBorder(new EmptyBorder(10,0,10,0));
			
		// Build the name and student number label.
			JLabel nameSNLabel = createLabel("<html>" + 
			                                    "Mark Kaganovsky<br>" +
			                                    "S/N:040-789-903" +
			                                "</html>", JLabel.CENTER, font, Color.WHITE, Color.DARK_GRAY, true); 
		
		// Add all the elements.
			contentPanel.add(progressBar, BorderLayout.NORTH);
			contentPanel.add(iconLabel, BorderLayout.CENTER);
			contentPanel.add(nameSNLabel, BorderLayout.SOUTH);
		
		// Set the size of the window so that it is big enough to hold the image and the text.
			//Splash screen height.
			int ssHeight = iconLabel.getPreferredSize().height   + 
			               progressBar.getPreferredSize().height + 
			               nameSNLabel.getPreferredSize().height;
			
			int ssWidth  = iconLabel.getPreferredSize().width; // Splash screen width.
			
			// name and student number label is wider than the image.
			if(nameSNLabel.getPreferredSize().width > ssWidth){
				ssWidth = nameSNLabel.getPreferredSize().width;
			}
			
			// loading label is larger than the current value image width.
			if(progressBar.getPreferredSize().width > ssWidth){
				ssWidth = progressBar.getPreferredSize().width;
			}
		
		// Display the splash screen.
			setSize(new Dimension(ssWidth + 20, ssHeight));
			setLocationByPlatform(true);
			setVisible(true);
		
		// animate the splash screen.
			animateSplashScreen();
		
		// Clean up.
			dispose();
	}
	
	
	
	
	/**
	 * Create JLabels with the same basic properties.
	 * 
	 * @param text          The text which will be displayed on this Label.
	 * @param textAlignment The alignment of the text (ex JLabel.CENTER).
	 * @param font          The font to create this JLabel with.
	 * @param fg            Foreground color.
	 * @param bg            Background color.
	 * @param isOpaque      Set to true if you want this JLabel to be opaque.
	 * @return              A reference to the created JLabel object.
	 */
	public JLabel createLabel(String text, int textAlignment, Font font, Color fg, Color bg, boolean isOpaque){
		JLabel label = new JLabel(text, textAlignment);
		
		label.setFont(font);
		label.setForeground(fg);
		label.setBackground(bg);
		label.setOpaque(isOpaque);
		
		return label;
	}
	
	
	
	
	/**
	 * Keep the splash screen visible for "duration" milliseconds.<br>
	 * Animate the progress bar.
	 */
	private void animateSplashScreen(){
		// This Runnable instance is used to update the percentage which shows on the progress bar.
		Runnable progressBarUpdater = () -> {
			// Make sure the initial text stays long enough so users can read it.
			if(timeTaken > 1500){
				progressBar.setString(String.format("%d %%", (int)((float)timeTaken / duration * 100)));
			}
			
			progressBar.setValue(timeTaken);
		};
		
		while(timeTaken < duration){
			try{
				Thread.sleep(50);
			}
			catch(InterruptedException e){
				e.printStackTrace();
			}
			
			SwingUtilities.invokeLater(progressBarUpdater);
			
			timeTaken += 50;
		}
	}
}
