#include "Functor.h"
#include <iostream>
#include <cmath>

using namespace std;

//Constructor
Functor::Functor(std::string s, std::function<double(double)> fi) : name(s), f(fi) {;}

//Copy constructor
Functor::Functor(Functor& Fi) {
    name = Fi.name;
    f = Fi.f;
}

//Operator to calculate value of function at a point, f(x)
double Functor::operator() (double x) {
    return f(x); 
}

//Draw function in [xi, xf] with num points
void Functor::Draw(double xi, double xf, int num, std::string xtitle, std::string ytitle) {
    double dx = (xf-xi)/(num-1);

    TApplication *app = new TApplication("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "Graph of the points in class DataPoints", 0, 0, 1920,1080);
    TRootCanvas *close = (TRootCanvas *)c->GetCanvasImp();
    close->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

    TGraph *graph = new TGraph(num);

    graph->SetLineColor(kBlue);
    graph->SetLineWidth(3);
    graph->SetName("Graph");
    graph->SetMarkerStyle(kFullCircle);
    graph->SetMarkerSize(.1);
    graph->SetMarkerColor(kBlack);
    graph->SetFillColor(68);
    graph->GetXaxis()->SetTitle(xtitle.c_str());
    graph->GetYaxis()->SetTitle(ytitle.c_str());
    string title = "Grafico de f(x) = " + this->name;
    graph->SetTitle(&title[0]);
    c->SetGrid();

    for (int i = 0; i < num; i++) {
        graph->SetPoint(i, xi + i*dx, operator()(xi + i*dx));
    }

    graph->Draw("ALP");
    c->Update();
    c->SaveAs("functor.pdf");
    app->Run();
}