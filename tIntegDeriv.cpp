#include "IntegDeriv.h"
#include <iostream>

using namespace std;

//Test main of class IntegDeriv

int main() {
    
    function<double(double)> f1 = [](double x) {
        return sin(x);
    };

    Functor func("sin(x)", f1);

    IntegDeriv f(func);

    double h = 1E-5;
    double h2 = 1E-4;
    double h3 = 7E-3;
    double h4 = 3E-3;
    double x = 12;

    double errort = 1E-10;
    double errors = 1E-10;
    double errormc = 1E-10;
    double errormcvn = 1E-10;

    int nmc = 10000;
    int nmcvn = 10000;
    double rep = 1;
    double sum = 0.;
    double errorsum = 0.;

    double integralt = f.TrapezoidalRule(0, x, errort);
    double integrals = f.SimpsonRule(0, x, errors);
    double integralmcvn = f.IntegrateMCVN(0, x, errormcvn, nmcvn);

    for (int i = 0; i < rep; i++) {
        sum += f.IntegrateMC(0, x, errormc, nmc);
        errorsum += errormc;
    }    
    
    cout << "\n f'(2) = " << f.D1backward(h, x);
    cout << "\n f'(2) = " << f.D1central(h, x);
    cout << "\n f'(2) = " << f.D1forward(h, x);
    cout << "\n f'(2) = " << f.D1fivepoint(h, x);

    cout << "\n\n";

    cout << "\n f''(2) = " << f.D2backward(h2, x);
    cout << "\n f''(2) = " << f.D2central(h2, x);
    cout << "\n f''(2) = " << f.D2forward(h2, x);
    cout << "\n f''(2) = " << f.D2fivepoint(h2, x);

    cout << "\n\n";

    cout << "\n f'''(2) = " << f.D3backward(h3, x);
    cout << "\n f'''(2) = " << f.D3central(h3, x);
    cout << "\n f'''(2) = " << f.D3forward(h3, x);
    cout << "\n f'''(2) = " << f.D3fivepoint(h3, x);

    cout << "\n\n";

    cout << "\n f''''(2) = " << f.D4backward(h4, x);
    cout << "\n f''''(2) = " << f.D4central(h4, x);
    cout << "\n f''''(2) = " << f.D4forward(h4, x);
    cout << "\n f''''(2) = " << f.D4fivepoint(h4, x);

    cout << "\n\n";

    cout << "\n Integral Trapezoidal: " << integralt << endl;
    cout << "\n Error Trapezoidal: " << errort << endl;

    cout << "\n Integral Simpson: " << integrals << endl;
    cout << "\n Error Simpson: " << errors << endl;

    cout << "\n Integral MC average, rep = " << rep << ": " << sum/rep << endl;
    cout << "\n Error MC average, rep = " << rep << ": " << errorsum/rep << endl;

    cout << "\n Integral MC Von Neumann: " << integralmcvn << endl;
    cout << "\n Erro MC Von Neumann: " << errormcvn << endl;

    //Monte Carlo importance sampling

    function<double(double)> g1 = [](double x) {
        return sin(x);
    };

    Functor func1("cos x", g1);
    IntegDeriv g(func1);

    double errormcis = 1E-10;
    double errormcis1 = 1E-10;
    int nmcis = 10000;

    function<double(double)> px = [](double x) {
        return x;
    };

    function<double(double)> xy = [](double x) {
        return sqrt(2*x);
    };

    double integralmcis = g.IntegrateMCIS(0, sqrt(2), px, xy, errormcis, nmcis);
    double integralmcis1 = g.IntegrateMCISDistribution(0, sqrt(2), px, errormcis1, nmcis);

    cout << "\n Integral MC Importance Sampling: " << integralmcis << endl;
    cout << "\n Error: " << errormcis << endl;

    cout << "\n Integral MC Importance Sampling Dist: " << integralmcis1 << endl;
    cout << "\n Error: " << errormcis1 << endl;

    //Improper integrals

    function<double(double)> fi1 = [](double x) {
        return 1/(1+x*x);
    };

    function<double(double)> fi2 = [](double x) {
        return exp(-x);
    };

    function<double(double)> fi3 = [](double x) {
        return exp(x);
    };

    Functor funci1("1/(1+x²)", fi1);
    IntegDeriv deriv1(funci1);

    Functor funci2("exp(-x)", fi2);
    IntegDeriv deriv2(funci2);

    Functor funci3("exp(x)", fi3);
    IntegDeriv deriv3(funci3);

    int n = 1000000;

    double error1 = 1E-3;
    double integral1 = deriv1.ImproperIntegral(-5, 5, error1, n);

    double error2 = 1E-3;
    double integral2 = deriv2.ImproperIntegralRight(0, 1, error2, n);

    double error3 = 1E-3;
    double integral3 = deriv3.ImproperIntegralLeft(0, -1, error3, n);

    cout << "\n Integral of exp(-x²): " << integral1 << endl;
    cout << "\n Error: " << error1 << endl;

    cout << "\n Integral of exp(-x): " << integral2 << endl;
    cout << "\n Error: " << error2 << endl;

    cout << "\n Integral of exp(x): " << integral3 << endl;
    cout << "\n Error: " << error3 << endl;

    //func.Draw(0, 10, 1000, "x", "y");
}