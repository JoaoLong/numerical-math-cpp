#include "RootFinderND.h"
#include <iostream>

using namespace std;

//Test main of class RootFinderND

int main() {

    vector<function<double(vector<double>)>> fi(2);
    fi[0] = [](vector<double> x) {  // x³ + y - 1
        return x[0]*x[0]*x[0] + x[1] - 1;
    };

    fi[1] = [](vector<double> x) { // y³ - x + 1
        return x[1]*x[1]*x[1] - x[0] + 1;
    };

    vector<vector<function<double(vector<double>)>>> gi(2);
    for (int i = 0; i < 2; i++) {
        gi[i].resize(2);
    }    
    gi[0][0] = [](vector<double> x) {  // 3x²
        return 3*x[0]*x[0];
    };

    gi[0][1] = [](vector<double> x) { // 1
        return 1;
    };

    gi[1][0] = [](vector<double> x) {  // -1
        return -1;
    };

    gi[1][1] = [](vector<double> x) { // 3y²
        return 3*x[1]*x[1];
    };

    vector<FunctorND> func(fi.size());
    for (int i = 0; i < fi.size(); i++) {
        string s = "f" + to_string(i);
        func[i] = FunctorND(&s[0], 2, fi[i]);
    }
 
    RootFinderND root(func);

    vector <double> x = root.NewtonNDNumerical({1, 1}, 1E-5);

    cout << "Newton Numerical: \n";
    for (int i = 0; i < fi.size(); ++i){
        cout << "x[" << i << "] = " << x[i] << endl;       
    }
    cout << "\n\n";
    vector <double> y = root.NewtonND({1, 1}, 1E-5, gi);

    cout << "Newton Analytic: \n";
    for (int i = 0; i < fi.size(); ++i){
        cout << "x[" << i << "] = " << y[i] << endl;       
    }
}
