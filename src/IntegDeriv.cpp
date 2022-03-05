#include "IntegDeriv.h"
#include <iostream>
#include <cmath>

using namespace std;

IntegDeriv::IntegDeriv(Functor& Fi) : F(Fi) {;}

//Trapezoidal rule with 2^n partitions depending on given error
double IntegDeriv::TrapezoidalRule(double xi, double xf, double& Error) {

    double Integral = 0.;
    double error_aux = Error+1;
    double sum = 0.;
    double eps = 0.01;
    double max_d2 = fabs(D2forward(eps, xi));
    double x = 0.;
    int k = 2;
    int n = 0;

    if (xi == xf) {
        Integral = 0;
        Error = 0;
        return Integral;
    }

    for (int j = 0; j < (xf-xi)/eps; j++) {
        if (fabs(D2forward(eps, xi+(j+1)*eps)) > max_d2) {
            max_d2 = fabs(D2forward(eps, xi+(j+1)*eps));
            x = xi+(j+1)*eps;
        }
    }

    do {
        Integral = 0;
        n = pow(2, k-1);
        double h = fabs((xf - xi) / n);
        sum = 0.;
        
        for (int i = 0; i < n; i++) {
            Integral += (h/2)*(F(xi+i*h) + F(xi+(i+1)*h));
        }

        error_aux = max_d2*h*h*(xf-xi)/12;
        k++;
    } while (error_aux > Error);

    cout << "Trapezoidal rule partitions: " << n << endl;
    Error = error_aux;

    return Integral;
}    

//Simpson rule with 2^n partitions depending on given error
double IntegDeriv::SimpsonRule(double xi, double xf, double& Error) {

    double Integral = 0.;
    double error_aux = 0.;
    double eps = 1E-4;
    double x = 0.;
    double max_d4 = fabs(D4forward(3E-3, xi));
    int n = 1;
    int c;
    double h = (xf - xi) / n;

    if (xi == xf) {
        Integral = 0;
        Error = 0;
        return Integral;
    }

    for (int j = 0; j < (xf-xi)/eps; j++) {
        if (fabs(D4forward(3E-3, xi+(j+1)*eps)) > max_d4) {
            max_d4 = fabs(D4forward(3E-3, xi+(j+1)*eps));
            x = xi+(j+1)*eps;
        }
    }

    do {
        Integral = 0.;
        error_aux = 0.;
        double h = fabs((xf - xi) / n);
        if (n % 2 == 0) {
            c = 0;
        } else if (n % 2 == 1) {
            c = 1;
        }    

        Integral += F(xi);
        for (int i = 1; i < n-c; i++) {
            if (i % 2 == 0) {
                Integral += 2*F(xi + i*h);
            } else if (i % 2 == 1) {
                Integral += 4*F(xi + i*h);
            }
        }
        Integral += F(xf);
        Integral *= (h/3);

        if (c == 1) {
            Integral += (h/12)*(-F(xf-2*h)+8*F(xf-h)+5*F(xf));
        }

        error_aux = max_d4*h*h*h*h*(xf-xi)/180;
        n++;
    } while (error_aux > Error);  

    cout << "Simpson rule partitions: " << n << endl;
    Error = error_aux;
    
    return Integral;
}

//Improper integral from -infinity to xf with breaking point a
double IntegDeriv::ImproperIntegralLeft(double xf, double a, double& Error, int n) {
    
    if (a == 0) {
        cout << "\n The breaking point cannot be zero." << endl;
        exit(0);
    }

    if (a >= xf) {
        cout << "\n The breaking point must be left of the endpoint." << endl;
        exit(0);
    }

    double errormiddle = Error;
    double errorleft = Error;
    double middle = SimpsonRule(a, xf, errormiddle);
    
    function<double(double)> f1 = [this](double x) {
        return F(1/x)/(x*x);
    };

    Functor* func = new Functor("f(1/x)/x²", f1);
    IntegDeriv* deriv = new IntegDeriv(*func);
    
    double left = deriv->IntegrateMC(1/a, 0, errorleft, n);

    if (a > 0) {
        left -= left;
    }

    Error = errormiddle + errorleft;
    return (middle + left);
}

//Improper integral from xi to +infinity with breaking point a
double IntegDeriv::ImproperIntegralRight(double xi, double b, double& Error, int n) {
   if (b == 0) {
        cout << "\n The breaking point cannot be zero." << endl;
        exit(0);
    }

    if (b <= xi) {
        cout << "\n The breaking point must be right of the endpoint." << endl;
        exit(0);
    }

    double errormiddle = Error;
    double errorright = Error;
    double middle = SimpsonRule(xi, b, errormiddle);
    
    function<double(double)> f1 = [this](double x) {
        return F(1/x)/(x*x);
    };

    Functor* func = new Functor("f(1/x)/x²", f1);
    IntegDeriv* deriv = new IntegDeriv(*func);
    
    double right = deriv->IntegrateMC(0, 1/b, errorright, n);

    if (b < 0) {
        right -= right;
    }

    Error = errormiddle + errorright;
    return (middle + right);
}

//Improper integral from -infinity to +infinity with breaking points a, b
double IntegDeriv::ImproperIntegral(double a, double b, double& Error, int n) {

    if (a*b >= 0) {
        cout << "\n The breaking points must have different signs." << endl;
        return 0;
    }

    double errormiddle = Error;
    double errorleft = Error;
    double errorright = Error;
    
    double middle = SimpsonRule(a, b, errormiddle);
    
    function<double(double)> f1 = [this](double x) {
        return F(1/x)/(x*x);
    };

    Functor* func = new Functor("f(1/x)/x²", f1);
    IntegDeriv* deriv = new IntegDeriv(*func);
    
    double left = deriv->IntegrateMC(1/a, 0, errorleft, n);
    double right = deriv->IntegrateMC(0, 1/b, errorright, n);

    Error = errormiddle + errorright + errorleft;
    return (middle + left + right);

}

//Monte Carlo integration
double IntegDeriv::IntegrateMC(double xi, double xf, double& Error, int n) {
    double Integral = 0;
    Error = 0;
    double sum = 0.;
    double sum2 = 0.;

    if (xi == xf) {
        Integral = 0;
        Error = 0;
        return Integral;
    }
    
    FCrand integralMC(0);
    for (int i = 0; i < n; i++) {
        double r = integralMC.GetRandom(xi, xf);
        sum += F(r);
        sum2 += F(r)*F(r);
    }

    Integral = (xf-xi)*sum/n;
    Error = sqrt(fabs(sum2/n -(sum/n)*(sum/n)))*(xf-xi)/sqrt(n);

    return Integral;
} 

//Analytical Monte Carlo importance sampling
double IntegDeriv::IntegrateMCIS(double xi, double xf, std::function<double(double)> px, std::function<double(double)> xy,
                                double& Error, int n) {
    
    double Integral = 0;
    Error = 0;
    double sum = 0.;
    double sum2 = 0.;

    if (xi == xf) {
        Integral = 0;
        Error = 0;
        return Integral;
    }
    
    FCrand integralMC(time(0));
    for (int i = 0; i < n; i++) {
        double r = integralMC.GetRandom();
        sum += F(xy(r))/px(xy(r));
        sum2 += (F(xy(r))/px(xy(r)))*(F(xy(r))/px(xy(r)));
    }

    Integral = sum/n;
    Error = sqrt(fabs(sum2/n -(sum/n)*(sum/n)))/sqrt(n);

    return Integral;
} 

//Monte Carlo importance sampling with random numbers generated directly from distribution 
double IntegDeriv::IntegrateMCISDistribution(double xi, double xf, std::function<double(double)> px, double& Error, int n) {
    double Integral = 0;
    Error = 0;
    double sum = 0.;
    double sum2 = 0.;

    if (xi == xf) {
        Integral = 0;
        Error = 0;
        return Integral;
    }
    
    Functor h("k", px);
    IntegDeriv* H = new IntegDeriv(h);
    double errork = 1E-10;
    double k = H->SimpsonRule(xi, xf, errork);
    delete H;

    FCrand integralMC(time(0));
    for (int i = 0; i < n; i++) {
        double r = integralMC.GetRandomDistribution(xi, xf, px);
        sum += k*F(r)/px(r);
        sum2 += (k*F(r)/px(r))*(k*F(r)/px(r));
    }

    Integral = sum/n;
    Error = sqrt(fabs(sum2/n -(sum/n)*(sum/n)))/sqrt(n);

    return Integral;
}

//Monte Carlo von Neumann (acceptance-rejection)
double IntegDeriv::IntegrateMCVN(double xi, double xf, double& Error, int n) {
    double Integral = 0;
    Error = 0;
    double fmax = F(xi);
    double eps = 0.01;

    if (xi == xf) {
        Integral = 0;
        Error = 0;
        return Integral;
    }

    for (int j = 0; j < (xf-xi)/eps; j++) {
        if (F(xi+(j+1)*eps) > fmax) {
            fmax = F(xi+(j+1)*eps);
        }  
    }

    if (fmax <= 0) {
        cout << "\n MC Von Neumann integration does not work, the function has to be positive." << endl;
        Integral = NAN;
        Error = NAN;
        return Integral;
    }

    double A = (xf-xi)*fmax;
    double count = 0.;

    FCrand integralMC(time(0));

    for (int i = 0; i < n; i++) {
        double x = integralMC.GetRandom(xi, xf);
        double f = integralMC.GetRandom(0, fmax);
        if (f <= F(x)) {
            count += 1;
        }
    }

    Integral = (xf-xi)*fmax*count/n;
    Error = (xf-xi)*fmax*sqrt(count*(1-count/n))/n;

    return Integral;
}

//First derivative O(h²) - h = 1E-5
double IntegDeriv::D1backward(double h, double x) {
    return (F(x-2*h) - 4*F(x-h) + 3*F(x)) / (2*h);
}

double IntegDeriv::D1central(double h, double x) {
    return (F(x+h)-F(x-h))/(2*h);
}

double IntegDeriv::D1forward(double h, double x) {
    return (-F(x+2*h) + 4*F(x+h) - 3*F(x)) / (2*h);
}

//First derivative O(h⁴)
double IntegDeriv::D1fivepoint(double h, double x) {
    return (F(x-2*h) - 8*F(x-h) + 8*F(x+h) - F(x+2*h))/(12*h);
}

//Second derivative O(h²) - h = 1E-4
double IntegDeriv::D2backward(double h, double x) {
    return (2*F(x)-5*F(x-h)+ 4*F(x-2*h)-F(x-3*h))/(h*h);
}

double IntegDeriv::D2forward(double h, double x) {
    return (2*F(x)-5*F(x+h)+4*F(x+2*h)-F(x+3*h))/(h*h);
}

double IntegDeriv::D2central(double h, double x) {
    return (F(x+h) - 2*F(x) + F(x-h))/(h*h);
}

//Second derivative O(h⁴)
double IntegDeriv::D2fivepoint(double h, double x) {
    return (-F(x-2*h) + 16*F(x-h) - 30*F(x) + 16*F(x+h) - F(x+2*h))/(12*h*h);
}

//Third derivative - O(h²) - h = 7E-3
double IntegDeriv::D3backward(double h, double x){
    return ((5*F(x)-18*F(x-h)+ 24*F(x-2*h)-14*F(x-3*h)+ 3*F(x-4*h))/(2*h*h*h));
}

double IntegDeriv::D3forward(double h, double x){
    return ((-3*F(x+4*h)+14*F(x+3*h)- 24*F(x+2*h)+18*F(x+h)- 5*F(x))/(2*h*h*h));
}

double IntegDeriv::D3central(double h, double x){
    return (F(x+2*h)-2*F(x+h)+ 2*F(x-h)-F(x-2*h))/(2*h*h*h);
}

//Third derivative O(h⁴)
double IntegDeriv::D3fivepoint(double h, double x){
    return (-F(x+3*h) + 8*F(x+2*h)-13*F(x+h)+ 13*F(x-h)-8*F(x-2*h) + F(x-3*h))/(8*h*h*h);
}

//Fourth derivative O(h²) - h = 3E-3
double IntegDeriv::D4backward(double h, double x) {
    return (3*F(x) - 14*F(x-h) + 26*F(x-2*h) - 24*F(x-3*h) + 11*F(x-4*h) - 2*F(x-5*h))/(h*h*h*h);
}

double IntegDeriv::D4forward(double h, double x) {
    return (-2*F(x+5*h)+11*F(x+4*h)-24*F(x+3*h)+26*F(x+2*h)-14*F(x+h)+3*F(x))/(h*h*h*h);
}

double IntegDeriv::D4central(double h, double x) {
    return (F(x-2*h) - 4*F(x-h) + 6*F(x) - 4*F(x+h) + F(x+2*h))/(h*h*h*h);
}

//Fourth derivative O(h⁴)
double IntegDeriv::D4fivepoint(double h, double x) {
    return (-F(x-3*h) + 12*F(x-2*h) - 39*F(x-h) + 56*F(x) -F(x+3*h) + 12*F(x+2*h) - 39*F(x+h))/(6*h*h*h*h);
}

//Nth derivative with central finite difference
double IntegDeriv::Dncentral(int n, double h, double x) {
    
	double parcela = 0;
	double result = 0;

    /* if (n <= 4) {
        cout << "\n Note that there are functions defined for derivatives of order 4 or less." << endl;
    } */

    function<int(int, int)> nCr = [&nCr](int n, int k) {
        if (k > n) {
            return 0;
        }    
        if (k == 0 || k == n) {
            return 1;
        }
        return nCr(n - 1, k - 1) + nCr(n - 1, k);
    };

	h = pow(1e-10, 1/(double)n);

	for (int i = 0; i < n+1; i++){
		parcela = nCr(n,i)*F(x+(n/2-i)*h);
		if (i % 2 != 0) { 
            parcela = -parcela;
        }    
		result += parcela;
	}

	return result/pow(h,n);
}