package lab;

import javafx.geometry.Point2D;

import java.util.Random;

class Vector {
    public int x;
    public int y;

    public Vector(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

public class Ball extends GameObject {
    private PlayingField field;
    private final int speed = 2;
    private Vector vector = new Vector(speed, speed);

    public Ball(Game game, PlayingField field) {
        super(game, 15, 15);
        this.field = field;
    }

    public Ball(Game game, Point2D startPos) {
        super(game, startPos, 15, 15);
    }

    public void hit() {
        vector.x *= -1;
    }

    // xDirection either -1 or 1
    public void reset(int xDirection) {
        Random rand = new Random();
        position = new Point2D(game.getWidth() / 2, rand.nextInt((int) (game.getHeight() - 40 - 40) + 1) + 40);
        vector = new Vector(speed * xDirection, speed);
    }

    public void simulate() {
        if (position.getX() + vector.x < 0) {
            field.scoreRight();
            reset(-1);
            return;
        }
        if (position.getX() + this.width + vector.x > game.getWidth()) {
            field.scoreLeft();
            reset(1);
            return;
        }
        if (position.getY() + vector.y < 15 || position.getY() + this.height + vector.y > game.getHeight() - 15) {
            vector.y *= -1;
        }
        position = new Point2D(position.getX() + vector.x, position.getY() + vector.y);
    }
}
