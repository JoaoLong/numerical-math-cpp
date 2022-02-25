#include "Interpolator.h"
#include <iostream>
#include <cmath>

using namespace std;

//Constructor with C array
Interpolator::Interpolator(int N, double *x, double *y) : DataPoints(N, x, y) {
    std::function<double(double*, double*)> fauxL = [this](double* x, double* p) {
        return this->InterpolateLagrange(x[0]);
    };
    std::function<double(double*, double*)> fauxN = [this](double* x, double* p) {
        return this->InterpolateNewton(x[0]);
    };
    std::function<double(double*, double*)> fauxS = [this](double* x, double* p) {
        return this->InterpolateSpline3(x[0]);
    };
    std::function<double(double*, double*)> fauxNev = [this](double* x, double* p) {
        return this->InterpolateNeville(x[0]);
    };
    std::function<double(double*, double*)> fauxTrig = [this](double* x, double* p) {
        return this->InterpolateTrigonometric(x[0]);
    };
    TF1 *lagrange = new TF1("lagrange", fauxL, 0, 1, 0);
    TF1 *newton = new TF1("newton", fauxN, 0, 1, 0);
    TF1 *spline3 = new TF1("spline3", fauxS, 0, 1, 0);
    TF1 *neville = new TF1("neville", fauxNev, 0, 1, 0);
    TF1 *trigonometric = new TF1("trigonometric", fauxTrig, 0, 1, 0);
    MI["Lagrange"] = lagrange;
    MI["Newton"] = newton;
    MI["Neville"] = neville;
    MI["Spline3"] = spline3;
    MI["Trigonometric"] = trigonometric;
}

//Constructor with vector of pairs
Interpolator::Interpolator(const std::vector<std::pair<double, double>> &A) : DataPoints(A) {
    std::function<double(double*, double*)> fauxL = [this](double* x, double* p) {
        return this->InterpolateLagrange(x[0]);
    };
    std::function<double(double*, double*)> fauxN = [this](double* x, double* p) {
        return this->InterpolateNewton(x[0]);
    };
    std::function<double(double*, double*)> fauxS = [this](double* x, double* p) {
        return this->InterpolateSpline3(x[0]);
    };
    std::function<double(double*, double*)> fauxNev = [this](double* x, double* p) {
        return this->InterpolateNeville(x[0]);
    };
    std::function<double(double*, double*)> fauxTrig = [this](double* x, double* p) {
        return this->InterpolateTrigonometric(x[0]);
    };
    TF1 *lagrange = new TF1("lagrange", fauxL, 0, 1, 0);
    TF1 *newton = new TF1("newton", fauxN, 0, 1, 0);
    TF1 *spline3 = new TF1("spline3", fauxS, 0, 1, 0);
    TF1 *neville = new TF1("neville", fauxNev, 0, 1, 0);
    TF1 *trigonometric = new TF1("trigonometric", fauxTrig, 0, 1, 0);
    MI["Lagrange"] = lagrange;
    MI["Newton"] = newton;
    MI["Neville"] = neville;
    MI["Spline3"] = spline3;
    MI["Trigonometric"] = trigonometric;   
}

//Constructor with two vectors of coordinates
Interpolator::Interpolator(const std::vector<double> &x, const std::vector<double> &y) : DataPoints(x, y) {
    std::function<double(double*, double*)> fauxL = [this](double* x, double* p) {
        return this->InterpolateLagrange(x[0]);
    };
    std::function<double(double*, double*)> fauxN = [this](double* x, double* p) {
        return this->InterpolateNewton(x[0]);
    };
    std::function<double(double*, double*)> fauxS = [this](double* x, double* p) {
        return this->InterpolateSpline3(x[0]);
    };
    std::function<double(double*, double*)> fauxNev = [this](double* x, double* p) {
        return this->InterpolateNeville(x[0]);
    };
    std::function<double(double*, double*)> fauxTrig = [this](double* x, double* p) {
        return this->InterpolateTrigonometric(x[0]);
    };
    TF1 *lagrange = new TF1("lagrange", fauxL, 0, 1, 0);
    TF1 *newton = new TF1("newton", fauxN, 0, 1, 0);
    TF1 *spline3 = new TF1("spline3", fauxS, 0, 1, 0);
    TF1 *neville = new TF1("neville", fauxNev, 0, 1, 0);
    TF1 *trigonometric = new TF1("trigonometric", fauxTrig, 0, 1, 0);
    MI["Lagrange"] = lagrange;
    MI["Newton"] = newton;
    MI["Neville"] = neville;
    MI["Spline3"] = spline3;
    MI["Trigonometric"] = trigonometric;
}

//Lagrange interpolation
double Interpolator::InterpolateLagrange(double x) {
    double l, sum;
    int N = P.size();

    sum = 0.;
    for (int i = 0; i < N; i++) {
        l = 1.;
        for (int k = 0; k < N; k++) {
            if (k != i) {
                l *= (x - P[k].first)/(P[i].first - P[k].first);
            }
        }
        sum += P[i].second * l;
    }
    return sum;
}

//Newton interpolation
double Interpolator::InterpolateNewton(double x) {
    vector<double> a;
    int N = P.size();
    a.resize(N);

    //Coefficients
    for (int i = 0; i < N; i++) {
        a[i] = P[i].second;
    }

    for (int k = 1; k < N; k++) {
        for (int i = k; i < N; i++) {
            a[i] = (a[i] - a[k-1]) / (P[i].first - P[k - 1].first);
        }
    }
    //Polynomial
    double pol = a[N-1];
    for (int i = 1; i < N; i++) {
        pol = a[N-1-i] + (x - P[N-1-i].first) * pol;
    }
    return pol;
} 

//Neville interpolation
double Interpolator::InterpolateNeville(double x) {
    vector<double> a;
    int N = P.size();
    a.resize(N);

    //Coefficients
    for (int i = 0; i < N; i++) {
        a[i] = P[i].second;
    }

    for (int k = 1; k < N; k++) {
        for (int i = 0; i < N-k; i++) {
            a[i] = ((x - P[i+k].first)*a[i] - (x - P[i].first)*a[i+1])/(P[i].first-P[i+k].first);
        }
    }

    return a[0];
} 

//Cubic spline interpolation
double Interpolator::InterpolateSpline3(double x) {
    //N points, N-1 functions, matrix N-2 x N-2
    int N = P.size();
    int o = 0;

    Eigen::Matrix<double,Eigen::Dynamic,1> Kaux;
    Eigen::Matrix<double,Eigen::Dynamic,1> K;
    Eigen::Matrix<double,Eigen::Dynamic,1> B;
    Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> A;

    Kaux.resize(N-2,1);
    K.resize(N, 1);
    A.resize(N-2,N-2);
    B.resize(N-2, 1);

    for (int i = 0; i < N-2; i++) {
        for (int j = 0; j < N-2; j++){
            A(i,j) = 0;
        }
        B(i,0) = 0;
        Kaux(i,0) = 0;
        K(i,0) = 0;
    }
    K[N-2] = 0;
    K[N-1] = 0;

    //Coefficients of A

    for (int i = 0; i < N-3; i++) {
        A(i,i) = 2*(P[i].first - P[i+2].first);
        A(i, i+1) = P[i+1].first - P[i+2].first;
        A(i+1, i) = A(i, i+1);
    }
    A(N-3, N-3) = 2*(P[N-3].first - P[N-1].first);
    
    //Coefficients of B

    for (int i = 1; i < N-1; i++) {
        B[i-1] = 6*((P[i-1].second - P[i].second)/(P[i-1].first - P[i].first) - (P[i].second - P[i+1].second)/(P[i].first - P[i+1].first));
    }
    
    EqSolver* spline3 = new EqSolver(A, B);
    Kaux = spline3->GaussSolver(true);
    delete spline3;

    K[0]=0;
    K[N-1]=0;
    for (int i = 1; i < N-1; i++) {
        K[i] = Kaux[i-1];
    }
    
    //Determine interval [x(i), x(i+1)]
    for (int k = 0; k < N; k++) {
        if (x >= P[k].first && x <= P[k+1].first) {
            o = k;
            break;
        }
    }

    //Behaviour past x[n-1]
    if (x >= P[N-1].first) {
        o = N-2;
    }

    return (K[o]/6)*((pow(x-P[o+1].first,3))/(P[o].first-P[o+1].first)-(x-P[o+1].first)*(P[o].first-P[o+1].first))-
			(K[o+1]/6)*((pow(x-P[o].first, 3))/(P[o].first-P[o+1].first)-(x-P[o].first)*(P[o].first-P[o+1].first))+
			(P[o].second*(x-P[o+1].first)-P[o+1].second*(x-P[o].first))/(P[o].first-P[o+1].first);

}

// Trigonometric interpolation
double Interpolator::InterpolateTrigonometric(double x) {
    vector<double> a;
    int N = P.size();
    a.resize(N);

    double prod;

    //if (N % 2 == 1) {
    for (int k = 0; k < N; k++) {
        prod = 1.;
        for (int m = 0; m < N; m++) {
            if (m != k) {
                prod *= sin(0.5*(x-P[m].first))/sin(0.5*(P[k].first-P[m].first));
            }
        }
        a[k] = prod;
    }  
    /* } else {
        vector<double> b;
        b.resize(N);
        double sum1 = 0.;
        for (int k = 0; k < N; k++) {
            sum1 = 0.;
            prod = 1.;
            for (int m = 0; m < N; m++) {
                if (m != k) {
                    sum1 += P[m].first;
                    prod *= sin(0.5*(x-P[m].first))/sin(0.5*(P[k].first-P[m].first));
                }
            }
            b[k] = sum1;
            a[k] = prod*sin(0.5*(x-b[k]))/sin(0.5*(P[k].first-b[k]));
        }  
    }     */  
   
    double sum = 0.;

    //Coefficients
    for (int i = 0; i < N; i++) {
        sum += a[i]*P[i].second;
    }

    return sum;
} 

//Draw points and interpolated curve, with string "Lagrange", "Newton", "Spline3", "Trigonometric", "All", "Points"
void Interpolator::Draw(std::string s) {
    TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "Graph of the points in class DataPoints", 0, 0, 1800, 1000);
    TRootCanvas *rc = (TRootCanvas *)c->GetCanvasImp();
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

    if (s == "All") {
        this->DataPoints::Draw("all methods");
        MI["Lagrange"]->SetLineColor(kGreen);
        MI["Lagrange"]->SetLineWidth(2);
        MI["Lagrange"]->SetRange(GetPoints()[0].first*0.9, GetPoints()[GetPoints().size()-1].first*1.05);  
        MI["Lagrange"]->Draw("same");
        
        MI["Spline3"]->SetLineColor(kRed);
        MI["Spline3"]->SetLineWidth(2);
        MI["Spline3"]->SetRange(GetPoints()[0].first*0.9, GetPoints()[GetPoints().size()-1].first*1.05);  
        MI["Spline3"]->Draw("same");

        MI["Trigonometric"]->SetLineColor(kRed);
        MI["Trigonometric"]->SetLineWidth(2);
        MI["Trigonometric"]->SetRange(GetPoints()[0].first*0.9, GetPoints()[GetPoints().size()-1].first*1.05);  
        MI["Trigonometric"]->Draw("same");

        double ymaxpol = MI["Lagrange"]->GetMaximum(GetPoints()[0].first, GetPoints()[GetPoints().size()-1].first);
        double ymaxs = MI["Spline3"]->GetMaximum(GetPoints()[0].first, GetPoints()[GetPoints().size()-1].first);
        double ymaxtrig = MI["Trigonometric"]->GetMaximum(GetPoints()[0].first, GetPoints()[GetPoints().size()-1].first);

        double yminpol = MI["Lagrange"]->GetMinimum(GetPoints()[0].first, GetPoints()[GetPoints().size()-1].first);
        double ymins = MI["Spline3"]->GetMinimum(GetPoints()[0].first, GetPoints()[GetPoints().size()-1].first);
        double ymintrig = MI["Trigonometric"]->GetMinimum(GetPoints()[0].first, GetPoints()[GetPoints().size()-1].first);

        double ymax=0, ymin=0;

        if (ymaxpol >= ymaxs && ymaxpol >= ymaxtrig) {
            ymax = ymaxpol;
        } else if (ymaxs >= ymaxtrig && ymaxs >= ymaxtrig) {
            ymax = ymaxs;
        } else {
            ymax = ymaxtrig;
        }

        if (yminpol <= ymins && yminpol <= ymintrig) {
            ymin = yminpol;
        } else if (ymins <= ymintrig && ymins <= ymintrig) {
            ymin = ymins;
        } else {
            ymin = ymintrig;
        }  

        graph->SetMinimum(ymin*1.1);
        graph->SetMaximum(ymax*1.1);
        graph->GetXaxis()->SetLimits(GetPoints()[0].first*0.9, GetPoints()[GetPoints().size()-1].first*1.05);

        gStyle->SetPalette(kRainBow);
        TLegend* legend = new TLegend(.85, .90, 1., 1.);
        legend->SetFillColor(0);
        legend->AddEntry("lagrange","Polynomial","lpf");
        legend->AddEntry("spline3","Cubic spline","lpf");
        legend->AddEntry("trigonometric","Trigonometric","lpf");
        legend->Draw();
        c->Update();

    } else if (s == "Points") {
        this->DataPoints::Draw("Points");
    } else {
        this->DataPoints::Draw(s);
        graph->GetXaxis()->SetRangeUser(-10, 10);
        MI[s]->SetLineColor(38);
        MI[s]->SetLineWidth(2);
        MI[s]->SetRange(GetPoints()[0].first*0.9, GetPoints()[GetPoints().size()-1].first*1.05);

        double ymax = MI[s]->GetMaximum(GetPoints()[0].first, GetPoints()[GetPoints().size()-1].first);
        double ymin = MI[s]->GetMinimum(GetPoints()[0].first, GetPoints()[GetPoints().size()-1].first);
        graph->SetMinimum(ymin*1.1);
        graph->SetMaximum(ymax*1.1);
        graph->GetXaxis()->SetLimits(GetPoints()[0].first*0.9, GetPoints()[GetPoints().size()-1].first*1.05);

        MI[s]->Draw("same");
    }

    c->Update();
    if (s == "Lagrange") {
        c->SaveAs("lagrange.pdf");
    } else if (s == "Newton") {
        c->SaveAs("newton.pdf");
    } else if (s == "Neville") {
        c->SaveAs("neville.pdf");
    } else if (s == "Spline3") {
        c->SaveAs("spline3.pdf");
    } else if (s == "Trigonometric") {
        c->SaveAs("trigonometric.pdf");
    } else if (s == "All") {
        c->SaveAs("interpolator.pdf");
    } else if (s == "Points") {
        c->SaveAs("datapoints.pdf");
    }  
       
    app.Run();
}

//Getter for interpolated functions
const TF1& Interpolator::GetFunction(std::string s) {
    return *MI[s];
}