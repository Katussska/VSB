package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;

public class World {
	private double width;
	private double height;
	private BulletAnimated bulletAnimatted;
	private Cannon cannon;
	private final Dragon[] dragons;
	
	public World(double width, double height) {
		this.width = width;
		this.height = height;
		cannon = new Cannon(this, new Point2D(50, 50), new Point2D(100, 20));
		bulletAnimatted = new BulletAnimated(this, cannon, new Point2D(30, 60), new Point2D(0, 0), 40);
		dragons = new Dragon[] {
				new Dragon(this, new Point2D(110, 90), new Point2D(70, 80)),
				new Dragon(this, new Point2D(70, 90), new Point2D(70, -80)),
				new Dragon(this, new Point2D(160, 70), new Point2D(170, 20)),
				new Dragon(this, new Point2D(110, 90), new Point2D(-70, 80)),
				new Dragon(this, new Point2D(110, 90), new Point2D(-50, -80))};
	}

	public Point2D getCanvasPoint(Point2D worldPoint) {
		return new Point2D(worldPoint.getX(), height - worldPoint.getY());
	}

	public void draw(GraphicsContext gc) {
		gc.clearRect(0, 0, width, height);
		cannon.draw(gc);
		bulletAnimatted.draw(gc);
		for (Dragon dragon : dragons) {
			dragon.draw(gc);	
		}
		
	}

	public void simulate(double timeDelta) {
		bulletAnimatted.simulate(timeDelta);
		cannon.simulate(timeDelta);
		for (Dragon dragon : dragons) {
			dragon.simulate(timeDelta);	
		}
		if (bulletAnimatted.isInCannon()) {
			return;
		}
		for (Dragon dragon : dragons) {
			if (dragon.getBB().intersects(bulletAnimatted.getBB())) {
				bulletAnimatted.reload();;
				dragon.hit();
			}
		}
	}

	public double getWidth() {
		return width;
	}

	public double getHeight() {
		return height;
	}

}
