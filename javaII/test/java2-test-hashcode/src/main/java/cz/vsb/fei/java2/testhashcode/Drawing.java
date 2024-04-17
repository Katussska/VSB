package cz.vsb.fei.java2.testhashcode;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Drawing {

	private final String name;
	private final List<Shape> shapes = new ArrayList<>();

	private final List<PropertyChangeListener> propertyChangeListeners = new ArrayList<>();

	public Drawing(String name) {
		this.name = name;
	}

	public void add(Shape shape) {
		shapes.add(shape);
		firePropertyChanged();
	}

	public boolean add(PropertyChangeListener listener) {
		return propertyChangeListeners.add(listener);
	}

	public boolean remove(PropertyChangeListener listener) {
		return propertyChangeListeners.remove(listener);
	}
	
	private void firePropertyChanged() {
		PropertyChangeEvent evt = new PropertyChangeEvent(this, "shapes", Collections.emptyList(), shapes);
		for (PropertyChangeListener propertyChangeListener : propertyChangeListeners) {
			propertyChangeListener.propertyChange(evt);
		}
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;

		Drawing drawing = (Drawing) o;
		return name.equals(drawing.name) && shapes.equals(drawing.shapes) && propertyChangeListeners.equals(drawing.propertyChangeListeners);
	}

	@Override
	public int hashCode() {
		int result = name.hashCode();
		result = 31 * result + shapes.hashCode();
		result = 31 * result + propertyChangeListeners.hashCode();
		return result;
	}

	public List<Shape> getShapes() {
		return shapes;
	}
}
