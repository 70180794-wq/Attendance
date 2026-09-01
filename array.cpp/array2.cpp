#include <iostream>
using namespace std;

int main() {
    int studentmarks[5][6];

    for (int i = 0; i < 5; i++) {
        int sum = 0;
        cout << "Enter marks for student " << i + 1 << endl;

        for (int j = 0; j < 6; j++) {
            cin >> studentmarks[i][j];
            sum += studentmarks[i][j];
        }

        cout << "Total marks of student " << i + 1 << " = " << sum << endl;
        cout << "Average marks of student " << i + 1 << " = " << sum / 6 << endl;
        cout << endl;
    }

    return 0;
}
