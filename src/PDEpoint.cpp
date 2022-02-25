#include "PDEpoint.h"

using namespace std;

//Constructor with vector of x
PDEpoint::PDEpoint(const std::vector<double> &xi, double yi) : y(yi) {
    x.resize(xi.size());
    copy(xi.begin(), xi.end(), x.begin());
    dim = x.size();
}

//Setter for x and y
void PDEpoint::SetPDEpoint(std::vector<double>& xi, double yi) {
    y = yi;
    x.resize(xi.size());
    copy(xi.begin(), xi.end(), x.begin());
    dim = x.size();
}

//Accessor to x
std::vector<double>& PDEpoint::X() { 
    return x;
} 

//Accessor to y
double& PDEpoint::Y() { 
    return y;
} 

//Write independent variables xi and dependent variable y
std::ostream& operator<< (std::ostream& s, const PDEpoint& P) {
    int n = P.x.size();

    s << "Independent variables: \n" << endl; 
    for (int i = 0; i < n; i++) {
        s << "x[" << i << "] = " << P.x[i] << "\n" << endl;
    }    
    s << "Dependent variable: \n" << endl;
    s << "y = " << P.y << "\n" << endl;

    return s;
}  