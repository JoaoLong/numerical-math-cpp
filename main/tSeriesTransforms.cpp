#include "SeriesTransforms.h"
#include <iostream>

using namespace std;

//Test main of class SeriesTransforms

int main() {

    //Infinite series

    function<double(int)> g = [](int n) {
        return sin(n)/pow(n, 2);
    };

    cout << "\n Series of 1/n²: " << SeriesTransforms::InfiniteSeries(g, 1E-10, 1) << endl;

    //Taylor and Fourier Series

    function<double(double)> f1 = [](double x) {
        return exp(x);
    };

    Functor func("exp(x)", f1);
    SeriesTransforms f(func);

    double x = 2;
    double x0 = 0;
    double L = 3;
 
    cout << "\n f(2): " << f1(x) << endl;
    cout << "\n Taylor expansion of order 3 at x = 2: " << f.TaylorSeries(3, x0, x) << endl;
    cout << "\n Fourier expansion of order 3 at x = 2: " << f.FourierSeries(3, L, x) << endl;
    
    f.Draw(3, x0, L, -3, 3, 1000);

    //f.Draw(-10, 20, 1000, "x", "y");
}
