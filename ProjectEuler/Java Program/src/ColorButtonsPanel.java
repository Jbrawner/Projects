import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;

public class ColorButtonsPanel extends JPanel {

	private JButton _blackB, _redB, _blueB, _greenB;
	private Color pointColor;

	public ColorButtonsPanel() {

		setLayout(new GridLayout(4,1));
		
		_blackB = new JButton("Black");
		_blackB.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				pointColor = Color.BLACK;
			}

		});
		add(_blackB);

		_redB = new JButton("Red");
		_redB.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				pointColor = Color.RED;
			}

		});
		add(_redB);

		_blueB = new JButton("Blue");
		_blueB.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				pointColor = Color.BLUE;
			}

		});
		add(_blueB);

		_greenB = new JButton("Green");
		_greenB.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				pointColor = Color.GREEN;
			}

		});
		add(_greenB);
		
	}
	
	public Color getPointColor(){
		return pointColor;
	}

}
