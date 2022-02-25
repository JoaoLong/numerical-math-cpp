#ifndef __INTEGDERIV__
#define __INTEGDERIV__

#include "Functor.h"
#include "FCrand.h"

//Class to differentiate and integrate one dimensional functions f(x)

class IntegDeriv {
    public:
        //Constructor and destructor
        IntegDeriv() = default;
        IntegDeriv(Functor&);
        ~IntegDeriv() = default;

        //Integration methods  
        double TrapezoidalRule(double, double, double&);
        double SimpsonRule(double, double, double&);

        //Monte Carlo integration
        double IntegrateMC(double, double, double&, int&);  

        //Monte Carlo importance sampling 
        double IntegrateMCIS(double, double, std::function<double(double)>, std::function<double(double)>, double&, int&);
        double IntegrateMCISDistribution(double, double, std::function<double(double)>, double&, int&);

        //Monte Carlo von Neumann (acceptance-rejection)
        double IntegrateMCVN(double, double, double&, int&);

        //First derivative methods
        double D1backward(double, double);
        double D1central(double, double);
        double D1forward(double, double);
        double D1fivepoint(double, double);

        //Second derivative methods
        double D2backward(double, double);
        double D2central(double, double);
        double D2forward(double, double);
        double D2fivepoint(double, double);

        //Third derivative methods
        double D3backward(double, double);
        double D3central(double, double);
        double D3forward(double, double);
        double D3fivepoint(double, double);

        //Fourth derivative methods 
        double D4backward(double, double);
        double D4central(double, double);
        double D4forward(double, double);
        double D4fivepoint(double, double);

        //Nth derivative with central finite difference
        double Dncentral(double, double);
        
    private:
        //Function to differentiate and integrate
        Functor& F;
};

#endif  