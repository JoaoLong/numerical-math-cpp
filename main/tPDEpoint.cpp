#include "PDEpoint.h"
#include <iostream>

using namespace std;

//Test main of class PDEpoint

int main() {
    vector <double> x = {0, 1, 2, 3, 4};
    double y = 2.3;

    vector <double> x1 = {0, 0.5, 1, 1.5, 2};
    double y1 = 3.5;

    //Constructors PDEpoint

    PDEpoint A(x, y);
    PDEpoint B(x, y);

    cout << A << endl;
    cout << B << endl;

    B.SetPDEpoint(x1, y1);

    cout << "-------------------------------------------" << endl;

    cout << B << endl;
}