#ifndef __SERIESTRANSFORMS__
#define __SERIESTRANSFORMS__

#include "IntegDeriv.h"
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
#include "TF1.h"
#include "TMultiGraph.h"
#include "TColor.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPad.h"

//Class to find series and transforms of function f(x)

class SeriesTransforms {
    public:
        //Constructors and destructor
        SeriesTransforms() = default;
        SeriesTransforms(Functor&);
        ~SeriesTransforms() = default;

        //Taylor series of order n
        double TaylorSeries(int, double, double);

        //Fourier series of order n with period L, interval [-L, L]
        double FourierSeries(int, double, double);

        //Discrete Fourier Transform of function
        double DiscreteFourierTransform(double, double, double);

        //Fast Fourier Transform of function
        double FastFourierTransform(double, double, double);

        //Draw function and approximations, with string key "Taylor", "Fourier", "DFT", "FFT"
        void Draw(int, double, double, double, double, int);

        //Evaluate infinite series of given function up to precision
        static double InfiniteSeries(std::function<double(int)>, double, int);

    private:
        //Function f(x)
        Functor& F;
};

#endif  