#include "Fitter.h"
#include <iostream>

using namespace std;

//Test main of class Fitter

int main() {
    //Points and errors
    vector<pair<double, double>> ref = {{0.6867, 2.40735}, {0.5893, 2.41734},{0.5270, 2.42694},{0.3968, 2.46476}};
    vector<pair<double, double>> v = {{0.5, 0.47}, {1.2, 1.23},{1.8, 1.84},{2.3, 2.47}};
    vector<pair<double, double>> e = {{0.02, 0.02}, {0.02, 0.02},{0.02, 0.02},{0.02, 0.02}};

    //string s = "pointsfitter.txt";

    //Set fitting function with parameters [0], [1], etc
    TF1 *f1 = new TF1("f1","[0]*x + [1]", 0, 800);
    
    //SetParameter(nº parameter, valor)
    /* f1->SetParameter(0, 2.5);
    f1->SetParameter(1, 1.5); */
    
    //SetParLimits(nº parameter, minimum value, maximum value)
    /* f1->SetParLimits(0, 2, 3);
    f1->SetParLimits(1, 1, 2); */

    Fitter fitlinear(v, e, f1);
    //Fitter fitlinear(s, f1);

    //fitlinear.SetFitFunction(f1);

    fitlinear.Print();
    fitlinear.DrawFit();

    return 0;
}