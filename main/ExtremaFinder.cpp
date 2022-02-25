#include "RootFinder.h"
#include <iostream>

using namespace std;

//Main to find extrema of one dimensional function f(x)

int main() {

    //Notice that numerical methods don't distinguish between 0 and very small numbers. So be careful when finding
    //higher-order extrema in functions like x^4, for example.

    //f(x)
    function<double(double)> f1 = [](double x) {
        //return pow(x, 4);
        //return (1-x*x+2*x)*sin(x)-6;
        return exp(-x*x);
    };

    Functor func("exp(-x^2)", f1);
    IntegDeriv func1(func);

    //f'(x)
    function<double(double)> flinha = [&func1](double x) {
        return func1.D1central(1E-5, x);
    };
    Functor fprime("f'(x)", flinha);
    RootFinder root(fprime);

    double a = -1;
    double b = 1;
    //For graph, because BisectionMethod changes values of the interval by reference
    double ag = a;
    double bg = b;
    double error = 1E-4;
    double extreme = root.BisectionMethod(a, b, error);
    
    if (func1.D2central(1E-4, extreme) > 0) {
        cout << "\n Minimum: ";
    } else if (func1.D2central(1E-4, extreme) < 0) {
        cout << "\n Maximum: ";
    } 

    cout << extreme << endl;
    func.Draw(ag, bg, 1000, "x", "y");
}
