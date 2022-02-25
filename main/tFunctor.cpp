#include "Functor.h"
#include <iostream>

using namespace std;

//Test main of class Functor

int main() {
    function<double(double)> f1 = [](double x) {
        return sin(1/x);
    };

    function<double(double)> f2 = [](double x) {
        return x*x*x*cos(x);
    };

    Functor func1("sin(1/x)", f1);
    Functor func2("x^3*cos(x)", f2);
    cout << "f1(2) = " << func1(2) << endl;
    cout << "f2(2) = " << func2(2) << endl;

    func1.Draw(-10, 10, 10000, "x", "y");
}