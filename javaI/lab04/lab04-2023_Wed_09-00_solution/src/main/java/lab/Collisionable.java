package lab;

import javafx.geometry.Rectangle2D;

public interface Collisionable {
	Rectangle2D getBoundingBox(); 
	
	void hitBy(Collisionable that);
	
	default void checkCollision(Object entity) {
		if (entity instanceof Collisionable ce2 
				&& this.getBoundingBox().intersects(ce2.getBoundingBox())) {
			ce2.hitBy(this);
			this.hitBy(ce2);
		}
	}
}
