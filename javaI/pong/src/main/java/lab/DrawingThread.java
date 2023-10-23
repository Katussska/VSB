package lab;

import javafx.animation.AnimationTimer;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;

public class DrawingThread extends AnimationTimer {

	private final Canvas canvas;
	private final GraphicsContext gc;
	private final Game game;

	public DrawingThread(Canvas canvas, Game game) {
		this.canvas = canvas;
		this.gc = canvas.getGraphicsContext2D();
		this.game = game;
	}

	@Override
	public void handle(long now) {
		gc.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
		game.draw(gc);
		game.simulate();
	}
}
