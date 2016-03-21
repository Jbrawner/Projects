import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JPanel;

public class PaintPanel extends JPanel{
	
	private ArrayList<Point> _points = new ArrayList<Point>();
	
	@Override
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		
		for(Point point : _points){
			
			g.setColor(point.getColor());
			g.fillOval(point.getX(), point.getY(), point.getSize(), point.getSize());
			
		}
	}
	
	public void addPoint(Point p){
		_points.add(p);
		this.repaint();
	}
	
	public void clear(){
		_points.clear();
		this.repaint();
	}
	
	public ArrayList<Point> getPoints(){
		return _points;
	}

}
