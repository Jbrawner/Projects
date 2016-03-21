import java.awt.Color;

public class Point {

	public static final int SMALL = 5;
	public static final int MEDIUM = 15;
	public static final int LARGE = 30;
	
	private int _x, _y;
	private int _size;
	private Color _color;
	
	public Point(int x, int y, int size, Color color){
		_x = x;
		_y = y;
		_size = size == 0 ? MEDIUM : size;
		_color = color;
	}
	
	
	//getters and setters

	public int getSize() {
		return _size;
	}

	public void setSize(int size) {
		_size = size;
	}

	public Color getColor() {
		return _color;
	}

	public void setColor(Color color) {
		_color = color;
	}
	
	public int getX(){
		return _x;
	}
	
	public void setX(int x){
		_x = x;
	}
	
	public int getY(){
		return _y;
	}
	
	public void setY(int y){
		_y = y;
	}

}
