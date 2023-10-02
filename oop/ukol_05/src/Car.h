#include <iostream>
#include <string>

using namespace std;

class Car
{
private:
    string manufacture;
    string model;
    string color;
    int year;
    int speed;

public:
    Car(string vyrobce, string model, int rok_vyroby, string barva);
    void maxSpeed(int rychlost);
};

class PrivateCar : public Car
{
private:
    int seats;
    int doors;

public:
    PrivateCar(string vyrobce, string model, int rok_vyroby, string barva, int sedadla, int dvere);
    void numberOfSeats();
    void numberOfDoors();
};

class Truck : public Car
{
private:
    int weight;

public:
    Truck(string vyrobce, string model, int rok_vyroby, string barva, int vaha);
    void truckWeight(int vaha);
};