package cz.vsb.fei.java2.testhashcode;

public enum NestType {
    CUP("Kalichové", "\\__/", "(4/3*PI(diameter/2)^3)/2") {
        @Override
        double calculateVolume(double diameter) {
            return (4.0 / 3.0 * Math.PI * Math.pow(diameter / 2, 3)) / 2;
        }
    },
    PLATFORM("Platforma", "----", "0") {
        @Override
        double calculateVolume(double diameter) {
            return 0;
        }
    };

    private final String name;
    private final String pictogram;
    private final String volumeCalculator;

    NestType(String name, String pictogram, String volumeCalculator) {
        this.name = name;
        this.pictogram = pictogram;
        this.volumeCalculator = volumeCalculator;
    }

    public String getName() {
        return name;
    }

    public String getPictogram() {
        return pictogram;
    }

    abstract double calculateVolume(double diameter);

    public void print(double diameter) {
        System.out.println(String.format("%s %s Volume: %.2f", name, pictogram, calculateVolume(diameter)));
    }
}