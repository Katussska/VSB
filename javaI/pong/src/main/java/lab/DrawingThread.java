package lab;

import javafx.animation.AnimationTimer;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.text.Font;

public class DrawingThread extends AnimationTimer {

	private final Canvas canvas;
	private final GraphicsContext gc;
	private final Game game;

	public DrawingThread(Canvas canvas) {
		this.canvas = canvas;
		this.gc = canvas.getGraphicsContext2D();
		this.game = new Game(canvas.getWidth(), canvas.getHeight());
	}

	@Override
	public void handle(long now) {
		gc.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
		game.draw(gc);
		game.simulate();
	}
}
