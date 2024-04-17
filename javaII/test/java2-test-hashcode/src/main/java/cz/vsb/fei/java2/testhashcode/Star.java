package cz.vsb.fei.java2.testhashcode;

import java.util.Random;

public record Star(int rayLength, int vertices) {

    public static Star generate() {
        Random random = new Random();
        int rayLength = random.nextInt(6) + 1;
        int vertices = random.nextInt(5) + 4;
        return new Star(rayLength, vertices);
    }

    public int perimeter() {
        return rayLength * vertices;
    }
}