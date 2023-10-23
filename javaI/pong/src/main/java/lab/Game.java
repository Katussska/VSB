package lab;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Game {
    private double width;
    private double height;
    private PlayingField field;
    private GameObject[] objects = new GameObject[3];

    public Game(double width, double height, String playerAName, String playerBName) {
        this.width = width;
        this.height = height;
        field = new PlayingField(width, height, playerAName, playerBName);
        objects[0] = new Ball(this, field);
        objects[1] = new Bat(this, 30);
        objects[2] = new Bat(this, (int)width - 45);
    }

    public void draw(GraphicsContext gc) {
        field.draw(gc);
        for (GameObject obj : objects)
            obj.draw(gc);
    }

    public void simulate() {
        for (GameObject obj : objects) {
            obj.simulate();
            if (obj instanceof Ball) {
                for (GameObject secondObj : objects) {
                    if (secondObj != obj && secondObj.intersects(obj)) {
                        ((Ball) obj).hit();
                    }
                }
            }
        }
//        ball.simulate();
//        for (Bat bat : bats) {
//            bat.simulate();
//            if (bat.intersects(ball)) {
//                ball.hit();
//            }
//        }
    }

    public double getWidth() {
        return width;
    }

    public double getHeight() {
        return height;
    }

    public void setPlayerPosition(int playerIndex, double newPosition) {
        objects[playerIndex].position = new Point2D(objects[playerIndex].position.getX(), newPosition);
    }

}
