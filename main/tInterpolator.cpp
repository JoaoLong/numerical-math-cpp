#include "Interpolator.h"
#include <iostream>

using namespace std;

//Test main of class Interpolator

int main() {
    //C array
    
    double time[12]={0.71, 1.51, 2.31, 3.11, 3.91, 4.71, 5.51, 6.31, 7.11, 7.91, 8.71, 9.51};
    double theta[12]={0.806, -0.702, -1.395, -0.608, 0.889, 1.371, 0.391, -1.051, -1.314, -0.162, 1.183, 1.225};
    Interpolator pendulum(12, time, theta);

    /*
    //Two vectors
    vector <double> time = {9.51, 1.51, 2.31, 3.11, 3.91, 4.71, 5.51, 6.31, 7.11, 7.91, 8.71, 0.71};
    vector <double> theta = {0.806, -0.702, -1.395, -0.608, 0.889, 1.371, 0.391, -1.051, -1.314, -0.162, 1.183, 1.225};
    Interpolator pendulum(time, theta);
    */

    /*
    //Vector of pairs
    double time[12]={0.71, 1.51, 2.31, 3.11, 3.91, 4.71, 5.51, 6.31, 7.11, 7.91, 8.71, 9.51};
    double theta[12]={0.806, -0.702, -1.395, -0.608, 0.889, 1.371, 0.391, -1.051, -1.314, -0.162, 1.183, 1.225};
    vector <pair<double,double>> v;
    for (int i = 0; i < 12; i++) {
        v.push_back(make_pair(time[i], theta[i]));
    }
    Interpolator pendulum(v);
    */
     
    cout << pendulum << endl;
    pendulum.GetPoints();
    cout << pendulum << endl;
    
    double x = 5.;

    
    cout << "\n Lagrange" << "\n" << pendulum.InterpolateLagrange(x) << endl;
    //pendulum.Draw("Lagrange");
    
    cout << "\n Newton" << "\n" << pendulum.InterpolateNewton(x) << endl;
    //pendulum.Draw("Newton");
    
    cout << "\n Neville" << "\n" << pendulum.InterpolateNeville(x) << endl;
    //pendulum.Draw("Neville");

    cout << "\n Spline3" << "\n" << pendulum.InterpolateSpline3(x) << endl;
    //pendulum.Draw("Spline3");

    cout << "\n Trigonometric" << "\n" << pendulum.InterpolateTrigonometric(x) << endl;
    //pendulum.Draw("Trigonometric");

    //Datapoints
    pendulum.Draw("All");

    return 0;
}