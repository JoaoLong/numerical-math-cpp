#include "VectorField.h"
#include <iostream>

using namespace std;

//Test main of class VectorField

int main() {
    
    vector<function<double(vector<double>)>> fi(3);
    fi[0] = [](vector<double> x) {  // x² + y² - z²
        return x[0]*x[0] + x[1]*x[1] - x[2]*x[2];
    };

    fi[1] = [](vector<double> x) { // // x² - y² + z²
        return x[0]*x[0] - x[1]*x[1] + x[2]*x[2];
    };

    fi[2] = [](vector<double> x) { // // x² - y² - z²
        return x[0]*x[0] - x[1]*x[1] - x[2]*x[2];
    };

    vector<FunctorND> func(fi.size());
    for (int i = 0; i < fi.size(); i++) {
        string s = "f" + to_string(i);
        func[i] = FunctorND(&s[0], 3, fi[i]);
    }
 
    VectorField vec(func);

    cout << "f(1, 2, 1) = (";
    for (int i = 0; i < vec.GetDimension(); i++) {
        cout << vec({1, 2, 1})[i] << ", ";
    }
    cout << ")" << endl;

    cout << "f(0, 4, 1) = (";
    for (int i = 0; i < vec.GetDimension(); i++) {
        cout << vec({0, 4, 1})[i] << ", ";
    }
    cout << ")" << endl;

    //TO IMPLEMENT
    //func.Draw(-10, 10, -10, 10, 100, 100, "x", "y", "z");
    return 0;
}