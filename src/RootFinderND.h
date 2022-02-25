#ifndef __ROOTFINDERND__
#define __ROOTFINDERND__

#include "FunctorND.h"
#include "IntegDerivND.h"
#include "EqSolver.h"

//Class to find solutions of system of nonlinear equations fi(x1, ..., xn) = 0

class RootFinderND {
    public:
        //Constructors and destructor
        RootFinderND() = default;
        RootFinderND(std::vector<FunctorND>&);
        ~RootFinderND() = default;

        //Newton method with analytic jacobian matrix
        vector<double> NewtonND(vector<double>, double, std::vector<std::vector<std::function<double(std::vector<double>)>>>);

        //Newton method with numerical jacobian matrix
        vector<double> NewtonNDNumerical(vector<double>, double);        

    private:
        //Functions of system fi(x1, ..., xn) = 0;
        std::vector<FunctorND>& F;
};

#endif  