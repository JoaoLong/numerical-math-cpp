#ifndef __MULTIFITTER__
#define __MULTIFITTER__

#include "Fitter.h"

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

//Class to fit several functions fi to different sets of points (xi, yi) with errors (exi, eyi) in the same graph with ROOT function TF1

class MultiFitter {
    public:
        //Constructors and destructor
        MultiFitter() = default;
        MultiFitter(std::vector<Fitter>);
        ~MultiFitter() = default;
        
        //Draw points
        void DrawPoints(double, double, double, double, std::string, std::string, std::string); 

        //Fit functions without plotting
        void Fit();

        //Draw points and fitted curve
        void DrawFit(double, double, double, double, std::string, std::string, std::string); 

        //Print points and error values
        void Print(std::string, std::string);

    private:
        //Vector of Fitter with respective graphs
        std::vector<Fitter> fit;
};

#endif