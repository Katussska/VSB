package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Bat {

    private Point2D position;
    private final int width = 15;
    private final int height = 75;
    private int speed = 2;
    private Game game;

    public Bat(Game game, int positionX) {
        this.game = game;
        this.position = new Point2D(positionX, 30);
    }

    public Bat(Game game, Point2D position) {
        this.game = game;
        this.position = position;
    }

    public void draw(GraphicsContext gc) {
        gc.save();
        gc.setFill(Color.GRAY);
        gc.fillRect(position.getX(), position.getY(), width, height);
        gc.restore();
    }

    public void simulate() {
        if (position.getY() + speed < 30 || position.getY() + speed > game.getHeight() - 30 - height) {
            speed *= -1;
        }
        position = new Point2D(position.getX(), position.getY() + speed);
    }

    public Rectangle2D getBB() {
        return new Rectangle2D(position.getX(), position.getY(), width, height);
    }
}
