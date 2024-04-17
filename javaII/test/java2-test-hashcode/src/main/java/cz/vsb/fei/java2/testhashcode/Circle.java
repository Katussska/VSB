package cz.vsb.fei.java2.testhashcode;

public class Circle extends Shape {

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		if (!super.equals(o)) return false;

		Circle circle = (Circle) o;
		return radius == circle.radius;
	}

	@Override
	public int hashCode() {
		int result = super.hashCode();
		result = 31 * result + radius;
		return result;
	}

	private int radius;

	public Circle(Point position, int radius) {
		super(position);
		this.radius = radius;
	}

}
