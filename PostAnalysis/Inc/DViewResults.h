#ifndef DPlotSignal
#define DPlotSignal

#include <iostream>
#include <fstream>
#include <cmath>
#include "DSignal.h"
#include <TCanvas.h>

#include "DChargeStatistics.h"

using namespace std;

class DViewResults
{
public:
    DViewResults(string fXLabel, string fYLabel, string fTitle);
    ~DViewResults();

    void ViewSignal(DSignal fSignal);
    void ViewSignals(vector<DSignal> fSignals);
    void ViewSignalsInGroupCompare(vector<DSignal> fSignals, int fGroupSize = 0);
    void ViewDataPoints(vector<DPairVector> fDataExp, vector<DPairVector> fDataSim, bool fXlog = false, bool fYlog = false);

    void ViewChargeRadialDistribution(vector<float> fRadii, vector<float> fDensity);
    void ViewChargeRadialDistribution(vector<float> fRadii, vector<vector<float>> fDensities, vector<std::string> fLegends);
    void ViewChargeRadialDistribution(vector<DChargeStatistics> fList);

    vector<float> DownSample(vector<float> fVec, int fStep)
    {
        vector<float> out;
        for (int i = 0; i < fVec.size(); i = i + fStep)
        {
            out.push_back(fVec[i]);
        }
        return out;
    }

    //
    string GetTitle()
    {
        return pTitle;
    }
    void SetTitle(string fTitle) { pTitle = fTitle; }

    string GetYLabel() { return pYLabel; }
    void GetYLabel(string fLabel) { pYLabel = fLabel; }

    string GetXLabel() { return pXLabel; }
    void GetXLabel(string fLabel) { pXLabel = fLabel; }

    void SetXRange(float fXmin, float fXmax)
    {
        xmin = fXmin;
        xmax = fXmax;
    }
    void SetYRange(float fYmin, float fYmax)
    {
        ymin = fYmin;
        ymax = fYmax;
    }

private:
    string pTitle;
    string pYLabel;
    string pXLabel;
    bool pXlog, pYlog;

    float xmin;
    float xmax;
    float ymin;
    float ymax;

    TCanvas *pCanvas;
};

#endif