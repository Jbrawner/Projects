import java.awt.BorderLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JFrame;

public class MainFrame extends JFrame{
	
	public static PaintPanel _paintP;
	private ColorButtonsPanel _colorButtonsP;
	private SizeButtonsPanel _sizeButtonsP;
	
	public MainFrame(){
		super("DrawIt!");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new BorderLayout());
		setSize(800,600);
		
		_colorButtonsP = new ColorButtonsPanel();
		add(_colorButtonsP, BorderLayout.WEST);
		
		_sizeButtonsP = new SizeButtonsPanel();
		add(_sizeButtonsP, BorderLayout.EAST);
		
		_paintP = new PaintPanel();
		_paintP.addMouseListener(new MouseAdapter(){
			@Override
			public void mouseClicked(MouseEvent e){
				_paintP.addPoint(new Point(e.getX(), e.getY(), _sizeButtonsP.getPointSize(), _colorButtonsP.getPointColor()));
			}
		});
		_paintP.addMouseMotionListener(new MouseAdapter(){
			@Override
			public void mouseDragged(MouseEvent e){
				_paintP.addPoint(new Point(e.getX(), e.getY(), _sizeButtonsP.getPointSize(), _colorButtonsP.getPointColor()));
			}
		});
		add(_paintP, BorderLayout.CENTER);
		
	}
	
}
