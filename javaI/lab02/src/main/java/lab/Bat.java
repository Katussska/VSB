package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Bat {

    private Point2D position;
    private int speed = 2;
    private final int width = 15;
    private final int height = 75;
    private Game game;

    public Bat(Game game, int posX) {
        this.game = game;
        this.position = new Point2D(posX, 30);
    }

    public Bat(Game game, Point2D pos) {
        this.game = game;
        this.position = pos;
    }

    public void draw(GraphicsContext gc) {
        gc.save();
        gc.setFill(Color.WHITE);
        gc.fillRect(position.getX(), position.getY(), width, height);
        gc.restore();
    }

    public void simulate() {
        if (position.getY() + speed < 30 || position.getY() + speed > game.getHeight() - 30 - height) {
            speed *= -1;
        }
        position = new Point2D(position.getX(), position.getY() + speed);
    }
}
