#include "BVPsolver.h"
#include <iostream>

using namespace std;

//Test main of class BVPsolver

int main() {
    double t0 = 0;
    double tmax = 45;
    double g = 9.81;
    double k = 0.3;
    double m = 80.;

    //ODEpoint - initial conditions
    vector<double> v = {0, 0};

    //initializer_list<double> l = {0, 0};
    ODEpoint X0(t0, v);

    //Lambda functions
    vector<function<double(ODEpoint)>> fi;
    fi.resize(2);

    fi[0] = [](ODEpoint Y) {  // dy/dt = v 
        return Y.X()[1];
    };

    fi[1] = [k, m, g](ODEpoint Y) { // dv/dt = kv^2/m - g
        double a;
        if (Y.X()[1] < 0) {
            a = 1.;
        } else {
            a = -1.;
        }
        return a*k*Y.X()[1]*Y.X()[1]/m-g;
    };

    //Shooting 1D
    vector<pair<int, pair<double, double>>> M = {{0, {42.7171, 0}}};

    BVPsolver solver(X0, fi, M);
    double step = 0.1;

    solver.ShootingSolver(step, tmax, 1E-1, {1800, 2200});

    cout << "\n Initial position: " << solver.Evaluate(0)[0] << " m" << endl;

    solver.Draw(t0, tmax);
 
    //Shooting ND

    double t01 = 0.;
    double tmax1 = 10.;

    vector<function<double(ODEpoint)>> gi;
    gi.resize(3);
    gi[0] = [](ODEpoint Y) { //dx/dt = x-y
        return Y.X()[0] - Y.X()[1];
    };
    gi[1] = [](ODEpoint Y) { //dy/dt = 2x-y
        return 2*Y.X()[0] - Y.X()[1];
    };
    gi[2] = [](ODEpoint Y) { //dz/dt = y - z sin t
        return Y.X()[1] - sin(Y.T())*Y.X()[2];
    };

    ODEpoint X01(0, {1, 0, 1});

    //Solution: x(t) = cos t + sin t, y(t) = 2 sin t

    //Different possibilities of boundary conditions

    vector<pair<int, pair<double, double>>> M1 = { {0, {5, cos(5)+sin(5)}}, {1, {5, 2*sin(5)}} };
    //vector<pair<int, pair<double, double>>> M1 = { {0, {5, cos(5)+sin(5)}}, {0, {6, cos(6)+sin(6)}} };

    BVPsolver solvernd(X01, gi, M1);

    solvernd.ShootingNDSolver(0.1, tmax1, 1E-8, {0, 1}, {10., 10.});

    cout << "\n Initial condition x0: " << solvernd.Evaluate(0)[0] << endl;
    cout << "\n Initial condition x1: " << solvernd.Evaluate(0)[1] << endl;
    cout << "\n Initial condition x2: " << solvernd.Evaluate(0)[2] << endl;

    solvernd.Draw(t01, tmax1);
    
    return 0;
}