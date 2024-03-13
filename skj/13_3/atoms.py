import playground
import random


class Atom:
    def __init__(self, x, y, rad, color):
        """
        Inicializator třídy Atom
        :param x: souřadnice X
        :param y: soouřadnice Y
        :param rad: poloměr
        :param color: barva
        """
        pass

    def to_tuple(self):
        """Vrátí n-tici hodnot 
        příklad: x = 10, y = 12, rad = 15, color = 'green' -> (10,12,15,'green')
        """
        pass

    def move(self, width, height):
        pass


class ExampleWorld(object):

    def __init__(self, size_x, size_y):
        self.width = size_x
        self.height = size_y

    def random_atom(self):
        pass

    def tick(self):
        """This method is called by playground. Sends a tuple of atoms to rendering engine.

        :param size_x: world size x dimension
        :param size_y: world size y dimension
        :return: tuple of atom objects, each containing (x, y, radius) coordinates 
        """

        return ((80, 50, 10, 'green'), (150, 200, 20, 'green'))


if __name__ == '__main__':
    size_x, size_y = 700, 400

    world = ExampleWorld(size_x, size_y)
    playground.run((size_x, size_y), world)
