#include "IntegDerivND.h"
#include <iostream>
#include <cmath>

using namespace std;

//Constructor
IntegDerivND::IntegDerivND(FunctorND &Fi) : F(Fi) {;}

//Monte Carlo multiple integral on an interval [x1i, x1f] x ... x [xni, xnf]
double IntegDerivND::IntegrateIntervalMC(std::vector<std::pair<double, double>> limits, double& Error, int& n) {
    if (limits.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    }
    
    double Integral = 0;
    Error = 0;
    double sum = 0.;
    double sum2 = 0.;
    double vol = 1.;
    vector<double> r;
    r.resize(limits.size());    

    //Calculate n-volume of paralelepiped
    for (int i = 0; i < limits.size(); i++) {
        vol *= (limits[i].second - limits[i].first);
        if (vol == 0) {
            Integral = 0;
            Error = 0;
            return Integral;
        }
    }

    FCrand integralMC(0);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < limits.size(); k++) {
            r[k] = integralMC.GetRandom(limits[k].first, limits[k].second);
        }
        sum += F(r);
        sum2 += F(r)*F(r);
    }        

    Integral = vol*sum/n;
    Error = sqrt(fabs(sum2/n -(sum/n)*(sum/n)))*vol/sqrt(n);

    return Integral;
} 

//Monte Carlo multiple integral on a general region with indicator function ind(x1, ..., xn) = 1 inside region and 0 outside region
double IntegDerivND::IntegrateRegionMC(std::function<int(std::vector<double>)> ind, std::vector<std::pair<double, double>> limits, double& Error, int& n) {
    if (limits.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    }
    
    double Integral = 0;
    Error = 0;
    double sum = 0.;
    double sum2 = 0.;
    double vol = 1.;
    vector<double> r;
    r.resize(limits.size());    

    //Calculate n-volume of paralelepiped
    for (int i = 0; i < limits.size(); i++) {
        vol *= (limits[i].second - limits[i].first);
        if (vol == 0) {
            Integral = 0;
            Error = 0;
            return Integral;
        }
    }

    FCrand integralMC(0);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < limits.size(); k++) {
            r[k] = integralMC.GetRandom(limits[k].first, limits[k].second);
        }
        sum += F(r)*ind(r);
        sum2 += F(r)*F(r)*ind(r)*ind(r);
    }        

    Integral = vol*sum/n;
    Error = sqrt(fabs(sum2/n -(sum/n)*(sum/n)))*vol/sqrt(n); 

    return Integral;
}

//First partial derivative - O(h²) - h = 1E-5
double IntegDerivND::D1backward(int i, double h, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    } else {
        vector<double> x1(x);
        vector<double> x2(x);
        x1[i-1] -= h;
        x2[i-1] -= 2*h;
        return (F(x2) - 4*F(x1) + 3*F(x)) / (2*h);
    }    
}

double IntegDerivND::D1central(int i, double h, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    } else {
        vector<double> x1(x);
        vector<double> x2(x);
        vector<double> x3(x);
        x1[i-1] += h;
        x2[i-1] -= h;
        
        return (F(x1)-F(x2))/(2*h);
    }  
}

double IntegDerivND::D1forward(int i, double h, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    } else {
        vector<double> x1(x);
        vector<double> x2(x);
        vector<double> x3(x);
        x1[i-1] += 2*h;
        x2[i-1] += h;
        return (-F(x1) + 4*F(x2) - 3*F(x3)) / (2*h);
    }   
}

//First partial derivative - O(h⁴) 
double IntegDerivND::D1fivepoint(int i, double h, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    } else {
        vector<double> x1(x);
        vector<double> x2(x);
        vector<double> x3(x);
        vector<double> x4(x);
        x1[i-1] -= 2*h;
        x2[i-1] -= h;
        x3[i-1] += 2*h;
        x4[i-1] += h;
        return (F(x1) - 8*F(x2) + 8*F(x4) - F(x3))/(12*h);
    }       
}

//Second partial derivative - O(h²) - h = 1E-4
double IntegDerivND::D2backward(int i, double h, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    } else {
        vector<double> x1(x);
        vector<double> x2(x);
        vector<double> x3(x);
        x1[i-1] -= h;
        x2[i-1] -= 2*h;
        x3[i-1] -= 3*h;
        return (2*F(x)-5*F(x1)+ 4*F(x2)-F(x3))/(h*h);
    }    
}

double IntegDerivND::D2forward(int i, double h, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    } else {
        vector<double> x1(x);
        vector<double> x2(x);
        vector<double> x3(x);
        vector<double> x4(x);
        x1[i-1] += 2*h;
        x2[i-1] += h;
        x4[i-1] += 3*h;
        return (2*F(x3)-5*F(x2)+4*F(x1)-F(x4))/(h*h);
    }   
}

double IntegDerivND::D2central(int i, double h, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    } else {
        vector<double> x1(x);
        vector<double> x2(x);
        vector<double> x3(x);
        x1[i-1] += h;
        x2[i-1] -= h;
        return (F(x1) - 2*F(x) + F(x2))/(h*h);
    }    
}

//Second partial derivative - O(h⁴)
double IntegDerivND::D2fivepoint(int i, double h, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    } else {
        vector<double> x1(x);
        vector<double> x2(x);
        vector<double> x3(x);
        vector<double> x4(x);
        x1[i-1] -= 2*h;
        x2[i-1] -= h;
        x3[i-1] += h;
        x4[i-1] += 2*h;  
        return (-F(x1) + 16*F(x2) - 30*F(x) + 16*F(x3) - F(x4))/(12*h*h);
    }  
}

//Second mixed partial derivative - O(h²)
double IntegDerivND::D2mixedcentral(int i, int j, double h1, double h2, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    } else {
        vector<double> x1(x);
        vector<double> x2(x);
        vector<double> x3(x);
        vector<double> x4(x);
        x1[i-1] += h1;
        x1[j-1] += h2;
        x2[i-1] -= h1; 
        x2[j-1] -= h2; 
        x3[i-1] += h1;
        x3[j-1] -= h2;
        x4[i-1] -= h1; 
        x4[j-1] += h2;
        return (F(x1) - F(x3) - F(x4) + F(x2))/(4*h1*h2);
    }  
}

//Second mixed partial derivative ∂²f/∂xi∂xj - O(h⁴)
double IntegDerivND::D2mixedfivepoint(int i, int j, double h1, double h2, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    } else {
        vector<double> x1(x);
        vector<double> x2(x);
        vector<double> x3(x);
        vector<double> x4(x);
        x1[i-1] += h1;
        x1[j-1] -= 2*h2;
        x2[i-1] += 2*h1; 
        x2[j-1] -= h2; 
        x3[i-1] -= 2*h1;
        x3[j-1] += h2;
        x4[i-1] -= h1; 
        x4[j-1] += 2*h2;

        vector<double> x5(x);
        vector<double> x6(x);
        vector<double> x7(x);
        vector<double> x8(x);
        x5[i-1] -= h1;
        x5[j-1] -= 2*h2;
        x6[i-1] -= 2*h1; 
        x6[j-1] -= h2; 
        x7[i-1] += h1;
        x7[j-1] += 2*h2;
        x8[i-1] += 2*h1; 
        x8[j-1] += h2;


        vector<double> x9(x);
        vector<double> x10(x);
        vector<double> x11(x);
        vector<double> x12(x);
        x9[i-1] += 2*h1;
        x9[j-1] -= 2*h2;
        x10[i-1] -= 2*h1; 
        x10[j-1] += 2*h2; 
        x11[i-1] -= 2*h1;
        x11[j-1] -= 2*h2;
        x12[i-1] += 2*h1; 
        x12[j-1] += 2*h2;



        vector<double> x13(x);
        vector<double> x14(x);
        vector<double> x15(x);
        vector<double> x16(x);
        x13[i-1] -= h1;
        x13[j-1] -= h2;
        x14[i-1] += h1; 
        x14[j-1] += h2; 
        x15[i-1] += h1;
        x15[j-1] -= h2;
        x16[i-1] -= h1; 
        x16[j-1] += h2;
        return (8*(F(x1) + F(x2) + F(x3) + F(x4))- 8*(F(x5) + F(x6) + F(x7) + F(x8)) - (F(x9) + F(x10) - F(x11) - F(x12))+ 64*(F(x13) + F(x14) - F(x15) - F(x16)))/(144*h1*h2);
    } 
}

//Gradient with central derivative
Eigen::VectorXd IntegDerivND::Gradient(double h, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    }  
    Eigen::VectorXd v;
    v.resize(F.GetDimension());
    for (int i = 0; i < v.size(); i++) {
        v[i] = D1central(i+1, h, x);
    }    
    return v;
}

//Hessian matrix with central second derivative
Eigen::MatrixXd IntegDerivND::Hessian(double h1, double h2, vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    }  
    Eigen::MatrixXd H;
    H.resize(F.GetDimension(), F.GetDimension());
    for (int i = 0; i < H.rows(); i++) {
        for (int j = 0; j < H.cols(); j++) {
            if (i == j) {
                H(i, j) = D2central(i+1, h1, x);
            } else {
                H(i, j) = D2mixedfivepoint(i+1, j+1, h1, h2, x);
            }
        }    
    }    
    return H;
}

//Laplacian with central second derivative
double IntegDerivND::Laplacian(double h, std::vector<double> x) {
    if (x.size() != F.GetDimension()) {
        cout << "\n Note that the function is " << F.GetDimension() << " dimensional." << endl;
        exit(0);
    } 
    double sum = 0.;
    for (int i = 0; i < x.size(); i++) {
        sum += D2central(i+1, h, x);
    }
    return sum;
}