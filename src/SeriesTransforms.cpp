#include "SeriesTransforms.h"
#include <iostream>

using namespace std;

//Constructor
SeriesTransforms::SeriesTransforms(Functor& Fi) : F(Fi) {;}
     
//Taylor series of order n centered at x0
double SeriesTransforms::TaylorSeries(int n, double x0, double x) {
    IntegDeriv* deriv = new IntegDeriv(F);
    function<int(int)> factorial = [&factorial](int k) {
        if (k < 0) {
            cout << "\n Factorial is not defined for negative integers." << endl;
            exit(0);
        }
        if (k == 0) {
            return 1;
        }    
        return k*factorial(k-1);
    };

    double sum = F(x0);

    for (int i = 1; i <= n; i++) {
        sum += deriv->Dncentral(i, 1E-5, x0)*pow(x-x0, i)/factorial(i);
    } 
    delete deriv;
    return sum;
}

//Fourier series of order n with period L, interval [-L, L]
double SeriesTransforms::FourierSeries(int n, double L, double x) {

    double sum = 0.;
    double error = 0.;

    for (int i = 0; i < n; i++) {
        function<double(double)> fcos = [i, L, this](double x) {
            return cos(i*M_PI*x/L)*F(x);
        };
        function<double(double)> fsin = [i, L, this](double x) {
            return sin(i*M_PI*x/L)*F(x);
        };
        Functor* f1cos = new Functor("fcos", fcos);
        Functor* f1sin = new Functor("fsin", fsin);
        IntegDeriv* derivcos = new IntegDeriv(*f1cos);
        IntegDeriv* derivsin = new IntegDeriv(*f1sin);

        if (i == 0) {
            sum += 0.5*derivcos->IntegrateMC(-L, L, error, 10000)/L;
        } else {
            sum += derivcos->IntegrateMC(-L, L, error, 10000)*cos(i*M_PI*x/L)/L + derivsin->IntegrateMC(-L, L, error, 10000)*sin(i*M_PI*x/L)/L;
        }    

        delete f1sin;
        delete f1cos;
        delete derivsin;
        delete derivcos;
    }
    return sum;    
}

//Discrete Fourier Transform of function in [xi, xf] with step h
double SeriesTransforms::DiscreteFourierTransform(double xi, double xf, double h) {

}

//Fast Fourier Transform of function in [xi, xf] with step h
double SeriesTransforms::FastFourierTransform(double xi, double xf, double h) {

}

//Draw function and Taylor and Fourier series
void SeriesTransforms::Draw(int n, double x0, double L, double xi, double xf, int num) {

    double dx = (xf-xi)/(num-1);

    TApplication *app = new TApplication("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "Taylor and Fourier series", 0, 0, 1920,1080);
    TRootCanvas *close = (TRootCanvas *)c->GetCanvasImp();
    close->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

    TMultiGraph* mg = new TMultiGraph();
    TGraph* graph[2];

    string title = "Taylor and Fourier series of order " + to_string(n) + " of f(x) = " + F.GetName();
    mg->SetTitle(&title[0]);

    for (int i = 0; i < 3; i++) {
        graph[i] = new TGraph(num);
        graph[i]->SetLineWidth(3);
        graph[i]->SetName("Graph");
        graph[i]->SetMarkerStyle(kFullCircle);
        graph[i]->SetMarkerSize(0.1);
        graph[i]->SetMarkerColor(kBlack);
        c->SetGrid();
    }
    for (int i = 0; i < num; i++) {
        graph[0]->SetPoint(i, xi + i*dx, 0);
        graph[1]->SetPoint(i, xi + i*dx, FourierSeries(n, L, xi + i*dx));
        graph[2]->SetPoint(i, xi + i*dx, F(xi + i*dx));
    }
    mg->Add(graph[0]);
    mg->Add(graph[1]);
    mg->Add(graph[2]);
    mg->GetXaxis()->SetLimits(xi, xf);
    mg->GetXaxis()->SetTitle("x");
    mg->GetYaxis()->SetTitle("y");

    gStyle->SetPalette(kRainBow);
    mg->Draw("APLC");

    TLegend* legend = new TLegend(.85, .85, .999, 1.);
    legend->SetFillColor(0);
    legend->AddEntry(graph[0], "Taylor series", "lpf");
    legend->AddEntry(graph[1], "Fourier series", "lpf");
    legend->AddEntry(graph[2], "f(x)", "lpf");
    legend->Draw();

    c->Update();
    c->SaveAs("taylorfourier.pdf");
    app->Run();
}

//Evaluate infinite series of given function g(n) up to precision starting at i
double SeriesTransforms::InfiniteSeries(std::function<double(int)> g, double error, int i) {
    double sum = 0.;
    do {
        sum += g((double)i);
        i++;

        if (i >= 100000) {
            cout << "\n Make sure the series converges beforehand, otherwise there will be an infinite loop." << endl;
            return 0;
        }

    } while (fabs(g(i+1)-g(i)) > error);
    return sum;  
}