import java.awt.EventQueue;
import java.util.Random;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;








/**
 * This program demonstrates that a thread which runs in parallel
 * with the event dispatch thread can cause errors in Swing components.
 */
public class SwingThreadTest{
	public static void main(String[] args) {
		EventQueue.invokeLater(() -> {
			SwingThreadFrame frame = new SwingThreadFrame();
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setVisible(true);
		});
	}
}








/**
 * This frame has two buttons to fill a combo box from a separate thread.
 * 
 * The "Good" button uses the event queue,
 * the "Bad" button modifies the combo box directly.
 */
class SwingThreadFrame extends JFrame {
	private static final long serialVersionUID = -6592537458591587426L;
	
	public SwingThreadFrame() {
		// Create combo box
		final JComboBox<Integer> comboBox = new JComboBox<>();
		comboBox.insertItemAt(Integer.MAX_VALUE, 0);
		comboBox.setPrototypeDisplayValue(comboBox.getItemAt(0));
		comboBox.setSelectedIndex(0);
		
		
		// Create the good button.
		JButton goodButton = new JButton("Good");
		goodButton.addActionListener((event) -> {
			new Thread(new GoodWorkerRunnable(comboBox)).start();
		});
		
		
		// Create the bad button.
		JButton badButton = new JButton("Bad");
		badButton.addActionListener((event) -> {
			new Thread(new BadWorkerRunnable(comboBox)).start();
		});
		
		
		// Add elements
		JPanel panel = new JPanel();
		
		panel.add(goodButton);
		panel.add(badButton);
		panel.add(comboBox);
		
		add(panel);
		
		pack();
	}
}








/**
 * This runnable modifies a combo box by randomly adding and removing numbers. This can result in
 * errors because the combo box methods are not synchronized and both the worker thread and the
 * event dispatch thread access the combo box.
 */
class BadWorkerRunnable implements Runnable {
	private JComboBox<Integer> comboBox;
	private Random random;
	
	public BadWorkerRunnable(JComboBox<Integer> comboBox) {
		this.comboBox = comboBox;
		random = new Random();
	}
	
	public void run() {
		try {
			while (true) {
				int i = Math.abs(random.nextInt());
				
				if(i%2 == 0){
					comboBox.insertItemAt(i, 0);
				}
				else if (comboBox.getItemCount() > 0){
					comboBox.removeItemAt(i % comboBox.getItemCount());
				}
				
				Thread.sleep(1);
			}
		}
		catch (InterruptedException e) { }
	}
}








/**
 * This runnable modifies a combo box by randomly adding and removing numbers.
 * 
 * In order to ensure that the combo box is not corrupted, the editing
 * operations are forwarded to the event dispatch thread.
 */
class GoodWorkerRunnable implements Runnable {
	private JComboBox<Integer> comboBox;
	private Random random;

	public GoodWorkerRunnable(JComboBox<Integer> comboBox) {
		this.comboBox = comboBox;
		random = new Random();
	}

	public void run() {
		try {
			while (true) {
				EventQueue.invokeLater(() -> {
					int i = Math.abs(random.nextInt());
					if (i%2 == 0){
						comboBox.insertItemAt(i, 0);
					}
					else if (comboBox.getItemCount() > 0){
						comboBox.removeItemAt(i % comboBox.getItemCount());
					}
				});
				
				Thread.sleep(1);
			}
		}
		catch (InterruptedException e) { }
	}
}