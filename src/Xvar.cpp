#include "Xvar.h"

using namespace std;

//Constructor with dimension of vector
Xvar::Xvar(int n) {
    x.resize(n);
} 

//Constructor with vector of x
Xvar::Xvar(std::vector<double> a) {
    x.resize(a.size());
    copy(a.begin(), a.end(), x.begin());
} 

//Constructor with initializer list of x
Xvar::Xvar(const std::initializer_list<double>& v) {
    x.resize(v.size());
    copy(v.begin(), v.end(), x.begin());
}

//Copy constructor
Xvar::Xvar(const Xvar& P) {
    x.resize(P.x.size());
    copy(P.x.begin(), P.x.end(), x.begin());
}

//Assignment operator X=P ; x[i] = p[i]
Xvar& Xvar::operator=(const Xvar &P) {
    int n = P.x.size();
    
    for (int i = 0; i < n; i++){
        this->x[i] = P.x[i];
    }
    return *this;
}

//Sum operator X+P ; x[i] + p[i]
Xvar Xvar::operator+(const Xvar&P) {
    int n = P.x.size();
    for (int i = 0; i < n; i++){
        this->x[i] += P.x[i];
    }
    return *this;
} 

//Access ith component of vector X[i] ; x[i]
double& Xvar::operator[](int i) {
    return x[i];
} 

//Multiplication with scalar X*a ; a*x[i]
Xvar operator*(double a, const Xvar& P) {
    int n = P.x.size();
    vector <double> y;
    y.resize(n);
    for (int i = 0; i < n; i++){
        y[i] = P.x[i]*a;
    }
    return Xvar(y);
} 

//Write dependent variables xi
std::ostream& operator<< (std::ostream& s, const Xvar& P){
    int n = P.x.size();
    s << "Number of points: " << P.x.size() << endl;
    s << "Values: \n" << endl; 
    for (int i = 0; i < n; i++) {
        s << "x = " << P.x[i] << "\n" << endl;
    }    
    return s;
}

//Getter for dimension
std::vector<double>& Xvar::X() { 
    return x;
} 