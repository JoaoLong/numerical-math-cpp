#ifndef __BVPSOLVER__
#define __BVPSOLVER__

#include "ODEsolver.h"
#include "FunctorND.h"
#include "RootFinderND.h"

//Class to solve ordinary differential equations boundary value problem

class BVPsolver : public ODEsolver {
    public:
        //Constructor and destructor
        BVPsolver() = default;
        BVPsolver(const ODEpoint&, std::vector<std::function<double(ODEpoint)>>&, std::vector<std::pair<int, std::pair<double, double>>>);
        ~BVPsolver() = default;
        
        //Shooting method
        const std::vector<ODEpoint>& ShootingSolver(double, double, double, std::pair<double, double>);
        const std::vector<ODEpoint>& ShootingNDSolver(double, double, double, std::vector<int>, std::vector<double>);

        //Draw graph of solution in [ti, tf]
        void Draw(double, double);

        //Obtain value of solution at a point t
        std::vector<double> Evaluate(double);

    private:
        //Vector of boundary conditions, ex: cfront[0] = {i, {ti, xi(ti)}}
        std::vector<std::pair<int, std::pair<double, double>>> cfront;  

        //Solution of BVP
        std::vector<ODEpoint> sol;
};

#endif