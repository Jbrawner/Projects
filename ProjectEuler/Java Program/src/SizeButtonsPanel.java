import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;

public class SizeButtonsPanel extends JPanel {

	private JButton _smallB, _mediumB, _largeB, _clearB;
	private int pointSize;
	
	public SizeButtonsPanel(){
		
		setLayout(new GridLayout(4,1));
		
		//START _smallB
		_smallB = new JButton("Small");
		_smallB.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				pointSize = Point.SMALL;
			}
			
		});
		add(_smallB);
		//END _smallB
		
		
		//START _mediumB
		_mediumB = new JButton("Medium");
		_mediumB.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				pointSize = Point.MEDIUM;
			}
			
		});
		add(_mediumB);
		//END _mediumB
		
		
		//START _largeB
		_largeB = new JButton("Large");
		_largeB.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				pointSize = Point.LARGE;
			}
			
		});
		add(_largeB);
		//END _largeB
		
		
		//START _clearB
		_clearB = new JButton("Clear");
		_clearB.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				MainFrame._paintP.clear();
			}
			
		});
		add(_clearB);
		//END _clearB
		
	}
	
	public int getPointSize(){
		return pointSize;
	}
	
}
