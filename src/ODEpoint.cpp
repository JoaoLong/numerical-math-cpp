#include "ODEpoint.h"

using namespace std;

//Constructor with Xvar object
ODEpoint::ODEpoint(double ti, Xvar ai) : t(ti), Xvar(ai) { ; }

//Constructor with vector of x
ODEpoint::ODEpoint(double ti, const std::vector<double> &v) : t(ti), Xvar(v) { ; }

//Constructor with initializer list of x
ODEpoint::ODEpoint(double ti, const std::initializer_list<double> &v) : t(ti), Xvar(v) { ; }

//Setter with Xvar object
void ODEpoint::SetODEpoint(double ti, Xvar &P) {
    t = ti;
    x.resize(P.X().size());
    copy(P.X().begin(), P.X().end(), x.begin());
}

//Setter with initializer list of x
void ODEpoint::SetODEpoint(double ti, const std::initializer_list<double> &v) {
    t = ti;
    x.resize(v.size());
    copy(v.begin(), v.end(), x.begin());
}

//Setter with vector of x
void ODEpoint::SetODEpoint(double ti, std::vector<double> v) {
    t = ti;
    x.resize(v.size());
    copy(v.begin(), v.end(), x.begin());
}

//Accessor to time
double& ODEpoint::T() { 
    return t;
} 

//Write independent variable t and dependent variables xi
std::ostream& operator<< (std::ostream& s, const ODEpoint& P) {
    int n = P.x.size();
    s << "Independent variable: \n" << endl;
    s << "t = " << P.t << "\n" << endl;
    s << "Dependent variables: \n" << endl; 
    for (int i = 0; i < n; i++) {
        s << "x[" << i << "] = " << P.x[i] << "\n" << endl;
    }    
    return s;
}  