
#include <iostream>
using namespace std;

class Vehicle
{
public:
    void display()
    {
        cout << "Vehicle" << endl;
    }
};

class Car : public Vehicle
{
public:
    void display()
    {
        cout << "Car" << endl;
    }
};	int main()
{
    Car c;
    c.display();
   // c.Vehicle::display();
}