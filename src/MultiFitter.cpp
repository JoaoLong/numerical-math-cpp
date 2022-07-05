#include "MultiFitter.h"

using namespace std;

//Constructor with vector of Fitter
MultiFitter::MultiFitter(std::vector<Fitter> fiti) {
    fit.resize(fiti.size());
    copy(fiti.begin(), fiti.end(), fit.begin());
}

//Draw points
void MultiFitter::DrawPoints(double xi, double xf, double yi, double yf, string title, string xtitle, string ytitle) { 
    TApplication app1("app", nullptr, nullptr);
    TCanvas *c1 = new TCanvas("c1", &title[0], 0, 0, 1280, 720);
    TRootCanvas *rc1 = (TRootCanvas *)c1->GetCanvasImp();
    rc1->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

    TMultiGraph* mg = new TMultiGraph();
    vector<TGraphErrors*> graph(fit.size());

    for (int i = 0; i < graph.size(); i++) {
        graph[i] = new TGraphErrors(fit[i].GetPoints().size());
        for (int j = 0; j < fit[i].GetPoints().size(); j++) {
            graph[i]->SetPoint(j, fit[i].GetPoints()[j].first, fit[i].GetPoints()[j].second);
            graph[i]->SetPointError(j, fit[i].GetErrors()[j].first, fit[i].GetErrors()[j].second);
        }
        graph[i]->SetMarkerStyle(kFullCircle);
        graph[i]->SetMarkerColor(fit[i].GetFitFunction()[0]->GetLineColor());
        graph[i]->SetMarkerSize(1);
        //gStyle->SetPalette(kRainBow);
        mg->Add(graph[i]);
    }

    c1->SetGrid();
    /* mg->SetMarkerStyle(kFullCircle);
    mg->SetMarkerColor(kBlack);
    mg->SetMarkerSize(1);
    mg->SetLineWidth(1); */
    mg->SetMinimum(yi);
    mg->SetMaximum(yf);

    //gPad->SetLogx();
    //gPad->SetLogy();

    mg->GetXaxis()->SetLimits(xi, xf);
    mg->GetXaxis()->SetTitle(xtitle.c_str());
    mg->GetYaxis()->SetTitle(ytitle.c_str());
    mg->SetTitle(&title[0]);
    
    gStyle->SetPalette(kRainBow);

    mg->Draw("AP");

    TLegend* legend = new TLegend(.85, .85, .999, 1.);
    legend->SetFillColor(0);
    for (int i = 0; i < graph.size(); i++) {
        string s = "Graph " + to_string(i+1);
        legend->AddEntry(graph[i], &s[0], "lpf");
    }
    legend->Draw();

    string name = title + "points.png";

    c1->Update();
    c1->SaveAs(&name[0]);

    app1.Run();
} 

//Fit function without plotting
void MultiFitter::Fit() {
    /* TApplication app1("app", nullptr, nullptr);
    TCanvas *c1 = new TCanvas("c1", &title[0], 0, 0, 1280, 720);
    TRootCanvas *rc1 = (TRootCanvas *)c1->GetCanvasImp();
    rc1->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()"); */

    TMultiGraph* mg = new TMultiGraph();
    vector<TGraphErrors*> graph(fit.size());

    for (int i = 0; i < graph.size(); i++) {
        graph[i] = new TGraphErrors(fit[i].GetPoints().size());
        for (int j = 0; j < fit[i].GetPoints().size(); j++) {
            graph[i]->SetPoint(j, fit[i].GetPoints()[j].first, fit[i].GetPoints()[j].second);
            graph[i]->SetPointError(j, fit[i].GetErrors()[j].first, fit[i].GetErrors()[j].second);
        }
        graph[i]->Fit(fit[i].GetFitFunction()[0], "R");
        for (int k = 1; k < fit[i].GetFitFunction().size(); k++) {
            graph[i]->Fit(fit[i].GetFitFunction()[k], "R+");
        }
        graph[i]->SetMarkerStyle(kFullCircle);
        graph[i]->SetMarkerColor(fit[i].GetFitFunction()[0]->GetLineColor());
        graph[i]->SetMarkerSize(1);
        mg->Add(graph[i]);
    }

    /* c1->SetGrid();
    mg->SetMinimum(yi);
    mg->SetMaximum(yf);*/

    //gPad->SetLogx();
    //gPad->SetLogy();

    /* mg->GetXaxis()->SetLimits(xi, xf);
    mg->GetXaxis()->SetTitle(xtitle.c_str());
    mg->GetYaxis()->SetTitle(ytitle.c_str());
    mg->SetTitle(&title[0]);
    mg->Draw("AP");

    string name = title + "points.png";

    c1->Update();
    c1->SaveAs(&name[0]);

    app1.Run(); */
}

//Draw points and fitted curves
void MultiFitter::DrawFit(double xi, double xf, double yi, double yf, string title, string xtitle, string ytitle) { 
    TApplication app1("app", nullptr, nullptr);
    TCanvas *c1 = new TCanvas("c1", &title[0], 0, 0, 1280, 720);
    TRootCanvas *rc1 = (TRootCanvas *)c1->GetCanvasImp();
    rc1->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

    TMultiGraph* mg = new TMultiGraph();
    vector<TGraphErrors*> graph(fit.size());

    for (int i = 0; i < graph.size(); i++) {
        graph[i] = new TGraphErrors(fit[i].GetPoints().size());
        for (int j = 0; j < fit[i].GetPoints().size(); j++) {
            graph[i]->SetPoint(j, fit[i].GetPoints()[j].first, fit[i].GetPoints()[j].second);
            graph[i]->SetPointError(j, fit[i].GetErrors()[j].first, fit[i].GetErrors()[j].second);
        }
        graph[i]->Fit(fit[i].GetFitFunction()[0], "R");
        for (int k = 1; k < fit[i].GetFitFunction().size(); k++) {
            graph[i]->Fit(fit[i].GetFitFunction()[k], "R+");
        }
        graph[i]->SetMarkerStyle(kFullCircle);
        graph[i]->SetMarkerColor(fit[i].GetFitFunction()[0]->GetLineColor());
        graph[i]->SetMarkerSize(1);
        mg->Add(graph[i]);
    }

    c1->SetGrid();
    mg->SetMinimum(yi);
    mg->SetMaximum(yf);

    //gPad->SetLogx();
    //gPad->SetLogy();
    //gStyle->SetOptFit();

    mg->GetXaxis()->SetLimits(xi, xf);
    mg->GetXaxis()->SetTitle(xtitle.c_str());
    mg->GetYaxis()->SetTitle(ytitle.c_str());
    mg->SetTitle(&title[0]);
    mg->Draw("AP");

    TLegend* legend = new TLegend(.85, .85, .999, 1.);
    legend->SetFillColor(0);
    for (int i = 0; i < graph.size(); i++) {
        string s = "Fit " + to_string(i+1);
        legend->AddEntry(graph[i], &s[0], "lpf");
    }
    legend->Draw();

    string name = title + "points.png";

    c1->Update();
    c1->SaveAs(&name[0]);

    app1.Run();
} 

//Print points and error values
void MultiFitter::Print(string unitx, string unity) { 
    for (int j = 0; j < fit.size(); j++) {
        cout << "Graph " << j + 1 << ":" << endl;
        for (int i = 0; i < fit[j].GetPoints().size(); i++) {
            cout << "X = (" << fit[j].GetPoints()[i].first << " +/- " << fit[j].GetErrors()[i].first << ") [" << unitx << "]" << endl;
            cout << "Y = (" << fit[j].GetPoints()[i].second << " +/- " << fit[j].GetErrors()[i].second << ") [" << unity << "]" << endl;
            cout << "\n";
        } 
        cout << "\n\n";
    }    
}  