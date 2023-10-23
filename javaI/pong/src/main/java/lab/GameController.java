package lab;

import javafx.animation.AnimationTimer;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;

public class GameController {

    private Game game;

    @FXML
    private Slider playerASlider;

    @FXML
    private Slider playerBSlider;

    @FXML
    private Canvas canvas;

    @FXML
    private TextField playerAName;

    @FXML
    private TextField playerBName;

    private AnimationTimer animationTimer;

    public GameController() {
    }

    public void startGame() {
        this.game = new Game(canvas.getWidth(), canvas.getHeight(), playerAName.getText(), playerBName.getText());
        playerAName.setDisable(true);
        playerBName.setDisable(true);
        //Draw scene on a separate thread to avoid blocking UI.
        animationTimer = new DrawingThread(canvas, game);

        playerASlider.valueProperty().addListener(this::playerAChangedPosition);
        playerASlider.setMax(game.getHeight() - Constants.BAT_HEIGHT - 30);
        game.setPlayerPosition(1, playerASlider.getValue());

        playerBSlider.valueProperty().addListener(this::playerBChangedPosition);
        playerBSlider.setMax(game.getHeight() - Constants.BAT_HEIGHT - 30);
        game.setPlayerPosition(2, playerBSlider.getValue());

        animationTimer.start();
    }


    public void stopGame() {
        animationTimer.stop();
    }

    @FXML
    private void startPressed() {
        this.startGame();
    }


    private void playerAChangedPosition(ObservableValue<? extends Number> observable
            , Number oldValue, Number newValue) {
        game.setPlayerPosition(1, newValue.doubleValue());
    }

    private void playerBChangedPosition(ObservableValue<? extends Number> observable
            , Number oldValue, Number newValue) {
        game.setPlayerPosition(2, newValue.doubleValue());
    }
}
