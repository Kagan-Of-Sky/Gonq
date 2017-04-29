/* File name:   CalculatorSplashScreen.java
 * Author:      Mark Kaganovsky
 * Course:      CST8221 - JAP, Lab Section: 302
 * Assignment:  1
 * Date:        Feb 24 2016
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
import javax.swing.JWindow;
import javax.swing.border.EmptyBorder;




/**
 * Displays a splash screen to the user before the actual calculator application launches.
 * 
 * @author  Mark Kaganovsky
 * @version 1.5
 * @see     JWindow
 * @since   1.8.0_20
 */
public class CalculatorSplashScreen extends JWindow{
	
	/** Auto generated serialVersionUID */
	private static final long serialVersionUID = 9175968677735518019L;
	
	/** The duration (milliseconds) to keep this splash screen visible for.
	 *  For best results set this animation to a multiple of 1000, but any value will work.
	 */
	private long duration;
	
	/**
	 * The loading label (shown at the top of the splash window).
	 * This reference is stored so that animateSplashScreen() can change its text.
	 */
	private JLabel loadingLabel;
	
	
	
	
	/**
	 * Use the method CalculatorSplashScreen.showSplashWindow() to show this window.
	 * 
	 * @param duration The duration (in milliseconds) to keep this splash screen visible for.
	 */
	public CalculatorSplashScreen(long durationms){
		this.duration = durationms;
	}
	
	
	
	
	/** Display this splash screen for the duration of milliseconds specified in the constructor. */
	public void showSplashWindow() {
		Font font = new Font(Font.MONOSPACED, Font.PLAIN, 18); // Font for the loading label and the name label.
		
		// Build the content panel.
			JPanel contentPanel = new JPanel(new BorderLayout());
			contentPanel.setBackground(Color.BLACK);
			contentPanel.setBorder(new EmptyBorder(10, 10, 10, 10));
			setContentPane(contentPanel);
			
		// Build the loading label.
			loadingLabel = createLabel("Loading...", JLabel.CENTER, font, Color.WHITE, Color.DARK_GRAY, true);
		
		// Build the icon label.
			JLabel iconLabel = new JLabel(new ImageIcon("splashScreenCalculatorIcon.png"));
			iconLabel.setBorder(new EmptyBorder(10,0,10,0));
		
		// Build the name and student number label.
			JLabel nameSNLabel = createLabel("<html>" + 
			                                    "Mark Kaganovsky<br>" +
			                                    "S/N:040-789-903" +
			                                "</html>", JLabel.CENTER, font, Color.WHITE, Color.DARK_GRAY, true); 
		
		// Add all the elements.
			contentPanel.add(loadingLabel, BorderLayout.NORTH);
			contentPanel.add(iconLabel, BorderLayout.CENTER);
			contentPanel.add(nameSNLabel, BorderLayout.SOUTH);
		
		// Set the size of the window so that it is big enough to hold the image and the text.
			//Splash screen height.
			int ssHeight = iconLabel.getPreferredSize().height    + 
			               loadingLabel.getPreferredSize().height + 
			               nameSNLabel.getPreferredSize().height;
			
			int ssWidth  = iconLabel.getPreferredSize().width; // Splash screen width.
			
			// name and student number label is wider than the image.
			if(nameSNLabel.getPreferredSize().width > ssWidth){
				ssWidth = nameSNLabel.getPreferredSize().width;
			}
			
			// loading label is larger than the current value image width.
			if(loadingLabel.getPreferredSize().width > ssWidth){
				ssWidth = loadingLabel.getPreferredSize().width;
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
	 * Keep the splash screen visible for "duration" milliseconds.
	 * 
	 * Animate the "Loading..." text at the top of the splash screen.
	 */
	private void animateSplashScreen(){
		// The strings to animate the top "Loading..." label.
		String loadingLabelStrings[] = new String[]{"Loading",
		                                            "Loading.",
		                                            "Loading..",
		                                            "Loading..."};
		
		int loadingAnimationIndex = 0; // Index into loadingLabelStrings
		
		/* Sleep for 'duration' milliseconds.
		 * Every 250 milliseconds animate the 'loading...' at the top of the splash screen.
		 */
		while(duration > 250){
			try{
				Thread.sleep(250);
			}
			catch(InterruptedException e){
				e.printStackTrace();
			}
			loadingLabel.setText(loadingLabelStrings[loadingAnimationIndex]);
			
			++loadingAnimationIndex;
			loadingAnimationIndex %= loadingLabelStrings.length;
			
			duration -= 250;
		}
		
		// Sleep for the remaining time. For example, if duration is 253 milliseconds then this will sleep for the remaining 3 milliseconds.
		try{
			Thread.sleep(duration);
		}
		catch(InterruptedException e){
			e.printStackTrace();
		}
	}
}
