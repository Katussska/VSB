package lab;

import javafx.geometry.Point2D;
import javafx.geometry.Rectangle2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public abstract class GameObject implements DrawableSimulable, Collisionable {
    protected Point2D position;
    protected final int width;
    protected final int height;
    protected Game game;

    public GameObject(Game game, int w, int h) {
        this.game = game;
        this.position = new Point2D(20, 20);
        this.width = w;
        this.height = h;
    }

    public GameObject(Game game, Point2D startPos, int w, int h) {
        this.game = game;
        this.position = startPos;
        this.width = w;
        this.height = h;
    }

    public void draw(GraphicsContext gc) {
        gc.save();
        gc.setFill(Color.WHITE);
        gc.fillRect(position.getX(), position.getY(), width, height);
        gc.restore();
    }

    public Rectangle2D getHitbox() {
        return new Rectangle2D(position.getX(), position.getY(), width, height);
    }
}
