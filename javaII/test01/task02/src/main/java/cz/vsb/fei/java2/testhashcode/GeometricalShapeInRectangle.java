package cz.vsb.fei.java2.testhashcode;

public enum GeometricalShapeInRectangle {
    RECTANGLE("Rectangle", "width * height") {
        @Override
        double surface(double width, double height) {
            return width * height;
        }
    },

    ELIPSE("Ellipse", "π * semiMajorAxis * semiMinorAxis") {
        @Override
        double surface(double semiMajorAxis, double semiMinorAxis) {
            return 3.14 * semiMajorAxis * semiMinorAxis;
        }
    };

    private final String name;
    private final String surfaceEquation;

    GeometricalShapeInRectangle(String name, String surfaceEquation) {
        this.name = name;
        this.surfaceEquation = surfaceEquation;
    }

    abstract double surface(double width, double height);

    void printCalculation(double width, double height) {
        System.out.println(String.format("%s, %s = %s", this.name, this.surfaceEquation, this.surface(width, height)));
    }
}
