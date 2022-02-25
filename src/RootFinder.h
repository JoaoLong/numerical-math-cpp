#ifndef __ROOTFINDER__
#define __ROOTFINDER__

#include "Functor.h"
#include "IntegDeriv.h"

//Class to find solutions of nonlinear equation f(x) = 0

class RootFinder {
    public:
        //Constructors and destructor
        RootFinder() = default;
        RootFinder(Functor&);
        ~RootFinder() = default;

        //Bisection method
        double BisectionMethod(double&, double&, double);

        //Regula falsi
        double RegulaFalsi(double&, double&, double);

        //Newton method with analytic derivative
        double NewtonRaphson(double, double, std::function<double(double)>);

        //Newton method with numerical derivative
        double NewtonNumerical(double, double);

        //Secant method
        double SecantMethod(double, double, double);

    private:
        //Function f(x)
        Functor& F;
};

#endif  