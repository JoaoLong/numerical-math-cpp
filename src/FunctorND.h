#ifndef __FUNCTORND__
#define __FUNCTORND__

#include <string>
#include "Functor.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TRootCanvas.h"
#include "TH2F.h" // histogram 2D
#include "TApplication.h"
#include "TGraph2D.h"
#include "TLatex.h"
#include "TStyle.h"

//Class to define a N dimensional function f(x1, ..., xn)

class FunctorND {
    public:
        //Constructors and destructor
        FunctorND() = default;
        FunctorND(std::string, int, std::function<double(std::vector<double>)>);
        FunctorND(FunctorND&);
        ~FunctorND() = default;

        //Calculate value of function at a point, f(x1, ..., xn)
        double operator() (std::vector<double>);

        //Draw function in [xi, xf] x [yi, yf]
        void Draw(double, double, double, double, int, int, std::string, std::string, std::string);
        
        //Getter for dimension of function
        int GetDimension();

    private:
        //Function expression as a string, "xy sin(xy)"
        std::string name;

        //Function f(x1, ..., xn)
        std::function<double(std::vector<double>)> f;

        //Dimension of function
        int dim;
};

#endif
