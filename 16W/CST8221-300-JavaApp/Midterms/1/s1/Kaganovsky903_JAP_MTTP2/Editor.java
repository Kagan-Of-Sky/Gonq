import java.awt.Dimension;

import javax.swing.SwingUtilities;



public class Editor {
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override public void run() {
				Notepad notepad = new Notepad("Title");
				
				notepad.setSize(new Dimension(1000, 700));
				notepad.setLocationByPlatform(true);
				notepad.setVisible(true);
				notepad.setDefaultCloseOperation(Notepad.EXIT_ON_CLOSE);
			}
		});
	}
}
