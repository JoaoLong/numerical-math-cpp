#include "Xvar.h"
#include <iostream>

using namespace std;

//Test main of class Xvar

int main() {
    vector <double> v = {0, 1, 2, 3, 4};
    vector <double> v1 = {1, 2, 3, 4, 5};
    double k = 2.5;
    initializer_list<double> l = {4,5,6,7,8};

    //Constructors Xvar(vector<double>)
    Xvar A(v), B(v1);

    //Operators testing
    cout << "A: " << A << endl;
    cout << "A+B: " << A+B << endl;
    cout << "2.5*B: " << k*B << endl;
    cout << A[2] << endl;  
    A=B;
    cout << A << endl;     

    for (int i = 0; i < A.X().size(); i++) {
        cout << A.X()[i] << endl;
    }    

    //Copy constructor
    Xvar C(B);
    cout << C << endl;

    //Constructor Xvar(int)
    Xvar D(50);
    cout << D << endl;

    //Constructor Xvar(initializer_list)
    Xvar E(l);
    cout << E << endl;
}