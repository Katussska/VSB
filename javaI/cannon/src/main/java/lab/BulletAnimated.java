package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;

public class BulletAnimated {

	private Point2D position;
	private Point2D start;
	private Point2D speed;
	private Point2D initialSpeed;
	private double size;
	private double mass = 2;
	private double strenghtOfCannon = 80;
	private double cannonLength = 100;
	private boolean accelerate = true;
	private boolean hitToGround = false;
	
	private Image image;
	private World world;
	private Cannon cannon;

	public BulletAnimated(World world, Cannon cannon) {
		this(world, cannon, new Point2D(0, 0), new Point2D(0, 0), 10);
	}

	public BulletAnimated(World world, Cannon cannon, Point2D start, Point2D speed, double size) {
		this.start = start;
		this.position = this.start;
		this.initialSpeed = speed;
		this.speed = speed;
		this.size = size;
		this.world = world;
		this.cannon = cannon;
		image = new Image(getClass().getResourceAsStream("fireball-transparent.gif"), size, size,
				true, true);
	}

	public void draw(GraphicsContext gc) {
		gc.save();
		Point2D canvasPosition = world.getCanvasPoint(position);
		gc.drawImage(image, canvasPosition.getX(), canvasPosition.getY());
		gc.restore();
	}

	public void simulate(double timeStep) {
		if (accelerate && start.distance(position) < cannonLength) {
			double cannonAngle = cannon.getAngle(); 
			speed = speed
					.add(new Point2D(Math.cos(cannonAngle) * strenghtOfCannon, Math.sin(cannonAngle) * strenghtOfCannon)
							.multiply(1 / mass * timeStep * 10));
		} else if (!hitToGround) {
			accelerate = false;
			Point2D acceleration = new Point2D(0, -Constants.GRAVITATIONAL_ACCELERATION*50 * mass * timeStep * 10);
			speed = speed.add(acceleration.multiply(timeStep));
		}
		if (!hitToGround) {
			position = position.add(speed.multiply(timeStep));
			if (!accelerate && position.getY() <= size / 2) {
				hitToGround = true;
				position = new Point2D(position.getX(), size / 2);
			}
		} else {
			reload();
		}
		
		
	}

	public void reload() {
		position = start;
		speed = initialSpeed;
		hitToGround = false;
		accelerate = true;
	}
	
	public Rectangle2D getBB() {
		return new Rectangle2D(position.getX(), position.getY(), size, size);
	}

	public boolean isInCannon() {
		return accelerate;
	}
	
}
