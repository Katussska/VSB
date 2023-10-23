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
    private String playerAName;
    private String playerBName;

    PlayingField(double w, double h, String playerAName, String playerBName) {
        this.width = w;
        this.height = h;
        this.playerAName = playerAName;
        this.playerBName = playerBName;
    }

    public void scoreLeft() {
        scoreLeft += 1;
    }

    public void scoreRight() {
        scoreRight += 1;
    }

    public void drawScore(GraphicsContext gc) {
        // score text
        gc.setFont(Font.font("monospace", 50));
        gc.setTextAlign(TextAlignment.RIGHT);
        gc.fillText(String.valueOf(scoreLeft), width / 2 - 20, 50);
        gc.setTextAlign(TextAlignment.LEFT);
        gc.fillText(String.valueOf(scoreRight), width / 2 + 20, 50);
    }

    public void drawBackground(GraphicsContext gc) {
        gc.setFill(Color.BLACK);
        gc.fillRect(0, 0, width, height);
    }

    public void drawField(GraphicsContext gc) {
        // horizontal lines
        gc.setFill(Color.WHITE);
        gc.fillRect(0, 0, width, 15);
        gc.fillRect(0, height - 15, width, 15);

        // playing net
        for (int i = 0; i < 15; i++) {
            gc.fillRect(width / 2 - 15, i * 15 + i * 15, 15, 15);
        }
    }

    public void drawNames(GraphicsContext gc) {
        gc.setFont(Font.font("monospace", 20));
        gc.setTextAlign(TextAlignment.RIGHT);
        gc.fillText(playerAName, width / 2 - 20, 70);
        gc.setTextAlign(TextAlignment.LEFT);
        gc.fillText(playerBName, width / 2 + 20, 70);
    }

    public void draw(GraphicsContext gc) {
        gc.clearRect(0, 0, width, height);
        drawBackground(gc);
        drawField(gc);
        drawScore(gc);
        drawNames(gc);
    }
}
