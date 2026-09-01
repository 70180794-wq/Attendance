#include <iostream>
3 using namespace std;
4
5 int main()
6 {
7 const int SIZE = 8;
8 int set[SIZE] = {5, 10, 15, 20, 25, 30, 35, 40};
9 int *numPtr = nullptr; // Pointer
10 int count; // Counter variable for loops
11
12 // Make numPtr point to the set array.
13 numPtr = set;
14
15 // Use the pointer to display the array contents.
16 cout << "The numbers in set are:\n";
17 for (count = 0; count < SIZE; count++)
18 {
19 cout << *numPtr << " ";
20 
21 }
22
23 // Display the array contents in reverse order.
24 cout << "\nThe numbers in set backward are:\n";
25 for (count = 0; count < SIZE; count++)
26 {
27 numPtr−−;
28 cout << *numPtr << " ";
29 }
30 return 0;
31 }