#include "IntegDerivVF.h"
#include <iostream>
#include <cmath>

using namespace std;

//Constructor
IntegDerivVF::IntegDerivVF(VectorField &Fi) : F(Fi) {;}

//Jacobian matrix with central derivative
Eigen::MatrixXd IntegDerivVF::JacobianMatrix(double h, std::vector<double> x) {
    int N = F.GetDimension();

    if (x.size() != N) {
        cout << "\n Note that the vector field is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    }  
    Eigen::MatrixXd J(N, N);
    for (int i = 0; i < N; i++) {
        IntegDerivND* fi = new IntegDerivND(F[i]);
        for (int j = 0; j < N; j++) {
            J(i, j) = fi->D1central(j+1, h, x);
        }    
        delete fi;
    }    
    return J;
}

//Divergence with central derivative
double IntegDerivVF::Divergence(double h, std::vector<double> x) {
    int N = F.GetDimension();

    if (x.size() != N) {
        cout << "\n Note that the vector field is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    }  
    double sum = 0.;
    for (int i = 0; i < N; i++) {
        IntegDerivND* fi = new IntegDerivND(F[i]);
        sum += fi->D1central(i+1, h, x);  
        delete fi;
    }    
    return sum;
}

//Curl with central derivative, only for 2 and 3 dimensions
Eigen::VectorXd IntegDerivVF::Curl(double h, std::vector<double> x) {
    int N = F.GetDimension();

    if (x.size() != N) {
        cout << "\n Note that the vector field is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    }  

    if (N == 2) {
        Eigen::VectorXd v(N);
        IntegDerivND* f1 = new IntegDerivND(F[0]);
        IntegDerivND* f2 = new IntegDerivND(F[1]);

        v[0] = f1->D1central(2, h, x);
        v[1] = f2->D1central(1, h, x);
            
        delete f1;
        delete f2;
        return v;
    } else if (N == 3) {
        Eigen::VectorXd v(N);
        IntegDerivND* f1 = new IntegDerivND(F[0]);
        IntegDerivND* f2 = new IntegDerivND(F[1]);
        IntegDerivND* f3 = new IntegDerivND(F[2]);

        v[0] = f3->D1central(2, h, x) - f2->D1central(3, h, x);
        v[1] = f1->D1central(3, h, x) - f3->D1central(1, h, x);
        v[2] = f2->D1central(1, h, x) - f1->D1central(2, h, x);
            
        delete f1;
        delete f2;
        delete f3;
        return v;

    } else {
        cout << "\n Note that curl is only defined for 2 and 3 dimensional vector fields." << endl;
        exit (0);
    }
}

//Laplacian with central derivative
Eigen::VectorXd IntegDerivVF::Laplacian(double h, std::vector<double> x) {
    int N = F.GetDimension();

    if (x.size() != N) {
        cout << "\n Note that the vector field is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    }  
    double sum = 0.;
    Eigen::VectorXd v(N);
    for (int i = 0; i < N; i++) {
        IntegDerivND* fi = new IntegDerivND(F[i]);
        v[i] = fi->Laplacian(h, x);  
        delete fi;
    }    
    return v;
}