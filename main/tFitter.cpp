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
    double xi = 0;
    double xf = 3;

    //0 - 1/sqrt(2pi sigma), 1 - media, 2 - sigma
    TF1* f1 = new TF1("f1", "[0] + [1]*x", 0.2, 2.8);

    vector<TF1*> fi;
    fi.resize(1);
    fi[0] = f1;
    
    //SetParameter(nº parameter, valor)
    /* f1->SetParameter(0, 2.5);
    f1->SetParameter(1, 1.5); */

    //SetParLimits(nº parameter, minimum value, maximum value)
    /* f1->SetParLimits(0, 2, 3);
    f1->SetParLimits(1, 1, 2); */

    //FixParameter(nº parameter, value)
    /*f1->FixParameter(0, 2.5);*/

    Fitter fitlinear(v, e, fi);
    //Fitter fitlinear(s, fi);

    //fitlinear.SetFitFunction(fi);

    fitlinear.Print("m", "kg");
    fitlinear.Fit();
    

    //GetParameter(nº parameter)
    double a = f1->GetParameter(0);
    double b = f1->GetParameter(1);
    
    cout << a << endl;
    cout << b << endl;

    fitlinear.DrawFit(xi, xf, 0, 5, "Linear fit", "x", "y");

    return 0;
}