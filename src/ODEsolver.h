#ifndef __ODESOLVER__
#define __ODESOLVER__

#include "ODEpoint.h"
#include "Functor.h"
#include "RootFinder.h"
#include <functional>

//Class to solve system of ordinary differential equations, dx/dt = f(t, x) (x vector)

class ODEsolver {
    public:
        //Constructors and destructor
        ODEsolver() = default;
        ODEsolver(const ODEpoint&, std::vector<std::function<double(ODEpoint)>>&);
        ODEsolver(const ODEsolver&);
        ~ODEsolver() = default;

        //Predictor-corrector method solver
        const std::vector<ODEpoint>& PredictorCorrectorSolver(double, double);

        //Euler method solver
        const std::vector<ODEpoint>& EulerSolver(double, double);

        //Euler-Cromer method solver
        const std::vector<ODEpoint>& EulerCromerSolver(double, double);

        //Runge-Kutta 2 method solver
        const std::vector<ODEpoint>& RungeKutta2Solver(double, double);

        //Runge-Kutta 4 method solver
        const std::vector<ODEpoint>& RungeKutta4Solver(double, double);

        //Draw graph of solution in [ti, tf]
        void Draw(std::vector<std::string>, double, double);

        //Obtain value of solution at a point t
        std::vector<double> Evaluate(double, std::string);

    protected:
        //Initial conditions, x(t0)
        ODEpoint X0; 
    
        //Functions of the system of ODEs, dxi/dt = fi(t)
        std::vector<std::function<double(ODEpoint)>> f;

    private:
        //Map of solutions, key = "predictorcorrector", "euler", "eulercromer" "RK2", "RK4"
        std::map<std::string, std::vector<ODEpoint>> MS;
};

#endif