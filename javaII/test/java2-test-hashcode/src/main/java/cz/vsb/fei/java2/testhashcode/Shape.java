package cz.vsb.fei.java2.testhashcode;

public abstract class Shape {

	private Point position;

	protected Shape(Point position) {
		this.position = position;
	}

	public Point getPosition() {
		return position;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;

		Shape shape = (Shape) o;
		return position.equals(shape.position);
	}

	@Override
	public int hashCode() {
		return position.hashCode();
	}
}
