package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Game {
    private double width;
    private double height;
    private Ball ball;
    private Bat batA;
    private Bat batB;

    public Game(double width, double height) {
        this.width = width;
        this.height = height;
        ball = new Ball(this);
        batA = new Bat(this, 30);
        batB = new Bat(this, (int)width - 45);
    }

    public void draw(GraphicsContext gc) {
        gc.clearRect(0, 0, width, height);

        // background
        gc.setFill(Color.BLACK);
		gc.fillRect(0, 0, width, height);

        // horizontal lines
		gc.setFill(Color.WHITE);
		gc.fillRect(0, 0, width, 15);
		gc.fillRect(0, height - 15, width, 15);

		// playing net
		for (int i = 0; i < 15; i++) {
			gc.fillRect(width / 2 - 15, i * 15 + i * 15, 15, 15);
		}

        ball.draw(gc);
        batA.draw(gc);
        batB.draw(gc);
    }

    public void simulate() {
        ball.simulate();
        batA.simulate();;
        batB.simulate();
    }

    public double getWidth() {
        return width;
    }

    public double getHeight() {
        return height;
    }

}
