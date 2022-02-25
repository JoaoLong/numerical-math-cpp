#include "IntegDerivVF.h"
#include <iostream>

using namespace std;

//Test main of class IntegDerivVF

int main() {

   vector<function<double(vector<double>)>> fi(3);
    fi[0] = [](vector<double> x) {  // x² + y² - z²
        return x[0]*x[0] + x[1]*x[1] - x[2]*x[2];
    };

    fi[1] = [](vector<double> x) { // // x² - y² + z²
        return x[0]*x[0] - x[1]*x[1] + x[2]*x[2];
    };

    fi[2] = [](vector<double> x) { // // x² - y² - z²
        return x[0]*x[0] - x[1]*x[1] - x[2]*x[2];
    };

    vector<FunctorND> func(fi.size());
    for (int i = 0; i < fi.size(); i++) {
        string s = "f" + to_string(i);
        func[i] = FunctorND(&s[0], 3, fi[i]);
    }
 
    VectorField vec(func);
    IntegDerivVF intderiv(vec);

    vector<double> x = {1,1,1};
    double h = 1E-5;

    cout << "\n\n";

    cout << "\n J(1,1,1) = \n\n" << intderiv.JacobianMatrix(h, x) << endl;

    cout << "\n ∇.F (1,1,1) = " << intderiv.Divergence(h, x) << endl;

    cout << "\n ∇xF (1,1,1)= " << intderiv.Curl(h, x) << endl;

    cout << "\n ∇²F (1,1,1) = " << intderiv.Laplacian(h, x) << endl;
}
