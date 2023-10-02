package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

class Vector {
    public int x;
    public int y;

    public Vector(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

public class Ball {

    private Vector vector = new Vector(2, 2);
    private Point2D position;
    private final int width = 15;
    private final int height = 15;
    private Game game;

    public Ball(Game game) {
        this.game = game;
        this.position = new Point2D(20, 20);
    }

    public Ball(Game game, Point2D startPos) {
        this.game = game;
        this.position = startPos;
    }

    public void draw(GraphicsContext gc) {
        gc.save();
        gc.setFill(Color.WHITE);
        gc.fillRect(position.getX(), position.getY(), width, height);
        gc.restore();
    }

    public void simulate() {
        if (position.getX() + vector.x < 0 || position.getX() + this.width + vector.x > game.getWidth()) {
            vector.x *= -1;
        }
        if (position.getY() + vector.y < 15 || position.getY() + this.height + vector.y > game.getHeight() - 15) {
            vector.y *= -1;
        }
        position = new Point2D(position.getX() + vector.x, position.getY() + vector.y);
    }
}
