#include "FunctorND.h"
#include <iostream>
#include <cmath>

using namespace std;

//Constructor
FunctorND::FunctorND(std::string s, int n, std::function<double(std::vector<double>)> fi) {
    name = s;
    f = fi;
    if (n == 0) {
        cout << "No arguments?" << endl;
        exit(0);
    } else if (n == 1) {
        cout << "Use class Functor please" << endl;
    } else {
        dim = n;
    }
}

//Copy constructor
FunctorND::FunctorND(FunctorND& Fi) {
    name = Fi.name;
    f = Fi.f;
    dim = Fi.dim;
}

//Operator to calculate value of function at a point, f(x)
double FunctorND::operator() (vector<double> x) {
    return f(x); 
}

//Draw function in [xi, xf] x [yi, yf] with nx, ny points
void FunctorND::Draw(double xi, double xf, double yi, double yf, int nx, int ny, std::string xtitle, std::string ytitle, std::string ztitle) {
    if (dim == 2) {    
        TApplication *app = new TApplication("app", nullptr, nullptr);
        TCanvas *c = new TCanvas("c", "Graph of the points in class DataPoints", 0, 0, 1920, 1080);
        TRootCanvas *close = (TRootCanvas *)c->GetCanvasImp();
        close->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

        double dx = (xf-xi)/(nx-1);
        double dy = (yf-yi)/(ny-1);

        TGraph2D *graph = new TGraph2D(nx*ny);
        graph->SetLineColor(kBlue);
        graph->SetLineWidth(3);
        graph->SetName("Graph");
        graph->SetMarkerStyle(kFullCircle);
        graph->SetMarkerSize(.1);
        graph->SetMarkerColor(kBlack);
        graph->SetFillColor(68);
       
        string title = "Grafico de f(x,y) = " + this->name;
        graph->SetTitle(&title[0]);

        vector<double> v;
        v.resize(2);

        for (int i = 0; i < nx; i++) {
            v[0] = xi+i*dx;
            for (int j = 0; j < ny; j++) {
                v[1] = yi+j*dy;
                graph->SetPoint(nx*i+j, v[0], v[1], operator()(v));
            }    
        }
        gStyle->SetPalette(kRainBow);
        graph->Draw("surf2");
        graph->GetXaxis()->SetTitle(&xtitle[0]);
        graph->GetYaxis()->SetTitle(&ytitle[0]);
        graph->GetZaxis()->SetTitle(&ztitle[0]);
        
        c->Update();
        c->SaveAs("functorND.pdf");
        app->Run();

    } else {
        cout << "There is no draw for more than 3 dimensions." << endl;
    }    
}

//Getter for dimension
int FunctorND::GetDimension() {
    return dim;
}