package lab;

import static lab.Constants.DRAGON_IMAGE;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;

public class Dragon {
	private static final double SIZE_OF_DRAGON = 100;
	private final World world;
	private Point2D position;
	private Point2D velocity;
	private Point2D dimension;
	private final Image image;
	
	public Dragon(World world, Point2D position, Point2D velocity) {
		this(world, position, velocity, new Point2D(SIZE_OF_DRAGON, SIZE_OF_DRAGON));
	}

	public Dragon(World world, Point2D position, Point2D velocity, Point2D dimension) {
		this.world = world;
		this.position = position;
		this.velocity = velocity;
		this.dimension = dimension;
		this.image = DRAGON_IMAGE;
	}
	
	public void draw(GraphicsContext gc) {
		Point2D p = world.getCanvasPoint(position);
		gc.drawImage(image, p.getX(), p.getY(), dimension.getX(), dimension.getY());
	}

	public void simulate(double deltaT) {
		position = position.add(velocity.multiply(deltaT));
		position = new Point2D((position.getX() + world.getWidth()) % world.getWidth(), (position.getY() + world.getHeight()) % world.getHeight());
	}
	
	public Rectangle2D getBB() {
		return new Rectangle2D(position.getX(), position.getY(), dimension.getX(), dimension.getY());
	}

	public void hit() {
		velocity = new Point2D(-velocity.getX(), -velocity.getY());
		
	}
}
