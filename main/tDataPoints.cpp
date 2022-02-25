#include "DataPoints.h"
#include <iostream>

using namespace std;

//Test main of class DataPoints

int main() {
    //C array
    
    double time[12]={0.71, 1.51, 2.31, 3.11, 3.91, 4.71, 5.51, 6.31, 7.11, 7.91, 8.71, 9.51};
    double theta[12]={0.806, -0.702, -1.395, -0.608, 0.889, 1.371, 0.391, -1.051, -1.314, -0.162, 1.183, 1.225};
    DataPoints pendulum(12, time, theta);

    /*
    //Two vectors
    vector <double> time = {9.51, 1.51, 2.31, 3.11, 3.91, 4.71, 5.51, 6.31, 7.11, 7.91, 8.71, 0.71};
    vector <double> theta = {0.806, -0.702, -1.395, -0.608, 0.889, 1.371, 0.391, -1.051, -1.314, -0.162, 1.183, 1.225};
    DataPoints pendulum(time, theta);
    */

    /*
    //Vector of pairs
    double time[12]={0.71, 1.51, 2.31, 3.11, 3.91, 4.71, 5.51, 6.31, 7.11, 7.91, 8.71, 9.51};
    double theta[12]={0.806, -0.702, -1.395, -0.608, 0.889, 1.371, 0.391, -1.051, -1.314, -0.162, 1.183, 1.225};
    vector <pair<double,double>> v;
    for (int i = 0; i < 12; i++) {
        v.push_back(make_pair(time[i], theta[i]));
    }
    DataPoints pendulum(v);
    */
    
    cout << pendulum << endl;
    pendulum.GetPoints();
    cout << pendulum << endl;
    pendulum.Draw("Points");

    return 0;
}