/* CST8221 - JAP, Midterm Test, Part 2
 * 
 * Student Name and Student Number: Mark Kaganovsky 040789903
 * Date: date of submission Time:   March 16 5:00pm
 * Development platform:            Win8.1
 * Development tool:                Eclipse Luna
 * Java SDK version:                1.8_25
 */

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JToolBar;
import javax.swing.KeyStroke;
import javax.swing.border.BevelBorder;
import javax.swing.filechooser.FileNameExtensionFilter;


public class Notepad extends JFrame {
	private static final long serialVersionUID = 2797089565687254735L;
	
	private JTextArea textArea;
	private JMenuBar menuBar;
	private JLabel statusLabel;
	
	public Notepad(String title) {
		super(title);
		JFrame parent = this;
		
		// Create file chooser
			JFileChooser fileChooser = new JFileChooser(".");
			fileChooser.setAcceptAllFileFilterUsed(false);
			fileChooser.addChoosableFileFilter(new FileNameExtensionFilter("Text files (.txt)", "txt"));
			fileChooser.addChoosableFileFilter(new FileNameExtensionFilter("Java files (.class)", "class"));
			fileChooser.addChoosableFileFilter(new FileNameExtensionFilter("Java files (.java)", "java"));
		
		// Create menu bar.
			menuBar = new JMenuBar();
			menuBar.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
			
			// File menu.
				JMenu fileMenu = new JMenu("File");
				fileMenu.setMnemonic(KeyEvent.VK_F);
				
				// File menu items
				JMenuItem newMenuItem = new JMenuItem("New");
				newMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, KeyEvent.CTRL_DOWN_MASK));
				newMenuItem.addActionListener(new ActionListener() {
					@Override public void actionPerformed(ActionEvent e) {
						textArea.setText("");
						statusLabel.setText("Status: New empty file.");
					}
				});
				
				JMenuItem openMenuItem = new JMenuItem("Open");
				openMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, KeyEvent.CTRL_DOWN_MASK));
				openMenuItem.addActionListener(new ActionListener() {
					@Override public void actionPerformed(ActionEvent event){
						if(fileChooser.showOpenDialog(parent) != JFileChooser.APPROVE_OPTION){
							statusLabel.setText("No file selected.");
							return;
						}
						
						// Read file
						try(FileReader reader = new FileReader(fileChooser.getSelectedFile())){
							StringBuilder sb = new StringBuilder();
							char buffer[] = new char[4096];
							int numChars;
							
							while((numChars=reader.read(buffer)) > 0){
								sb.append(buffer, 0, numChars);
							}
							
							textArea.setText(sb.toString());
							statusLabel.setText("Status: " + "File " + fileChooser.getSelectedFile().getName() + " is open.");
						}
						catch(FileNotFoundException e){
							statusLabel.setText("Status: " + "File " + fileChooser.getSelectedFile().getName() + " does not exist.");
						}
						catch(Exception e){
							statusLabel.setText(e.getMessage());
						}
					}
				});
				
				JMenuItem saveMenuItem = new JMenuItem("Save");
				saveMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, KeyEvent.CTRL_DOWN_MASK));
				saveMenuItem.addActionListener(new ActionListener() {
					@Override public void actionPerformed(ActionEvent event) {
						// Get file name.
						if(fileChooser.showSaveDialog(parent) != JFileChooser.APPROVE_OPTION){
							statusLabel.setText("No file selected.");
							return;
						}
						
						// Save file
						try(FileWriter writer = new FileWriter(fileChooser.getSelectedFile())){
							writer.write(textArea.getText());
							statusLabel.setText("Status: " + "File " + fileChooser.getSelectedFile().getName() + " is saved.");
						}
						catch(Exception e){
							statusLabel.setText(e.getMessage());
						}
					}
				});
				
				JMenuItem exitMenuItem = new JMenuItem("Exit");
				exitMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F4, KeyEvent.ALT_DOWN_MASK));
				exitMenuItem.addActionListener(new ActionListener() {
					@Override public void actionPerformed(ActionEvent e) {
						parent.dispose();
					}
				});
				
				fileMenu.add(newMenuItem);
				fileMenu.addSeparator();
				fileMenu.add(openMenuItem);
				fileMenu.add(saveMenuItem);
				fileMenu.addSeparator();
				fileMenu.add(exitMenuItem);
				
				menuBar.add(fileMenu);
			
			// Edit menu
				JMenu editMenu = new JMenu("Edit");
				editMenu.setMnemonic(KeyEvent.VK_E);
				
				// File menu items
				Action cutAction = new AbstractAction() {
					@Override public void actionPerformed(ActionEvent e) {
						statusLabel.setText("Status: " + e.getActionCommand() + " menu item has been selected.");
					}
				};
				cutAction.putValue(Action.NAME, "Cut");
				
				Action copyAction = new AbstractAction() {
					@Override public void actionPerformed(ActionEvent e) {
						statusLabel.setText("Status: " + e.getActionCommand() + " menu item has been selected.");
					}
				};
				copyAction.putValue(Action.NAME, "Copy");
				
				Action pasteAction = new AbstractAction() {
					@Override public void actionPerformed(ActionEvent e) {
						statusLabel.setText("Status: " + e.getActionCommand() + " menu item has been selected.");
					}
				};
				pasteAction.putValue(Action.NAME, "Paste");
				
				editMenu.add(cutAction);
				editMenu.add(copyAction);
				editMenu.add(pasteAction);
				
				menuBar.add(editMenu);
			
			// Help menu
				JMenu helpMenu = new JMenu("Help");
				helpMenu.setMnemonic(KeyEvent.VK_H);
				
				JMenuItem aboutMenuItem = new JMenuItem("About");
				aboutMenuItem.setMnemonic(KeyEvent.VK_A);
				aboutMenuItem.addActionListener(new ActionListener() {
					@Override public void actionPerformed(ActionEvent e) {
						JOptionPane.showMessageDialog(parent, "Mark Kaganovsky's Program Editor\nVersion 1.0 Winter 2016");
					}
				});
				
				helpMenu.add(aboutMenuItem);
				menuBar.add(Box.createHorizontalGlue());
				menuBar.add(helpMenu);
			
			add(menuBar, BorderLayout.NORTH);
		
		// Tool bar
			JToolBar toolBar = new JToolBar("Toolbar", JToolBar.VERTICAL);
			
			JButton defaultBackgroundButton = new JButton("D");
			defaultBackgroundButton.setMnemonic(KeyEvent.VK_D);
			defaultBackgroundButton.addActionListener(new ActionListener() {
				@Override public void actionPerformed(ActionEvent e) {
					textArea.setBackground(Color.WHITE);
					textArea.setForeground(Color.BLACK);
				}
			});
			
			JButton blueBackgroundButton = new JButton("B");
			blueBackgroundButton.setMnemonic(KeyEvent.VK_B);
			blueBackgroundButton.addActionListener(new ActionListener() {
				@Override public void actionPerformed(ActionEvent e) {
					textArea.setBackground(Color.BLUE);
					textArea.setForeground(Color.WHITE);
				}
			});
			
			JButton orangeBackgroundButton = new JButton("O");
			orangeBackgroundButton.setMnemonic(KeyEvent.VK_O);
			orangeBackgroundButton.addActionListener(new ActionListener() {
				@Override public void actionPerformed(ActionEvent e) {
					textArea.setBackground(Color.ORANGE);
					textArea.setForeground(Color.WHITE);
				}
			});
			
			toolBar.addSeparator();
			toolBar.addSeparator();
			toolBar.add(defaultBackgroundButton);
			toolBar.addSeparator();
			toolBar.add(blueBackgroundButton);
			toolBar.addSeparator();
			toolBar.add(orangeBackgroundButton);
			
			add(toolBar, BorderLayout.EAST);
			
		// Text area
			textArea = new JTextArea(80, 80);
			textArea.setMargin(new Insets(10, 10, 10, 10));
			
			JPopupMenu popupMenu = new JPopupMenu();
			popupMenu.add(cutAction);
			popupMenu.add(copyAction);
			popupMenu.add(pasteAction);
			
			textArea.addMouseListener(new MouseListener() {
				@Override public void mouseReleased(MouseEvent e) {}
				@Override public void mousePressed(MouseEvent e) {}
				@Override public void mouseExited(MouseEvent e) {}
				@Override public void mouseEntered(MouseEvent e) {}
				
				@Override public void mouseClicked(MouseEvent e) {
					if(MouseEvent.BUTTON3 == e.getButton()){
						popupMenu.show(e.getComponent(), e.getX(), e.getY());
					}
				}
			});
			
			add(new JScrollPane(textArea), BorderLayout.CENTER);
		
		// Status label
			statusLabel = new JLabel();
			add(statusLabel, BorderLayout.SOUTH);
	}
}
