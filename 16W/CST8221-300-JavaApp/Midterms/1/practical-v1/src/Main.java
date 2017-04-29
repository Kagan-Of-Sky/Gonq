import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JTextArea;
import javax.swing.JToolBar;

public class Main {
	boolean fileSaved;
	
	public static void main(String[] args) {
		JFrame frame = new JFrame("Notepad");
		
		Action action = new AbstractAction() {
			@Override public void actionPerformed(ActionEvent e) {
				System.out.println("Action");
			}
		};
		
		// Menu bar
			JMenuBar menuBar = new JMenuBar();
			
			// File menu
				JMenu fileMenu = new JMenu("File");
				fileMenu.add(new JMenuItem("Open"));
				fileMenu.add(new JMenuItem("Save"));
			
			// Edit menu
				JMenu editMenu = new JMenu("Edit");
				JMenuItem cutItem = new JMenuItem("Cut");
				cutItem.addActionListener(action);
				JMenuItem copyItem = new JMenuItem("Copy");
				JMenuItem pasteItem = new JMenuItem("Paste");
				editMenu.add(cutItem);
				editMenu.add(copyItem);
				editMenu.add(pasteItem);
				
			// Add menus to bar
				menuBar.add(fileMenu);
				menuBar.add(editMenu);
		
		// Tool bar
			JToolBar toolBar = new JToolBar("Toolbar");
			toolBar.add(new JButton("Cut"));
			toolBar.add(new JButton("Copy"));
			toolBar.add(new JButton("Paste"));
		
		JTextArea textArea = new JTextArea();
		
		JPopupMenu popupMenu = new JPopupMenu();
		popupMenu.add(new JButton("Cut"));
		popupMenu.add(new JButton("Copy"));
		popupMenu.add(new JButton("Paste"));
		
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
		
		JPanel menuBarToolbarPanel = new JPanel(new BorderLayout());
		menuBarToolbarPanel.add(menuBar, BorderLayout.NORTH);
		menuBarToolbarPanel.add(toolBar, BorderLayout.SOUTH);
		
		frame.add(menuBarToolbarPanel, BorderLayout.NORTH);
		frame.add(textArea, BorderLayout.CENTER);
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(500, 500);
		frame.setLocationByPlatform(true);
		frame.setVisible(true);
	}
}
