import javax.swing.JApplet;

public class CalculatorApplet extends JApplet{
	private static final long serialVersionUID = 1L;
	
	@Override
	public void init() {
		super.init();
		
		add(new CalculatorView());
	}
}