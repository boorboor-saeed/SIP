
#include "DViewResults.h"
#include "DSignalTools.h"
#include "DTools.h"

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
#include "TGaxis.h"

#include <sstream>
#include <fstream>
#include <istream>
#include <iostream>

#include <iostream>
#include <sstream>

DViewResults::DViewResults(string fXLabel, string fYLabel, string fTitle)
{
  pXLabel = fXLabel;
  pYLabel = fYLabel;
  pTitle = fTitle;
  xmin = 0;
  xmax = 0;
  ymin = 0;
  ymax = 0;

  // pCanvas = new TCanvas(GetTitle().c_str(), GetTitle().c_str(), 200, 200, 600, 600);
  // pCanvas->SetGrid();
  // pCanvas->cd();
}
DViewResults::~DViewResults()
{
}

void DViewResults::ViewSignal(DSignal fSignal)
{
  gROOT->Reset();
  gStyle->SetPalette(1);
  gROOT->SetStyle("Plain");

  auto pCanvas = new TCanvas(GetTitle().c_str(), GetTitle().c_str(), 200, 200, 600, 600);
  pCanvas->SetGrid();
  TGraph *gr = new TGraph(fSignal.GetLength(), &fSignal.GetTimeVec()[0], &fSignal.GetValueVec()[0]);

  gr->SetLineWidth(2);
  gr->Draw("al");

  gr->GetXaxis()->CenterTitle(true);
  gr->GetXaxis()->SetTitleOffset(1.2);
  gr->GetXaxis()->SetTitleSize(0.03);
  gr->GetXaxis()->SetMoreLogLabels(true);
  gr->GetXaxis()->SetLabelSize(0.03);

  gr->GetYaxis()->CenterTitle(true);
  gr->GetYaxis()->SetTitleOffset(1.2);
  gr->GetYaxis()->SetTitleSize(0.03);
  gr->GetYaxis()->SetMoreLogLabels(true);
  gr->GetYaxis()->SetLabelSize(0.03);

  // gr->GetXaxis()->SetTitle("Time (ns)");
  // gr->GetYaxis()->SetTitle("Signal (fC/ns)");
  // gr->SetTitle(fSignal.GetTitle().c_str());

  gr->GetXaxis()->SetTitle(GetXLabel().c_str());
  gr->GetYaxis()->SetTitle(GetYLabel().c_str());
}

void DViewResults::ViewChargeRadialDistribution(vector<float> fRadii, vector<float> fDensity)
{
  gROOT->Reset();
  gStyle->SetPalette(1);
  gROOT->SetStyle("Plain");

  auto pCanvas = new TCanvas(GetTitle().c_str(), GetTitle().c_str(), 200, 200, 600, 600);
  pCanvas->SetGrid();
  TGraph *gr = new TGraph(fRadii.size(), &fRadii[0], &fDensity[0]);

  gr->SetLineWidth(2);
  gr->Draw("al");

  gr->GetXaxis()->CenterTitle(true);
  gr->GetXaxis()->SetTitleOffset(1.2);
  gr->GetXaxis()->SetTitleSize(0.03);
  gr->GetXaxis()->SetMoreLogLabels(true);
  gr->GetXaxis()->SetLabelSize(0.03);

  gr->GetYaxis()->CenterTitle(true);
  gr->GetYaxis()->SetTitleOffset(1.6);
  gr->GetYaxis()->SetTitleSize(0.03);
  gr->GetYaxis()->SetMoreLogLabels(true);
  gr->GetYaxis()->SetLabelSize(0.03);

  gr->GetXaxis()->SetTitle(GetXLabel().c_str());
  gr->GetYaxis()->SetTitle(GetYLabel().c_str());

  // gPad->SetLogx();
}

void DViewResults::ViewChargeRadialDistribution(vector<float> fRadii, vector<vector<float>> fDensities, vector<std::string> fLegends)
{
  int step = 10;
  vector<float> MarkerSize{2, 2, 2, 2, 2, 2};
  // vector<EColor> MarkerColor{kBlack, kBlue, kOrange, kRed, kGreen, kP8Cyan};
  // vector<int> MarkerStyle{108, 106, 91, 104, 107, 105, 107};

  vector<EColor> MarkerColor{kBlack, kBlue, kGreen, kRed, kOrange, kP8Cyan};
  vector<int> MarkerStyle{108, 106, 107, 104, 91, 105, 107};

  auto pCanvas = new TCanvas(GetTitle().c_str(), GetTitle().c_str(), 200, 200, 600, 600);
  pCanvas->SetGrid();
  pCanvas->cd();

  TMultiGraph *mg = new TMultiGraph();
  TMultiGraph *mg_markers = new TMultiGraph();

  TLegend *leg = new TLegend();

  vector<float> RadiiDownSample = DownSample(fRadii, step);

  for (int i = 0; i < fDensities.size(); i++)
  {

    TGraph *gr_line = new TGraph(fRadii.size(), &fRadii[0], &fDensities[i][0]);
    gr_line->SetLineWidth(2);
    gr_line->SetLineColor(MarkerColor[i]);
    mg->Add(gr_line);
    // down sample signal for marker plot
    vector<float> DensityDownSample = DownSample(fDensities[i], step);
    TGraph *gr_marker = new TGraph(DensityDownSample.size(), &RadiiDownSample[0], &DensityDownSample[0]);
    gr_marker->SetMarkerStyle(MarkerStyle[i]);
    gr_marker->SetMarkerColor(MarkerColor[i]);
    gr_marker->SetMarkerSize(MarkerSize[i]);
    gr_marker->SetLineWidth(2);
    gr_marker->SetLineColor(MarkerColor[i]);
    mg_markers->Add(gr_marker);
    leg->AddEntry(gr_marker, fLegends[i].c_str());
  }

  mg->GetXaxis()->SetTitle(GetXLabel().c_str());
  mg->GetYaxis()->SetTitle(GetYLabel().c_str());

  mg->GetXaxis()->CenterTitle(true);
  mg->GetXaxis()->SetTitleOffset(1.2);
  mg->GetXaxis()->SetTitleSize(0.03);
  mg->GetXaxis()->SetMoreLogLabels(true);
  mg->GetXaxis()->SetLabelSize(0.03);

  mg->GetYaxis()->CenterTitle(true);
  mg->GetYaxis()->SetTitleOffset(1.2);
  mg->GetYaxis()->SetTitleSize(0.03);
  mg->GetYaxis()->SetMoreLogLabels(true);
  mg->GetYaxis()->SetLabelSize(0.03);

  mg->Draw("al");
  mg_markers->Draw("p");

  leg->SetFillColor(0);
  // leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->DrawClone("Same");

  pCanvas->Update();
}

#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>

void DViewResults::ViewChargeRadialDistribution(vector<DChargeStatistics> fList)
{
  int step = 20;
  vector<float> MarkerSize{2, 2, 2, 2, 2, 2, 2};
  // vector<EColor> MarkerColor{kBlack, kBlue, kOrange, kRed, kGreen, kP8Cyan};
  // vector<int> MarkerStyle{108, 106, 91, 104, 107, 105, 107};

  vector<EColor> MarkerColor{kBlack, kBlue, kGreen, kRed, kOrange, kP8Cyan, kMagenta};
  vector<int> MarkerStyle{108, 106, 107, 104, 91, 105, 107, 107};

  auto pCanvas = new TCanvas(GetTitle().c_str(), GetTitle().c_str(), 200, 200, 600, 600);
  pCanvas->SetGrid();
  pCanvas->cd();

  TMultiGraph *mg = new TMultiGraph();
  TMultiGraph *mg_markers = new TMultiGraph();

  TLegend *leg = new TLegend();

  for (int i = 0; i < fList.size(); i++)
  {

    //
    if (fList[i].IsValid() == false)
    {
      continue;
    }
    vector<float> Radii = fList[i].GetRaddi();
    vector<float> Radii_um = DTools ::MultiplyVec(Radii, 1.0 / DUnitSystem::um);
    vector<float> dist = fList[i].GetRadialDistribution();

    float max = DTools::FindMax(dist);
    if (max <= 0)
    {
      continue;
    }
    dist = DTools::MultiplyVec(dist, 1.0 / max);

    std::stringstream number;
    number << std::setprecision(4) << max;
    std::string number_str;
    number >> number_str;

    std::string caption;
    caption = fList[i].GetName() + " ( #/" + number_str + ")";

    TGraph *gr_line = new TGraph(Radii_um.size(), &Radii_um[0], &dist[0]);
    gr_line->SetLineWidth(2);
    gr_line->SetLineColor(MarkerColor[i]);
    mg->Add(gr_line);
    leg->AddEntry(gr_line, caption.c_str());
    // down sample signal for marker plot //
    // vector<float> RadiiDownSample = DownSample(Radii_um, step);
    // vector<float> DensityDownSample = DownSample(dist, step);
    // TGraph *gr_marker = new TGraph(DensityDownSample.size(), &RadiiDownSample[0], &DensityDownSample[0]);
    // gr_marker->SetMarkerStyle(MarkerStyle[i]);
    // gr_marker->SetMarkerColor(MarkerColor[i]);
    // gr_marker->SetMarkerSize(MarkerSize[i]);
    // gr_marker->SetLineWidth(2);
    // gr_marker->SetLineColor(MarkerColor[i]);
    // mg_markers->Add(gr_marker);
    // leg->AddEntry(gr_marker, fList[i].GetName().c_str());
  }

  mg->GetXaxis()->SetTitle(GetXLabel().c_str());
  mg->GetYaxis()->SetTitle(GetYLabel().c_str());

  mg->GetXaxis()->CenterTitle(true);
  mg->GetXaxis()->SetTitleOffset(1.2);
  mg->GetXaxis()->SetTitleSize(0.03);
  mg->GetXaxis()->SetMoreLogLabels(true);
  mg->GetXaxis()->SetLabelSize(0.03);

  mg->GetYaxis()->CenterTitle(true);
  mg->GetYaxis()->SetTitleOffset(1.2);
  mg->GetYaxis()->SetTitleSize(0.03);
  mg->GetYaxis()->SetMoreLogLabels(true);
  mg->GetYaxis()->SetLabelSize(0.03);

  mg->Draw("al");
  mg_markers->Draw("p");

  leg->SetFillColor(0);
  // leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->DrawClone("Same");

  mg->GetXaxis()->SetLimits(xmin, xmax);
  // gPad->SetLogx();

  gPad->Update();
  pCanvas->Modified();
  pCanvas->Update();
}

void DViewResults::ViewSignalsInGroupCompare(vector<DSignal> fSignals, int fGroupSize)
{

  if (fGroupSize == 0)
  {
    fGroupSize = fSignals.size();
  }

  vector<float> MarkerSize{2, 2, 2, 2, 2, 2};
  vector<EColor> MarkerColor{kBlack, kBlue, kGreen, kRed, kOrange, kP8Cyan};
  vector<int> MarkerStyle{108, 106, 107, 104, 91, 105, 107};

  auto pCanvas = new TCanvas(GetTitle().c_str(), GetTitle().c_str(), 200, 200, 600, 600);
  pCanvas->SetGrid();
  pCanvas->cd();

  TMultiGraph *mg = new TMultiGraph();
  TMultiGraph *mg_markers = new TMultiGraph();

  TLegend *leg = new TLegend();

  for (int i = 0; i < fSignals.size(); i++)
  {
    if (fSignals[i].IsZombie() == true)
    {
      return;
    }

    // compute marker index
    int markerIndex = i % fGroupSize;

    TGraph *gr_line = new TGraph(fSignals[i].GetLength(), &fSignals[i].GetTimeVec()[0], &fSignals[i].GetValueVec()[0]);
    gr_line->SetLineWidth(2);
    gr_line->SetLineColor(MarkerColor[markerIndex]);
    mg->Add(gr_line);
    // down sample signal for marker plot
    DSignal sigMarker = DSignalTools::DownSampleSignal(fSignals[i], 20);
    TGraph *gr_marker = new TGraph(sigMarker.GetLength(), &sigMarker.GetTimeVec()[0], &sigMarker.GetValueVec()[0]);

    gr_marker->SetMarkerStyle(MarkerStyle[markerIndex]);
    gr_marker->SetMarkerColor(MarkerColor[markerIndex]);
    gr_marker->SetMarkerSize(MarkerSize[markerIndex]);
    gr_marker->SetLineWidth(2);
    gr_marker->SetLineColor(MarkerColor[markerIndex]);
    mg_markers->Add(gr_marker);

    if (i < fGroupSize) // add to legend only for the first group
    {
      leg->AddEntry(gr_marker, fSignals[i].GetTitle().c_str());
    }
  }

  if (xmin < xmax)
  {
    mg->GetXaxis()->SetRangeUser(xmin, xmax);
    mg->GetXaxis()->SetRangeUser(xmin, xmax);
  }

  mg->GetXaxis()->SetTitle(GetXLabel().c_str());
  mg->GetYaxis()->SetTitle(GetYLabel().c_str());

  mg->GetXaxis()->CenterTitle(true);
  mg->GetXaxis()->SetTitleOffset(1.2);
  mg->GetXaxis()->SetTitleSize(0.03);
  mg->GetXaxis()->SetMoreLogLabels(true);
  mg->GetXaxis()->SetLabelSize(0.03);

  mg->GetYaxis()->CenterTitle(true);
  mg->GetYaxis()->SetTitleOffset(1.2);
  mg->GetYaxis()->SetTitleSize(0.03);
  mg->GetYaxis()->SetMoreLogLabels(true);
  mg->GetYaxis()->SetLabelSize(0.03);

  mg->Draw("al");
  mg_markers->Draw("p");

  leg->SetFillColor(0);
  // leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->DrawClone("Same");

  pCanvas->Update();
}

void DViewResults::ViewSignals(vector<DSignal> fSignals)
{

  vector<float> MarkerSize{2, 2, 2, 2, 2, 2};
  // vector<EColor> MarkerColor{kBlack, kBlue, kOrange, kRed, kGreen, kP8Cyan};
  // vector<int> MarkerStyle{108, 106, 91, 104, 107, 105, 107};

  vector<EColor> MarkerColor{kBlack, kBlue, kGreen, kRed, kOrange, kP8Cyan};
  vector<int> MarkerStyle{108, 106, 107, 104, 91, 105, 107};

  auto pCanvas = new TCanvas(GetTitle().c_str(), GetTitle().c_str(), 200, 200, 600, 600);
  pCanvas->SetGrid();
  pCanvas->cd();

  TMultiGraph *mg = new TMultiGraph();
  TMultiGraph *mg_markers = new TMultiGraph();

  TLegend *leg = new TLegend();

  for (int i = 0; i < fSignals.size(); i++)
  {
    if (fSignals[i].IsZombie() == true)
    {
      return;
    }
    TGraph *gr_line = new TGraph(fSignals[i].GetLength(), &fSignals[i].GetTimeVec()[0], &fSignals[i].GetValueVec()[0]);
    gr_line->SetLineWidth(2);
    gr_line->SetLineColor(MarkerColor[i]);
    mg->Add(gr_line);
    // down sample signal for marker plot
    DSignal sigMarker = DSignalTools::DownSampleSignal(fSignals[i], 5);
    TGraph *gr_marker = new TGraph(sigMarker.GetLength(), &sigMarker.GetTimeVec()[0], &sigMarker.GetValueVec()[0]);
    gr_marker->SetMarkerStyle(MarkerStyle[i]);
    gr_marker->SetMarkerColor(MarkerColor[i]);
    gr_marker->SetMarkerSize(MarkerSize[i]);
    gr_marker->SetLineWidth(2);
    gr_marker->SetLineColor(MarkerColor[i]);
    mg_markers->Add(gr_marker);
    leg->AddEntry(gr_marker, fSignals[i].GetTitle().c_str());
  }

  mg->GetXaxis()->SetTitle(GetXLabel().c_str());
  mg->GetYaxis()->SetTitle(GetYLabel().c_str());

  mg->GetXaxis()->CenterTitle(true);
  mg->GetXaxis()->SetTitleOffset(1.2);
  mg->GetXaxis()->SetTitleSize(0.03);
  mg->GetXaxis()->SetMoreLogLabels(true);
  mg->GetXaxis()->SetLabelSize(0.03);

  mg->GetYaxis()->CenterTitle(true);
  mg->GetYaxis()->SetTitleOffset(1.2);
  mg->GetYaxis()->SetTitleSize(0.03);
  mg->GetYaxis()->SetMoreLogLabels(true);
  mg->GetYaxis()->SetLabelSize(0.03);

  mg->Draw("al");
  mg_markers->Draw("p");

  leg->SetFillColor(0);
  // leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->DrawClone("Same");

  pCanvas->Update();
}

void DViewResults::ViewDataPoints(vector<DPairVector> fDataExp, vector<DPairVector> fDataSim, bool fXlog, bool fYlog)
{
  gROOT->Reset();
  gStyle->SetPalette(1);
  gROOT->SetStyle("Plain");

  gStyle->SetStatStyle(0);
  gStyle->SetTitleStyle(0);
  gROOT->ForceStyle();

  // auto c1 = new TCanvas("PlasmaTime", "PlasmaTime", 10, 10, 700, 500);
  // c1->Range(0, 0, 4, 30);

  vector<float> MarkerSize{1, 1, 1, 1, 1, 1};
  vector<EColor> MarkerColor{kBlack, kBlue, kRed, kGreen, kOrange, kP8Cyan};
  vector<int> MarkerStyle_exp{20, 21, 22, 23, 29, 33};
  vector<int> MarkerStyle_sim{24, 25, 26, 32, 30, 27};

  auto pCanvas = new TCanvas(GetTitle().c_str(), GetTitle().c_str(), 200, 200, 600, 600);
  pCanvas->SetGrid();
  pCanvas->cd();

  TMultiGraph *mg_exp = new TMultiGraph();
  TMultiGraph *mg_sim = new TMultiGraph();

  float w = 0.5;
  float h = 0.1;
  float x = 0.15;
  float y = 0.15;

  TLegend *leg_exp = new TLegend(x, y, x + w, y + h);
  y = 0.25;
  TLegend *leg_sim = new TLegend(x, y, x + w, y + h);

  for (int i = 0; i < fDataExp.size(); i++)
  {

    if (fDataExp[i].IsZombie() == true)
    {
      return;
    }

    TGraph *gr = new TGraph(fDataExp[i].GetLength(), &fDataExp[i].GetXVec()[0], &fDataExp[i].GetYVec()[0]);
    gr->SetMarkerStyle(MarkerStyle_exp[i]);
    gr->SetMarkerColor(MarkerColor[i]);
    gr->SetLineWidth(0);
    gr->SetMarkerSize(MarkerSize[i] + 0.5);
    mg_exp->Add(gr);
    leg_exp->AddEntry(gr, fDataExp[i].GetTitle().c_str());
  }

  for (int i = 0; i < fDataSim.size(); i++)
  {

    if (fDataSim[i].IsZombie() == true)
    {
      return;
    }

    TGraph *gr = new TGraph(fDataSim[i].GetLength(), &fDataSim[i].GetXVec()[0], &fDataSim[i].GetYVec()[0]);
    gr->SetMarkerStyle(MarkerStyle_sim[i]);
    gr->SetMarkerColor(MarkerColor[i]);
    gr->SetLineWidth(0);
    gr->SetMarkerSize(MarkerSize[i] + 0.8);
    mg_sim->Add(gr);
    leg_sim->AddEntry(gr, fDataSim[i].GetTitle().c_str());
  }

  // ----------------------------------------- //
  mg_exp->GetXaxis()->SetTitle(GetXLabel().c_str());
  mg_exp->GetYaxis()->SetTitle(GetYLabel().c_str());

  mg_exp->GetXaxis()->CenterTitle(true);
  mg_exp->GetXaxis()->SetTitleOffset(1.2);
  mg_exp->GetXaxis()->SetTitleSize(0.03);
  mg_exp->GetXaxis()->SetMoreLogLabels(true);
  mg_exp->GetXaxis()->SetLabelSize(0.03);
  // mg_exp->GetXaxis()->SetNdivisions(5000);

  mg_exp->GetYaxis()->CenterTitle(true);
  mg_exp->GetYaxis()->SetTitleOffset(1.2);
  mg_exp->GetYaxis()->SetTitleSize(0.03);
  mg_exp->GetYaxis()->SetMoreLogLabels(true);
  mg_exp->GetYaxis()->SetLabelSize(0.03);

  if (xmin < xmax)
  {
    mg_exp->GetXaxis()->SetRangeUser(xmin, xmax);
    mg_sim->GetXaxis()->SetRangeUser(xmin, xmax);
  }

  if (ymin < ymax)
  {
    mg_exp->GetYaxis()->SetRangeUser(ymin, ymax);
    mg_sim->GetYaxis()->SetRangeUser(ymin, ymax);
  }

  mg_exp->Draw("ap");
  mg_sim->Draw("p");

  gPad->SetLogy(fYlog);
  gPad->SetLogx(fXlog);

  if (1)
  {
    leg_exp->SetFillColor(0);
    leg_exp->SetBorderSize(0);
    leg_exp->SetTextSize(0.03);
    leg_exp->DrawClone("Same");

    leg_sim->SetFillColor(0);
    leg_sim->SetBorderSize(0);
    leg_sim->SetTextSize(0.03);
    leg_sim->SetFillColorAlpha(kWhite, 1);
    // leg_sim->SetFillStyle(0); hollow
    leg_sim->DrawClone("Same");
  }

  pCanvas->Update();
}

// void ComparePlasmaTime(vector<SignalData> fDataExp, vector<SignalData> fDataSim, string title)
// {
//   gROOT->Reset();
//   gStyle->SetPalette(1);
//   gROOT->SetStyle("Plain");

//   gStyle->SetStatStyle(0);
//   gStyle->SetTitleStyle(0);
//   gROOT->ForceStyle();

//   auto c1 = new TCanvas("PlasmaTime", "PlasmaTime", 10, 10, 700, 500);
//   c1->Range(0, 0, 4, 30);

//   vector<float> MarkerSize{1, 1, 1, 1, 1, 1};
//   vector<EColor> MarkerColor{kBlack, kBlue, kRed, kGreen, kOrange, kP8Cyan};
//   vector<int> MarkerStyle_exp{20, 21, 22, 23, 29, 33};
//   vector<int> MarkerStyle_sim{24, 25, 26, 32, 30, 27};

//   auto pCanvas = new TCanvas(title.c_str(), title.c_str(), 200, 200, 600, 600);
//   pCanvas->SetGrid();
//   pCanvas->cd();

//   TMultiGraph *mg_exp = new TMultiGraph();
//   TMultiGraph *mg_sim = new TMultiGraph();

//   float w = 0.5;
//   float h = 0.1;
//   float x = 0.15;
//   float y = 0.15;

//   TLegend *leg_exp = new TLegend(x, y, x + w, y + h);
//   y = 0.25;
//   TLegend *leg_sim = new TLegend(x, y, x + w, y + h);

//   for (int i = 0; i < fDataExp.size(); i++)
//   {

//     if (fDataExp[i].IsZombie == true)
//     {
//       return;
//     }

//     TGraph *gr = new TGraph(fDataExp[i].length, &fDataExp[i].time[0], &fDataExp[i].value[0]);
//     gr->SetMarkerStyle(MarkerStyle_exp[i]);
//     gr->SetMarkerColor(MarkerColor[i]);
//     gr->SetLineWidth(0);
//     gr->SetMarkerSize(MarkerSize[i] + 0.5);
//     mg_exp->Add(gr);
//     leg_exp->AddEntry(gr, fDataExp[i].Title.c_str());
//   }

//   for (int i = 0; i < fDataSim.size(); i++)
//   {

//     if (fDataSim[i].IsZombie == true)
//     {
//       return;
//     }

//     TGraph *gr = new TGraph(fDataSim[i].length, &fDataSim[i].time[0], &fDataSim[i].value[0]);
//     gr->SetMarkerStyle(MarkerStyle_sim[i]);
//     gr->SetMarkerColor(MarkerColor[i]);
//     gr->SetLineWidth(0);
//     gr->SetMarkerSize(MarkerSize[i] + 0.8);
//     mg_sim->Add(gr);
//     leg_sim->AddEntry(gr, fDataSim[i].Title.c_str());
//   }

//   // ----------------------------------------- //
//   mg_exp->GetXaxis()->SetTitle("Electric field (kV/cm)");
//   mg_exp->GetYaxis()->SetTitle(title.c_str());

//   mg_exp->GetXaxis()->CenterTitle(true);
//   mg_exp->GetXaxis()->SetTitleOffset(1.2);
//   mg_exp->GetXaxis()->SetTitleSize(0.03);
//   mg_exp->GetXaxis()->SetMoreLogLabels(true);
//   mg_exp->GetXaxis()->SetLabelSize(0.03);
//   // mg_exp->GetXaxis()->SetNdivisions(5000);

//   mg_exp->GetYaxis()->CenterTitle(true);
//   mg_exp->GetYaxis()->SetTitleOffset(1.2);
//   mg_exp->GetYaxis()->SetTitleSize(0.03);
//   mg_exp->GetYaxis()->SetMoreLogLabels(true);
//   mg_exp->GetYaxis()->SetLabelSize(0.03);

//   double xmin = 0.5;
//   double xmax = 3;
//   double ymin = 1;
//   double ymax = 30;

//   mg_exp->Draw("ap");
//   mg_sim->Draw("p");

//   gPad->SetLogy(1);
//   gPad->SetLogx(1);

//   if (1)
//   {
//     leg_exp->SetFillColor(0);
//     leg_exp->SetBorderSize(0);
//     leg_exp->SetTextSize(0.03);
//     leg_exp->DrawClone("Same");

//     leg_sim->SetFillColor(0);
//     leg_sim->SetBorderSize(0);
//     leg_sim->SetTextSize(0.03);
//     leg_sim->SetFillColorAlpha(kWhite, 1);
//     // leg_sim->SetFillStyle(0); hollow
//     leg_sim->DrawClone("Same");
//   }

//   pCanvas->Update();
// }
