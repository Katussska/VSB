package lab;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.TextAlignment;

public class PlayingField {
    private double width;
    private double height;
    private int scoreLeft = 0;
    private int scoreRight = 0;
    private GraphicsContext gc;

    PlayingField(GraphicsContext gc, double w, double h) {
        this.gc = gc;
        this.width = w;
        this.height = h;
    }

    public void scoreLeft() {
        scoreLeft += 1;
    }

    public void scoreRight() {
        scoreRight += 1;
    }

    public void drawScore() {
        // score text
        gc.setFont(Font.font("monospace", 50));
        gc.setTextAlign(TextAlignment.RIGHT);
        gc.fillText(String.valueOf(scoreLeft), width / 2 - 20, 50);
        gc.setTextAlign(TextAlignment.LEFT);
        gc.fillText(String.valueOf(scoreRight), width / 2 + 20, 50);
    }

    public void drawBackground() {
        gc.setFill(Color.BLACK);
        gc.fillRect(0, 0, width, height);
    }

    public void drawField() {
        // horizontal lines
        gc.setFill(Color.WHITE);
        gc.fillRect(0, 0, width, 15);
        gc.fillRect(0, height - 15, width, 15);

        // playing net
        for (int i = 0; i < 15; i++) {
            gc.fillRect(width / 2 - 15, i * 15 + i * 15, 15, 15);
        }
    }

    public void draw() {
        gc.clearRect(0, 0, width, height);
        drawBackground();
        drawField();
        drawScore();
    }
}
