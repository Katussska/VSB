package lab;

import javafx.animation.AnimationTimer;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;

public class DrawingThread extends AnimationTimer {

    private final Canvas canvas;
    private final GraphicsContext gc;

    public DrawingThread(Canvas canvas) {
        this.canvas = canvas;
        this.gc = canvas.getGraphicsContext2D();

    }

    @Override
    public void handle(long now) {

        double x = 300;
        double y = 200;

        //background
        gc.setFill(Color.BLACK);
        gc.fillRect(0, 0, x * 2, y * 2);

        //lines
        gc.setFill(Color.GRAY);
        gc.fillRect(0, 0, x * 2, 15);
        gc.fillRect(0, 385, x * 2, 15);

        //player left
        gc.fillRect(30, 180, 15, 75);

        //player right
        gc.fillRect(555, 250, 15, 75);

        //middle
        for (int i = 12; i <= y * 2; i += 30)
            gc.fillRect(292.5, i, 15, 15);

        //rectangle
        gc.fillRect(500, 260, 15, 15);

        //score left
        gc.fillText("0", 240, 70);
        gc.setFont(Font.font(50));

        //score right
        gc.fillText("3", 330, 70);
    }
}