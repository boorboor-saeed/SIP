

#include <TCanvas.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TApplication.h>
#include <TH1D.h>
#include "TNtuple.h"
#include <TFile.h>
#include <TF1.h>
#include <TF2.h>

#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TRootCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TStyle.h"

#include "DChargeView.h"

enum DType
{
    Electron = 0,
    Hole = 1,
    PositiveIon = 2,
    NegativeIon = 3,
    Unknown = 4
};

void viewChargePlane(string fPath, string fViewPlane)
{

    cout << "this is viewCharge macro" << endl;

    //--------------------------------------------------------------------//
    gROOT->Reset();
    gStyle->SetPalette(1);
    gROOT->SetStyle("Plain");

    cout << "ViewPlane: " << fViewPlane << endl;

    TFile *in_file = new TFile(fPath.c_str());

    if (in_file->IsZombie())
    {
        cout << "Cannot open file: " << fPath << endl;
        return;
    }

    TNtuple *ntuple;

    in_file->GetObject("ChargeList", ntuple);

    float *row_content;

    int n = ntuple->GetEntries();

    // px:
    // py:
    // pz:
    // type:
    // scale:
    // process:
    // time

    TGraph *ge = new TGraph();
    TGraph *gh = new TGraph();

    int cc = 0;

    for (int irow = 0; irow < n; ++irow)
    {
        ntuple->GetEntry(irow);
        row_content = ntuple->GetArgs();

        float px = row_content[0];
        float py = row_content[1];
        float pz = row_content[2];
        int type = row_content[3];
        float scale = row_content[4];
        int process = row_content[5];
        float time = row_content[6];

        double xp, yp;

        if (fViewPlane == "XY")
        {
            xp = px;
            yp = py;
        }
        else if (fViewPlane == "XZ")
        {
            xp = px;
            yp = pz;
        }
        else if (fViewPlane == "YZ")
        {
            xp = py;
            yp = pz;
        }

        xp /= 1e-4;
        yp /= 1e-4;

        if (type == DType::Electron)
        {
            cc++;
            ge->AddPoint(xp, yp);
        }

        if (type == DType::Hole)
        {
            cc++;
            gh->AddPoint(xp, yp);
        }
    }

    cout << cc << endl;

    double markerSize = 0.5;
    ge->SetMarkerColor(kBlue);
    ge->SetMarkerSize(markerSize);
    gh->SetMarkerColor(kRed);
    gh->SetMarkerSize(markerSize);

    auto canvas = new TCanvas("Charge", "", 20, 20, 1000, 500);
    canvas->Divide(2, 1);

    canvas->cd(1);
    gStyle->SetOptStat(000000);
    ge->Draw("ap");
    ge->SetTitle("Electrons");

    canvas->cd(2);
    gStyle->SetOptStat(000000);
    gh->SetMarkerStyle(53);
    gh->Draw("ap");
    gh->SetTitle("Holes");
}

//

void viewCharge3D(string fPath)
{
    //--------------------------------------------------------------------//
    gROOT->Reset();
    gStyle->SetPalette(1);
    gROOT->SetStyle("Plain");

    TFile *in_file = new TFile(fPath.c_str());

    if (in_file->IsZombie())
    {
        cout << "Cannot open file: " << fPath << endl;
        return;
    }

    TNtuple *ntuple;

    in_file->GetObject("Charge", ntuple);

    float *row_content;

    int n = ntuple->GetEntries();

    ntuple->SetMarkerColor(2);
    ntuple->Draw("px:py:pz*10000", "type==0");

    ntuple->SetMarkerColor(4);
    ntuple->Draw("px:py:pz*10000", "type==1", "same");
}