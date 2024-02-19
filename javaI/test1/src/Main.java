import java.util.Random;

public class Main {
    public static int getRandomInt(int min, int max) {
        return new Random().nextInt(max - min + 1) + min;
    }

    public static void main(String[] args) {
        Goods[] array = new Goods[20];

        for (int i = 0; i < array.length; i++) {
            int selection = getRandomInt(0, 2);

            switch (selection) {
                case 0:
                    array[i] = new Voucher("Vylet " + getRandomInt(0, 999), getRandomInt(20, 5000), getRandomInt(1, 30));
                    break;
                case 1:
                    array[i] = new Apple("Zelene jablko  " + getRandomInt(0, 999), getRandomInt(20, 5000), getRandomInt(500, 2000), getRandomInt(1, 30));
                    break;
                case 2:
                    array[i] = new Lego("Hrad  " + getRandomInt(0, 999), getRandomInt(20, 5000), getRandomInt(500, 2000));
                    break;
            }
        }

        for (int i = 0; i < array.length; i++) {
            System.out.println(array[i].getDescription());
        }

        for (int i = 0; i < array.length; i++) {

            if (array[i] instanceof IExpiration && ((IExpiration) array[i]).getExpiration() < 50) {
                System.out.println(array[i].getDescription() + " - " + ((IExpiration) array[i]).getExpiration() + " dni do exp.");
            }
        }


    }
}