import random

import playground


class Atom:
    def __init__(self, x, y, sx, sy, rad, color):
        """
        Inicializator třídy Atom
        :param x: souřadnice X
        :param y: soouřadnice Y
        :param rad: poloměr
        :param color: barva
        """
        self.x = x
        self.y = y
        self.speed_x = sx
        self.speed_y = sy
        self.rad = rad
        self.color = color

    def to_tuple(self):
        """Vrátí n-tici hodnot 
        příklad: x = 10, y = 12, rad = 15, color = 'green' -> (10,12,15,'green')
        """
        return self.x, self.y, self.speed_x, self.speed_y, self.rad, self.color

    def move(self, width, height):
        """
        Posune atom o vektor rychlosti a zohlední šířku a výšku prostoru
        :param width: šířka prostoru
        :param height: výška prostoru
        """
        self.x += self.speed_x
        self.y += self.speed_y

        # Kontrola kolize s okrajem prostoru
        if self.x - self.rad < 0:
            self.x = self.rad
            self.speed_x = -self.speed_x
        elif self.x + self.rad > width:
            self.x = width - self.rad
            self.speed_x = -self.speed_x

        if self.y - self.rad < 0:
            self.y = self.rad
            self.speed_y = -self.speed_y
        elif self.y + self.rad > height:
            self.y = height - self.rad
            self.speed_y = -self.speed_y


class FallDownAtom(Atom):
    def __init__(self, x, y, sx, sy, rad, color):
        super().__init__(x, y, sx, sy, rad, color)
        self.g = 3.0
        self.damping = 0.8

    def move(self, width, height):
        """
        Posune atom o vektor rychlosti s gravitací
        a zohlední šířku a výšku prostoru
        :param width: šířka prostoru
        :param height: výška prostoru
        """

        super().move(width, height)

        self.speed_y += self.g

        if self.x - self.rad < 0 or self.x + self.rad > width:
            self.speed_x *= -self.damping
        if self.y - self.rad < 0 or self.y + self.rad > height:
            self.speed_y *= -self.damping

        if self.y + self.rad == height:
            self.speed_x *= self.damping
            self.speed_y *= self.damping


class ExampleWorld(object):

    def __init__(self, size_x, size_y, count):
        self.width = size_x
        self.height = size_y
        self.count = count
        self.atoms = []
        for _ in range(count):
            atom = self.random_atom()
            self.atoms.append(atom)

    def random_atom(self):
        return FallDownAtom(random.randint(1, self.width - 1),  # x
                            random.randint(1, self.height - 1),  # y
                            random.randint(1, 20),  # speed x
                            random.randint(1, 20),  # speed y
                            random.randint(1, 20),  # ran
                            random.choice(['blue', 'red', 'green', 'black', 'yellow']))  # color

    def tick(self):
        """This method is called by playground. Sends a tuple of atoms to rendering engine.

        :param size_x: world size x dimension
        :param size_y: world size y dimension
        :return: tuple of atom objects, each containing (x, y, radius) coordinates
        """
        list = []

        for atom in self.atoms:
            atom.move(self.width, self.height)
            list.append((atom.x, atom.y, atom.rad, atom.color))

        return list


if __name__ == '__main__':
    size_x, size_y = 700, 400
    count = random.randint(2, 10)

    world = ExampleWorld(size_x, size_y, count)
    playground.run((size_x, size_y), world)
