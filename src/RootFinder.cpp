#include "RootFinder.h"
#include <iostream>

using namespace std;

// Constructor
RootFinder::RootFinder(Functor &Fi) : F(Fi) { ; }

// Bisection method
double RootFinder::BisectionMethod(double& a, double& b, double error) {
    double xl, x0, xr;
    double fa = F(a);
    double fb = F(b);

    if (fa * fb > 0.0) {
        cout << "\n There are no zeros on the initial interval." << endl;
        exit(0);
    }    
    
    xl = a;
    xr = b;
    int i = 1;
    while (fabs(xr - xl) >= error) {
        double fl = F(xl);
        double fr = F(xr);
        x0 = (xr + xl) / 2.0;
        double f0 = F(x0);
        if ((fl * f0) <= 0.0) {
            xr = x0;
        } else {
            xl = x0;
        }  
        i++;  
    }
    
    a = xl;
    b = xr;
    cout << a << endl << b << endl;
    cout << "Bisection iterations: " << i << endl;
    return x0;
}

// Regula falsi
double RootFinder::RegulaFalsi(double& a, double& b, double error) {
    double xl, x0, xr;
    double fa = F(a);
    double fb = F(b);
    if (fa * fb > 0.0) {
        cout << "\n There are no zeros on the initial interval." << endl;
        exit(0);
    }    
    
    xl = a;
    xr = b;
    x0 = xl;

    int i = 1;
    while (fabs(xr - xl) >= error) {
        double fl = F(xl);
        double fr = F(xr);
        x0 = xl - (xr-xl)*fl/(fr-fl);  
        
        double f0 = F(x0);

        if ((f0 * fr) == 0.0) {
            a = xl;
            b = xr;
            return x0;
        } else if (f0 * fr < 0.0) {    
            xl = x0;
            
        } else {
            xr = x0;
        }
        i++;
    }
    a = xl;
    b = xr;
    cout << "Regula Falsi iterations: " << i << endl;
    return x0;
}

// Newton method with analytic derivative
double RootFinder::NewtonRaphson(double x0, double error, std::function<double(double)> deriv) {
    double xf = x0;
    double xi = xf;
    int i = 1;

    do {
        xi = xf;
        xf -= F(xi)/deriv(xi);
        i++;
    } while (fabs(xf-xi) >= error);

    cout << "Newton-Raphson iterations: " << i << endl;
    return xf;
}

// Newton method with numerical derivative
double RootFinder::NewtonNumerical(double x0, double error) {
    double xf = x0;
    double xi = xf;

    int i = 1;
    IntegDeriv* deriv = new IntegDeriv(F);
    do {
        xi = xf;
        xf -= F(xi)/deriv->D1central(1E-5, xi);
        i++;
    } while (fabs(xf-xi) >= error);
    delete deriv;

    cout << "Newton Numerical iterations: " << i << endl;
    return xf;
}

// Secant method
double RootFinder::SecantMethod(double a, double b, double error){
    vector <double> x = {a, b, 0};
    int i = 1;
    double e = 1.;

    do {
        x[2] = x[1] - F(x[1])*(x[1]-x[0])/(F(x[1])-F(x[0]));
        e = fabs(x[2]-x[1]);
        x[0] = x[1];
        x[1] = x[2];
        i++;
    } while (e >= error);

    cout << "Secant iterations: " << i << endl;
    return x[2];
}