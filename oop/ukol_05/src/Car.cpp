#include "Car.h"

Car::Car(string vyrobce, string model, int rok_vyroby, string barva)
{
    this->manufacture = vyrobce;
    this->model = model;
    this->year = rok_vyroby;
    this->color = barva;
    this->speed = 90;
}

void Car::maxSpeed(int rychlost)
{
    this->speed += rychlost;
    cout << "Zrychleni vozidla " << this->speed << " km/h." << endl;
}

PrivateCar::PrivateCar(string vyrobce, string model, int rok_vyroby, string barva, int sedadla, int dvere) : Car(vyrobce, model, rok_vyroby, barva)
{
    this->seats = sedadla;
    this->doors = dvere;
}

void PrivateCar::numberOfSeats()
{
    cout << "Pocet sedadel ve vozidle: " << this->seats << endl;
}

void PrivateCar::numberOfDoors()
{
    cout << "Pocet dveří ve vozidle: " << this->doors << endl;
}

Truck::Truck(string vyrobce, string model, int rok_vyroby, string barva, int vaha) : Car(vyrobce, model, rok_vyroby, barva)
{
    this->weight = vaha;
}

void Truck::truckWeight(int vaha)
{
    cout << "Váha vozidla je: " << vaha << " tun." << endl;
}
