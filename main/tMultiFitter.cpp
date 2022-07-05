#include "MultiFitter.h"
#include <iostream>

using namespace std;

//Test main of class MultiFitter

int main() {
    //Points and errors
    vector<pair<double, double>> v = {{0.5, 0.47}, {1.2, 1.23},{1.8, 1.84},{2.3, 2.47}};
    vector<pair<double, double>> e = {{0.02, 0.02}, {0.02, 0.02},{0.02, 0.02},{0.02, 0.02}};

    vector<pair<double, double>> v1 = {{0.6, 1.57}, {1.25, 2.2},{2, 3.05},{2.6, 3.55}};
    vector<pair<double, double>> e1 = {{0.02, 0.02}, {0.02, 0.02},{0.02, 0.02},{0.02, 0.02}};

    double xi = 0;
    double xf = 3;

    TF1* f1 = new TF1("f1", "[0] + [1]*x", 0.2, 2.8);
    TF1* f2 = new TF1("f2", "[0] + [1]*x", 0.2, 2.8);

    //Recommended that you keep all the functions that fit the same graph of the same color to avoid confusion
    f1->SetLineColor(kRed);
    f2->SetLineColor(kBlue);

    vector<TF1*> fi;
    fi.resize(1);
    fi[0] = f1;

    vector<TF1*> gi;
    gi.resize(1);
    gi[0] = f2;
    
    //SetParameter(nº parameter, valor)
    /* f1->SetParameter(0, 2.5);
    f1->SetParameter(1, 1.5); */

    //SetParLimits(nº parameter, minimum value, maximum value)
    /* f1->SetParLimits(0, 2, 3);
    f1->SetParLimits(1, 1, 2); */

    //FixParameter(nº parameter, value)
    /*f1->FixParameter(0, 2.5);*/

    Fitter fitlinear(v, e, fi);
    Fitter fitlinear1(v1, e1, gi);

    vector<Fitter> fit(2);
    fit[0] = fitlinear;
    fit[1] = fitlinear1;
 
    MultiFitter multifit(fit);    

    //MUITOS FITS, PORQUÊ?

    multifit.Print("m", "kg");
    //multifit.Fit();
    //multifit.DrawPoints(xi, xf, 0, 5, "Linear fit", "x", "y");
    multifit.DrawFit(xi, xf, 0, 5, "Linear fit", "x", "y");

    return 0;
}