#ifndef __FUNCTOR__
#define __FUNCTOR__

#include <string>
#include <functional>
#include "TCanvas.h"
#include "TF1.h"
#include "TRootCanvas.h"
#include "TH2F.h" 
#include "TApplication.h"
#include "TGraph.h"
#include "TLatex.h"

//Class to define a one dimensional function f(x)

class Functor {
    public:
        //Constructors and destructor
        Functor() = default;
        Functor(std::string, std::function<double(double)>);
        Functor(Functor&);
        ~Functor() = default;

        //Calculate value of function at a point, f(x)
        double operator() (double);

        //Draw function in [xi, xf]
        void Draw(double, double, int, std::string, std::string);

        //Getter for string name
        std::string GetName();

    private:
        //Function expression as a string, "x sin(x)"
        std::string name;

        //Function f(x)
        std::function<double(double)> f;
};

#endif
