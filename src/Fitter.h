#ifndef __FITTER__
#define __FITTER__

#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <iomanip> 
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <cstring>
#include <sstream>
#include <ostream>
#include <string>
#include <list>
#include <initializer_list>
#include <cmath>
#include "TLatex.h"
#include "TCanvas.h" 
#include "TRootCanvas.h"
#include "TH2F.h" 
#include "TApplication.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TMultiGraph.h"
#include "TColor.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPad.h"

//Class to fit a function f to a set of points (xi, yi) with errors (exi, eyi) with ROOT function TF1

class Fitter {
    public:
        //Constructors and destructor
        Fitter() = default;
        Fitter(std::vector<std::pair<double,double>>, std::vector<std::pair<double,double>>, std::vector<TF1*>);
        Fitter(std::string filename, std::vector<TF1*>);
        ~Fitter();

        //Getter and setter for points and errors
        void SetPoints(std::vector<std::pair<double,double>>); 
        void SetErrors(std::vector<std::pair<double,double>>);
        std::vector<std::pair<double,double>> GetPoints();
        std::vector<std::pair<double,double>> GetErrors();
        
        //Getter and setter for function to fit
        void SetFitFunction(std::vector<TF1*>);
        std::vector<TF1*> GetFitFunction(); 
        
        //Draw points
        void DrawPoints(double, double, double, double, std::string, std::string, std::string); 

        //Draw points and fitted curve
        void DrawFit(double, double, double, double, std::string, std::string, std::string); 

        //Print points and error values
        void Print(std::string, std::string);

    private:
        //Points and respective errors
        std::vector<std::pair<double,double>> points;
        std::vector<std::pair<double,double>> errors;

        //ROOT function TF1 to fit 
        std::vector<TF1*> f;
};

#endif