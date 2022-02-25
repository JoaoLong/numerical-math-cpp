#include "ODEpoint.h"
#include <iostream>

using namespace std;

//Test main of class ODEpoint

int main() {
    vector <double> v = {0, 1, 2, 3, 4};
    initializer_list<double> l = {4,5,6,7,8};

    vector <double> v1 = {6,7,8,9,10};
    initializer_list<double> l1 = {11,12,13,14,15};

    double t = 2.3;
    double t1 = 4.4;

    //Constructors Xvar(vector<double>)
    Xvar A(v);
    Xvar F(v1);

    //Constructors ODEpoint
    ODEpoint B;
    cout << B << endl;

    ODEpoint C(t, A);
    ODEpoint D(t, v);
    ODEpoint E(t, l);

    cout << C << endl;
    cout << D << endl;
    cout << E << endl;

    C.SetODEpoint(t1, F);
    D.SetODEpoint(t1, v1);
    E.SetODEpoint(t1, l1);

    cout << "-------------------------------------------" << endl;

    cout << C << endl;
    cout << D << endl;
    cout << E << endl;
}