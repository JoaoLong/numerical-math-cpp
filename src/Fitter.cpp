#include "Fitter.h"

using namespace std;

//Constructor with two vectors of pair, points and errors
Fitter::Fitter(vector<pair<double,double>> p, vector<pair<double,double>> e, std::vector<TF1*> fi) { //Constructor
    points.resize(p.size());
    copy(p.begin(), p.end(), points.begin());

    errors.resize(e.size());
    copy(e.begin(), e.end(), errors.begin());
    f.resize(fi.size());
    for (int i = 0; i < f.size(); i++) {
        f[i] = fi[i];
    }
    //f = fi;
} 

//Constructor reading from txt file with 2-4 columns (x, y, ex, ey)
Fitter::Fitter(string filename, std::vector<TF1*> fi) {
    string line;
    ifstream infile;

    //Fitting with errors does not accept ey=0. If it is 0, invert the fit. If both are zero, no problem

    double x=0, y=0, ex=0, ey=0;
    int n = 0;

    infile.open(filename); 
    if (infile.fail()) {
        cout << "File opening failed" << endl;
    }

    while (getline(infile, line)) {
        stringstream s(line);
        if (s >> x >> y >> ex >> ey) {
            points.push_back(make_pair(x, y));
            errors.push_back(make_pair(ex, ey));
        }
        n++;
    }

    infile.close();
    f.resize(fi.size());
    for (int i = 0; i < f.size(); i++) {
        f[i] = fi[i];
    }
    //f = fi;
}

//Destructor
Fitter::~Fitter() {
    //delete f;
}

//Setter for points
void Fitter::SetPoints(vector<pair<double,double>> p) { 
    for (int i = 0 ; i < p.size(); i++){
        points[i] = make_pair(p[i].first, p[i].second);
    }
} 

//Setter for errors
void Fitter::SetErrors(vector<pair<double,double>> e) { 
    for (int i = 0 ; i < e.size(); i++){
        errors[i] = make_pair(e[i].first, e[i].second);
    }
} 

//Getter for points
vector<pair<double,double>> Fitter::GetPoints() {
    return points;
}

//Setter for points
vector<pair<double,double>> Fitter::GetErrors() {
    return errors;
}

//Setter for function to fit
void Fitter::SetFitFunction(std::vector<TF1*> F1) { 
    f.resize(F1.size());
    for (int i = 0; i < f.size(); i++) {
        f[i] = F1[i];
    }
} 

//Getter for function to fit
std::vector<TF1*> Fitter::GetFitFunction() { 
    return f;
} 

//Draw points
void Fitter::DrawPoints(double xi, double xf, double yi, double yf, string title, string xtitle, string ytitle) { 
    TApplication app1("app", nullptr, nullptr);
    TCanvas *c1 = new TCanvas("c1", &title[0], 0, 0, 1920, 1080);
    TRootCanvas *rc1 = (TRootCanvas *)c1->GetCanvasImp();
    rc1->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

    TGraphErrors *graph1 = new TGraphErrors(points.size());

    for (int i = 0; i < points.size(); ++i) {
        graph1->SetPoint(i, points[i].first, points[i].second);
        graph1->SetPointError(i, errors[i].first, errors[i].second);
    }

    c1->SetGrid();
    graph1->SetMarkerStyle(kFullCircle);
    graph1->SetMarkerColor(kBlack);
    graph1->SetMarkerSize(1);
    graph1->SetLineWidth(1);
    graph1->SetMinimum(yi);
    graph1->SetMaximum(yf);

    graph1->GetXaxis()->SetLimits(xi, xf);
    graph1->GetXaxis()->SetTitle(xtitle.c_str());
    graph1->GetYaxis()->SetTitle(ytitle.c_str());
    graph1->SetTitle(&title[0]);
    
    graph1->Draw("AP");

    string name = title + "points.pdf";

    c1->Update();
    c1->SaveAs(&name[0]);

    app1.Run();
} 

//Draw points and fitted curve
void Fitter::DrawFit(double xi, double xf, double yi, double yf, string title, string xtitle, string ytitle) { 

    TApplication app1("app", nullptr, nullptr);
    TCanvas *c1 = new TCanvas("c1", &title[0], 0, 0, 1920, 1080);
    TRootCanvas *rc1 = (TRootCanvas *)c1->GetCanvasImp();
    rc1->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

    TGraphErrors *graph1 = new TGraphErrors(points.size());

    for (int i = 0; i < points.size(); ++i) {
        graph1->SetPoint(i, points[i].first, points[i].second);
        graph1->SetPointError(i, errors[i].first, errors[i].second);
    }

    c1->SetGrid();
    graph1->SetMarkerStyle(kFullCircle);
    graph1->SetMarkerColor(kBlack);
    graph1->SetMarkerSize(1);
    graph1->SetLineWidth(2);
    graph1->SetMinimum(yi);
    graph1->SetMaximum(yf);

    //SetParameters, SetRange
    //v - verbose, q - quiet, R - range 

    graph1->Fit(f[0], "R");
    for (int i = 1; i < f.size(); i++) {
        f[i]->SetLineWidth(2);
        graph1->Fit(f[i], "R+");
    }

    graph1->GetXaxis()->SetLimits(xi, xf);
    graph1->GetXaxis()->SetTitle(xtitle.c_str());
    graph1->GetYaxis()->SetTitle(ytitle.c_str());
    graph1->SetTitle(&title[0]);
    gStyle->SetOptFit();
    
    graph1->Draw("AP");

    string name = title + ".png";

    c1->Update();
    c1->SaveAs(&name[0]);

    app1.Run();
} 

//Print points and error values
void Fitter::Print(string unitx, string unity) { 
    for (int i = 0; i < points.size(); i++) {
        cout << "X = (" << points[i].first << " +/- " << errors[i].first << ") [" << unitx << "]" << endl;
        cout << "Y = (" << points[i].second << " +/- " << errors[i].second << ") [" << unity << "]" << endl;
        cout << "\n\n";
    } 
} 