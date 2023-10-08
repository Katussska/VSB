package lab;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Game {
    private double width;
    private double height;
    private Ball ball;
    private Bat player1;
    private Bat player2;
    private Bat[] players;

    public Game(double width, double height) {
        this.width = width;
        this.height = height;
        ball = new Ball(this);
        players = new Bat[]{
                new Bat(this, 30),
                new Bat(this, (int) width - 45)
        };
    }

    public void draw(GraphicsContext gc) {
        gc.clearRect(0, 0, width, height);

        //background
        gc.setFill(Color.BLACK);
        gc.fillRect(0, 0, width, height);

        //lines
        gc.setFill(Color.GRAY);
        gc.fillRect(0, 0, width, 15);
        gc.fillRect(0, height - 15, width, 15);

        //middle
        for (int i = 0; i < 15; i++) {
            gc.fillRect(width / 2 - 15, i * 15 + i * 15, 15, 15);
        }

        ball.draw(gc);
        for (Bat player : players) {
            player.draw(gc);
        }
    }

    public void simulate() {
        ball.simulate();
        for (Bat player : players) {
            player.simulate();
            if (player.getBB().intersects(ball.getBB())) {
                ball.hit();
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
