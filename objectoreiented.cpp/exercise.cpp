#include <iostream>
#include <conio.h>  // for getch()
using namespace std;

class tollBooth
{
private:
    unsigned int totalCars;
    double totalCash;

public:
    // Constructor
    tollBooth() : totalCars(0), totalCash(0.0) {}

    // Paying car
    void payingCar()
    {
        totalCars++;
        totalCash += 0.50;
    }

    // Non-paying car
    void nopayCar()
    {
        totalCars++;
    }

    // Display totals (const function)
    void display() const
    {
        cout << "\nTotal cars: " << totalCars;
        cout << "\nTotal cash: $" << totalCash << endl;
    }
};

int main()
{
    tollBooth booth;
    char ch;

    cout << "Press keys:\n";
    cout << "  'p' for paying car\n";
    cout << "  'n' for non-paying car\n";
    cout << "  'Esc' to exit\n";

    while (true)
    {
        ch = getch();  // get character without pressing Enter

        if (ch == 'p' || ch == 'P')
        {
            booth.payingCar();
        }
        else if (ch == 'n' || ch == 'N')
        {
            booth.nopayCar();
        }
        else if (ch == 27)  // ESC key
        {
            break;
        }
    }

    booth.display();

    return 0;
}