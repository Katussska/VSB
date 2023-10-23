package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Bat extends GameObject {

    private int speed = 2;

    public Bat(Game game, int posX) {
        super(game, new Point2D(posX, 30), 15, Constants.BAT_HEIGHT);
    }

    public Bat(Game game, Point2D pos) {
        super(game, pos, 15, Constants.BAT_HEIGHT);
    }

    public void simulate() {
//        if (position.getY() + speed < 30 || position.getY() + speed > game.getHeight() - 30 - height) {
//            speed *= -1;
//        }
//        position = new Point2D(position.getX(), position.getY() + speed);
    }
}
