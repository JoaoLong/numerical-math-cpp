#include "FunctorND.h"
#include <iostream>

using namespace std;

//Test main of class FunctorND

int main() {
    string name = "sin(x)*sin(y) / sqrt(x^2+y^2)";

    function<double(vector<double>)> f1 = [](vector<double> x) {
        return sin(x[0])*sin(x[1]) / sqrt(x[0]*x[0]+x[1]*x[1]);
    };

    FunctorND func(name, 2, f1);
    cout << "f(1, 2) = " << func({1, 2}) << endl;

    func.Draw(-10, 10, -10, 10, 100, 100, "x", "y", "z");
}

