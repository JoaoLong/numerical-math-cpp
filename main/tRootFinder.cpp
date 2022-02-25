#include "RootFinder.h"
#include <iostream>

using namespace std;

//Test main of class RootFinder

int main() {

    function<double(double)> f1 = [](double x) {
        return (1-x*x+2*x)*sin(x)-6;
    };

    Functor func("(1-x^2+2x)*sin(x)-6", f1);
    RootFinder root(func);

    double a = 8;
    double b = 11;
    double error = 1E-4;
    cout << "\nBisection: " << root.BisectionMethod(a, b, error) << endl;
    cout << "[" << a << "," << b << "]" << endl;

    double ar = 8;
    double br = 11;
    cout << "\nRegula Falsi: " << root.RegulaFalsi(ar, br, error) << endl;
    cout << "[" << ar << "," << br << "]" << endl;
    
    double an = 10;
    
    function<double(double)> deriv = [](double x) {
        return ((-x*x + 2.*x + 1)*cos(x)+2.*(x-1)*sin(x));
    };

    cout << "\nNewton Raphson: " << root.NewtonRaphson(an, error, deriv) << endl;
    cout << "\nNewton Numerical: " << root.NewtonNumerical(an, error) << endl;

    double as = 8.;
    double bs = 11.;

    cout << "\nSecant: " << root.SecantMethod(as, bs, error) << endl;

    func.Draw(-10, 20, 1000, "x", "y");
}
