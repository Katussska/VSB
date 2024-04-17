package cz.vsb.fei.java2.testhashcode;

public class Rectangle extends Shape {

	private int width;
	private int height;

	public Rectangle(Point position, int width, int height) {
		super(position);
		this.width = width;
		this.height = height;
	}
	
	public int getWidth() {
		return width;
	}

	public int getHeight() {
		return height;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		if (!super.equals(o)) return false;

		Rectangle rectangle = (Rectangle) o;
		return width == rectangle.width && height == rectangle.height;
	}

	@Override
	public int hashCode() {
		int result = super.hashCode();
		result = 31 * result + width;
		result = 31 * result + height;
		return result;
	}
}
