#include "RootFinderND.h"
#include <iostream>

using namespace std;

//Main to find extrema of N dimensional function f(x1, ..., xn)

int main() {

    //Notice that numerical methods don't distinguish between 0 and very small numbers. So be careful when finding
    //higher-order extrema in functions like x^4, for example.

    //f(x)
    int dim = 3;

    function<double(vector<double>)> f1 = [](vector<double> x) {
        return x[0]*x[0]+x[1]*x[1];
        //return 1;
    };

    string name = "x^2+y^2";

    FunctorND func(name, dim, f1);

    IntegDerivND func1(func);

    //∇f(x)
    vector<function<double(vector<double>)>> flinha(dim);
    
    for (int i = 0; i < dim; i++) {
        flinha[i] = [&func1, i](vector<double> x) {
            return func1.Gradient(1E-5, x)[i];
        };
    }    
    vector<FunctorND> fprime(dim);
    for (int i = 0; i < dim; i++) {
        string s = "∇f" + to_string(i);
        fprime[i] = FunctorND(&s[0], dim, flinha[i]);
    }
 
    RootFinderND root(fprime);

    vector<double> guess = {1, 1};
    vector <double> extreme = root.NewtonNDNumerical(guess, 1E-5);

    cout << "\n Extreme: [ ";
    for (int i = 0; i < dim; i++) {
        cout << extreme[i] << " ";
    }
    cout << "]" << endl;    

    func.Draw(extreme[0]-1, extreme[0]+1, extreme[1]-1, extreme[1]+1, 100, 100, "x", "y", "z");
}
