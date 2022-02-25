#include "IntegDerivND.h"
#include <iostream>

using namespace std;

//Test main of class IntegDerivND

int main() {

    function<double(vector<double>)> f1 = [](vector<double> x) {
        return exp(-x[0]*x[0]-x[1]*x[1]);
    };

    function<int(vector<double>)> ind = [](vector<double> x) {
        if (x[0]*x[0]+x[1]*x[1] <= 1) {
            return 1;
        } else {
            return 0;
        }
    };

    string name = "exp(-x^2-y^2)";

    FunctorND func(name, 2, f1);

    IntegDerivND f(func);

    double errormc = 1E-10;
    int nmc = 100000;

    double errormc1 = 1E-10;
    int nmc1 = 100;

    double integralmc2 = 0.;
    double errormc2 = 0.;


    for (int i = 0; i < 10000; i++) {
        integralmc2 += f.IntegrateRegionMC(ind, {{-1,1}, {-1,1}}, errormc1, nmc1);
        errormc2 += errormc1;
    }
    
    cout << "\n Integral MC: " << integralmc2/10000 << endl;
    cout << "\n Error MC: " << errormc2/10000 << endl;

    double integralmc = f.IntegrateIntervalMC({{0,1}, {0,1}}, errormc, nmc);

    double h = 1E-5;
    double h2 = 1E-4;
    vector<double> x = {1,1};
    int i = 1;
    int j = 2;

    cout << "\n Integral MC: " << integralmc << endl;
    cout << "\n Error MC: " << errormc << endl;
    
    cout << "\n ∂/∂x" << i << " (1,1) = " << f.D1backward(i, h, x);
    cout << "\n ∂/∂x" << i << " (1,1) = " << f.D1forward(i, h, x);
    cout << "\n ∂/∂x" << i << " (1,1) = " << f.D1central(i, h, x);
    cout << "\n ∂/∂x" << i << " (1,1) = " << f.D1fivepoint(i, h, x);

    cout << "\n\n";

    cout << "\n ∂²/∂x" << i << "² (1,1) = " << f.D2backward(i, h2, x);
    cout << "\n ∂²/∂x" << i << "² (1,1) = " << f.D2forward(i, h2, x);
    cout << "\n ∂²/∂x" << i << "² (1,1) = " << f.D2central(i, h2, x);
    cout << "\n ∂²/∂x" << i << "² (1,1) = " << f.D2fivepoint(i, h2, x);

    cout << "\n\n";

    cout << "\n ∂²/∂x" << i << "∂x" << j << " (1,1) = " << f.D2mixedcentral(i, j, h2, h2, x);
    cout << "\n ∂²/∂x" << i << "∂x" << j << " (1,1) = " << f.D2mixedfivepoint(i, j, h2, h2, x);

    cout << "\n\n";

    cout << "\n ∇ F (1,1) = [" << f.Gradient(h, x) << "  ]";

    cout << "\n\n";

    cout << "\n Hessian F (1,1) = \n\n" << f.Hessian(h2, h2, x) << endl;

    cout << "\n ∇² F (1,1) = " << f.Laplacian(h2, x) << endl;

    func.Draw(0, 1, 0, 1, 100, 100, "x", "y", name);
}
