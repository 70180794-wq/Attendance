#include <iostream>
using namespace std;
class Boxt {
private:
    double side;

public:
   
    Boxt() {
        side = 1.0;
    }
  
    Boxt(double s) {
        side = s;
    }
    double calculateVolume() {
        return side * side * side;
    }
};

int main() {
    Boxt defaultBox;     
    Boxt customBox(5.0);  

    std::cout << "Volume of Default Box: " << defaultBox.calculateVolume() << std::endl;
    std::cout << "Volume of Custom Box: " << customBox.calculateVolume() << std::endl;
    return 0;
}