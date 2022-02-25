#include "ODEsolver.h"
#include <iostream>

using namespace std;

//Test main of class ODEsolver

int main() {
    double t0 = 5;
    int dim = 12;

    //ODEpoint - initial conditions

    vector<double> v = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //initializer_list<double> l = {0, 0};

    ODEpoint X0(t0, v);

    //Lambda Functions

    vector<function<double(ODEpoint)>> fi;
    fi.resize(dim);
    fi[0] = [](ODEpoint Y) {  // dx0/dt = sin(t) + x0 
        return sin(Y.T()) + Y.X()[0];
    };
    fi[1] = [](ODEpoint Y) {  // dx1/dt = cos(t) - x1
        return cos(Y.T()) - Y.X()[1];
    };
    fi[2] = [](ODEpoint Y) {  // dx2/dt = exp(t) + x7
        return exp(Y.T()) + Y.X()[7];
    };
    fi[3] = [](ODEpoint Y) {  // dx3/dt = exp(2-t) - x3
        return exp(2-Y.T()) - Y.X()[3];
    };
    fi[4] = [](ODEpoint Y) {  // dx4/dt = sin²(t+3) + x4
        return sin(3+Y.T())*sin(3+Y.T()) + Y.X()[4];
    };
    fi[5] = [](ODEpoint Y) {  // dx5/dt = cos(t+5) - x1
        return cos(5+Y.T()) - Y.X()[1];
    };
    fi[6] = [](ODEpoint Y) {  // dx6/dt = sinh(t) + x8
        return sinh(Y.T()) + Y.X()[8];
    };
    fi[7] = [](ODEpoint Y) {  // dx7/dt = cosh(t) - x4
        return cosh(Y.T()) - Y.X()[4];
    };
    fi[8] = [](ODEpoint Y) {  // dx8/dt = exp(2t) + x6
        return exp(2*Y.T()) + Y.X()[6];
    };
    fi[9] = [](ODEpoint Y) {  // dx9/dt = tanh(5-t) + t⁵ - x3 
        return tanh(5-Y.T()) - Y.X()[3] + pow(Y.T(), 5);
    };
    fi[10] = [](ODEpoint Y) { // dx10/dt = sin(t+32)sin(t+3) + x10 
        return sin(32+Y.T())*sin(3+Y.T()) + Y.X()[10];
    };
    fi[11] = [](ODEpoint Y) { // dx11/dt = cosh(t+12) - x6
        return cosh(12+Y.T()) - Y.X()[6];
    };
    
    ODEsolver solver(X0, fi);
    double step = 0.1;
    double tmax = 10;
    double x = 6.;
    
    vector<string> s = {"euler", "eulercromer", "predictorcorrector", "RK2", "RK4"};

    solver.EulerSolver(step, tmax);
    solver.EulerCromerSolver(step, tmax);
    solver.PredictorCorrectorSolver(step, tmax);    
    solver.RungeKutta2Solver(step, tmax);
    solver.RungeKutta4Solver(step, tmax);

    for (int i = 0; i < fi.size(); i++) {
        cout << "\n";
        cout << "Euler: x" << i << "(" << x << ") = " << solver.Evaluate(x, "euler")[i] << endl;
        cout << "Euler-Cromer: x" << i << "(" << x << ") = " << solver.Evaluate(x, "eulercromer")[i] << endl;
        cout << "Predictor-Corrector: x" << i << "(" << x << ") = " << solver.Evaluate(x, "predictorcorrector")[i] << endl;
        cout << "RK2: x" << i << "(" << x << ") = " << solver.Evaluate(x, "RK2")[i] << endl;
        cout << "RK4: x" << i << "(" << x << ") = " << solver.Evaluate(x, "RK4")[i] << endl;
    } 

    solver.Draw(s, t0, tmax);
}