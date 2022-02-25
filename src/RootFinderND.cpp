#include "RootFinderND.h"
#include <iostream>

using namespace std;

// Constructor
RootFinderND::RootFinderND(std::vector<FunctorND>& Fi) : F(Fi) {
    if (F.size() != F[0].GetDimension()) {
        cout << "\n The number of equations and variables is different, the system will be impossible or indeterminate." << endl;
        exit(0);
    }
}

//Newton method with analytic jacobian matrix
vector<double> RootFinderND::NewtonND(vector<double> x0, double error, std::vector<std::vector<std::function<double(std::vector<double>)>>> J) {
    int n = F.size();
    std::vector<double> xf = x0;
    std::vector<double> xi = xf;
    int i = 1;  
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> D(n, n);
    Eigen::Matrix<double, Eigen::Dynamic, 1> Fxi(n, 1);
    Eigen::Matrix<double, Eigen::Dynamic, 1> sol(n, 1);

    double sum;

    do {
        sum = 0.;
        xi = xf;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                D(i, j) = J[i][j](xi);
            }
            Fxi[i] = -F[i](xi);
        }

        EqSolver * eq = new EqSolver(D, Fxi);
        sol = eq->GaussSolver(true);

        for (int r = 0; r < n; ++r) {
            xf[r] = xi[r] + sol[r]; 
            sum += (xf[r] -xi[r])*(xf[r]-xi[r]);
        }
        delete eq;
        i++;
    } while (sqrt(sum) > error);  

    cout << "Newton ND Analytic iterations: " << i << endl;
    return xf;
}

//Newton method with numerical jacobian matrix
vector<double> RootFinderND::NewtonNDNumerical(vector<double> x0, double error) {
    
    int n = F.size();
    std::vector<double> xf = x0;
    std::vector<double> xi = xf;
    int i = 1;  
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> J(n, n);
    Eigen::Matrix<double, Eigen::Dynamic, 1> Fxi(n, 1);
    Eigen::Matrix<double, Eigen::Dynamic, 1> sol(n, 1);

    double sum;

    do {
        sum = 0.;
        xi = xf;
        for (int i = 0; i < n; i++) {
            IntegDerivND* a = new IntegDerivND(F[i]);
            for (int j = 0; j < n; j++) {
                J(i, j) = a->D1central(j+1, 1E-5, xi);
            }
            Fxi[i] = -F[i](xi);
            delete a;
        }


        EqSolver* eq = new EqSolver(J, Fxi);
        sol = eq->GaussSolver(true);

        for (int r = 0; r < n; ++r) {
            xf[r] = xi[r] + sol[r]; 
            sum += (xf[r] -xi[r])*(xf[r]-xi[r]);
        }
        delete eq;
        i++;
    } while (sqrt(sum) > error);  
    
    cout << "Newton ND Numerical iterations: " << i << endl;
    return xf;
} 