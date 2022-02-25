#ifndef __ODEPOINT__
#define __ODEPOINT__

#include "Xvar.h"

//Class to store point (t, x1(t), ..., xn(t)), solution of a system of ordinary differential equations

class ODEpoint : public Xvar {
    public:
        //Constructors and destructor
        ODEpoint() = default;
        ODEpoint(double, Xvar);
        ODEpoint(double, const std::vector<double> &);
        ODEpoint(double, const std::initializer_list<double> &);
        virtual ~ODEpoint() = default;

        //Setter for t and x
        void SetODEpoint(double, Xvar &);
        void SetODEpoint(double, const std::initializer_list<double> &);
        void SetODEpoint(double, std::vector<double>);
        
        //Accessor to independent variable
        double& T(); 

        //Write independent variable t and dependent variables xi
        friend std::ostream& operator<< (std::ostream&, const ODEpoint&); 

    private:
        //Independent variable, dependent variables on Xvar class
        double t;  
};

#endif