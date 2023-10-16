package lab;

import javafx.geometry.Rectangle2D;

public interface Collisionable {
    Rectangle2D getHitbox();
    default boolean intersects(Collisionable other) {
        return getHitbox().intersects(other.getHitbox());
    }
}
