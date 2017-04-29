import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.FileReader;
import java.util.HashMap;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JToolBar;




public class Main {
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			@Override public void run() {
				(new Notepad()).setVisible(true);
			}
		});
	}
}




class Notepad extends JFrame {
	private ActionHandler handler;
	private JTextArea     textArea;
	private JLabel        statusLabel;
	
	public Notepad() {
		// Initialize JFrame
			super("Notepad");
			setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			setSize(500, 500);
			setLocationByPlatform(true);
		
		// Create actions and handler
			handler = new ActionHandler(this);
			
			// Edit actions.
				ConcreteAction cutAction   = new ConcreteAction("Cut");
				ConcreteAction copyAction  = new ConcreteAction("Copy");
				ConcreteAction pasteAction = new ConcreteAction("Paste");
			
			// File actions.
				ConcreteAction fileOpenAction = new ConcreteAction("Open");
				ConcreteAction fileSaveAction = new ConcreteAction("Save");
		
		// Menu bar
			JMenuBar menuBar = new JMenuBar();
			
			// File menu
				JMenu fileMenu = new JMenu("File");
				fileMenu.add(new JMenuItem(fileOpenAction));
				fileMenu.add(new JMenuItem(fileSaveAction));
			
			// Edit menu
				JMenu editMenu = new JMenu("Edit");
				editMenu.add(cutAction);
				editMenu.add(copyAction);
				editMenu.add(pasteAction);
				
			// Add menus to bar
				menuBar.add(fileMenu);
				menuBar.add(editMenu);
		
		// Tool bar
			JToolBar toolBar = new JToolBar("Toolbar");
			toolBar.add(fileOpenAction);
			toolBar.add(fileSaveAction);
			toolBar.add(cutAction);
			toolBar.add(copyAction);
			toolBar.add(pasteAction);
		
		// Create text area
			textArea = new JTextArea();
			
			// Context menu
				JPopupMenu popupMenu = new JPopupMenu();
				popupMenu.add(cutAction);
				popupMenu.add(copyAction);
				popupMenu.add(pasteAction);
			
			// Event handler.
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
		
		// Create toolbar and menu bar panel.
			JPanel menuBarToolbarPanel = new JPanel(new BorderLayout());
			menuBarToolbarPanel.add(menuBar, BorderLayout.NORTH);
			menuBarToolbarPanel.add(toolBar, BorderLayout.SOUTH);
			
			add(menuBarToolbarPanel, BorderLayout.NORTH);
			add(new JScrollPane(textArea), BorderLayout.CENTER);
		
		// Create status label.
			statusLabel = new JLabel("Status");
			
			add(statusLabel, BorderLayout.SOUTH);
	}
	
	private class ConcreteAction extends AbstractAction {
		public ConcreteAction(String name) {
			putValue(Action.NAME, name);               // Displayed Text and Action Command
			putValue(Action.ACTION_COMMAND_KEY, name); // Action Command
			putValue(Action.SHORT_DESCRIPTION, name);  // ToolTip
		}
		
		@Override public void actionPerformed(ActionEvent e) {
			handler.actionPerformed(e);
		}
	}

	private class ActionHandler {
		private HashMap<String, Runnable> actionCommandMap;
		private JFrame parent;
		
		public ActionHandler(JFrame parent) {
			this.parent = parent;
			
			actionCommandMap = new HashMap<>();
			
			actionCommandMap.put("Open", new Runnable() {
				@Override public void run() {
					JFileChooser fileChooser = new JFileChooser(".");
					
					if(fileChooser.showOpenDialog(parent) != JFileChooser.APPROVE_OPTION ){
						statusLabel.setText("No file chosen");
						return;
					}
					
					File file = fileChooser.getSelectedFile();
					
					try{
						FileReader reader = new FileReader(file);
						StringBuilder sb = new StringBuilder();
						char buffer[] = new char[4096];
						
						int numChars;
						while((numChars=reader.read(buffer)) > 0){
							for(int i=0; i<numChars; ++i){
								sb.append(buffer[i]);
							}
						}
						
						textArea.setText(sb.toString());
					}
					catch(Exception e){
						statusLabel.setText(e.getMessage());
					}
				}
			});
			
			actionCommandMap.put("Save", new Runnable() {
				@Override public void run() {
					System.out.println("Save");
				}
			});
			
			actionCommandMap.put("Cut", new Runnable() {
				@Override public void run() {
					System.out.println("Cut");
				}
			});
			
			actionCommandMap.put("Copy", new Runnable() {
				@Override public void run() {
					System.out.println("Copy");
				}
			});
			
			actionCommandMap.put("Paste", new Runnable() {
				@Override public void run() {
					System.out.println("Paste");
				}
			});
		}
		
		public void actionPerformed(ActionEvent e) {
			actionCommandMap.get(e.getActionCommand()).run();
		}
	}
}







