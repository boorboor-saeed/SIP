#include "DChargeStatistics.h"
#include "DTools.h"
#include "DFileTools.h"
#include <math.h>

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

DChargeStatistics::DChargeStatistics(std::string fName, std::string fAddress)
{
    pValidFlag = ReadChargeFromRoot(fAddress);
    pName = fName;
}
DChargeStatistics::~DChargeStatistics() {

};

std::string DChargeStatistics::GetName()
{
    return pName;
}

bool DChargeStatistics::IsValid()
{
    return pValidFlag;
}

// bool DChargeStatistics::ReadChargeFromCSV(std::string fAddress)
// {
//     pChargeList.clear();
//     pChargeList.resize(0);

//     CSVFileReader file(fAddress);
//     if (file.IsZombie() == true)
//     {
//         return false;
//     }

//     for (int i = 0; i < file.GetNRows(); i++)
//     {
//         vector<float> row = file.GetRow(i);
//         float x = row[0];
//         float y = row[1];
//         float z = row[2];
//         float scale = row[3];
//         int type = row[4];
//         DThreeVector position(x, y, z);
//         DCharge charge;
//         charge.Position = position;
//         charge.Scale = scale;
//         charge.Type = DType(type);
//         pChargeList.push_back(charge);
//     }
//     return true;
// }

bool DChargeStatistics::ReadChargeFromRoot(std::string fAddress)
{
    pChargeList.clear();
    pChargeList.resize(0);

    TFile *in_file = new TFile(fAddress.c_str());

    if (in_file->IsZombie())
    {
        cout << "Cannot open file: " << fAddress << endl;
        return false;
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

    for (int irow = 0; irow < n; ++irow)
    {
        ntuple->GetEntry(irow);
        row_content = ntuple->GetArgs();

        float px = row_content[0] / DUnitSystem::um;
        float py = row_content[1] / DUnitSystem::um;
        float pz = row_content[2] / DUnitSystem::um;
        int type = row_content[3];
        float scale = row_content[4];
        int process = row_content[5];
        float time = row_content[6];

        DThreeVector position(px, py, pz);
        DCharge charge;
        charge.Position = position;
        charge.Scale = scale;
        charge.Type = DType(type);
        pChargeList.push_back(charge);
    }

    return true;
}

vector<float> DChargeStatistics::GetRadialDistribution()
{
    return pRadialDistribution;
}
vector<float> DChargeStatistics::GetRaddi()
{
    return pRadii;
}
void DChargeStatistics::ComputeRadialDistribution(std::vector<float> fRaddi, DType fType, DThreeVector fAxisStart, DThreeVector fAxisEnd)
{
    pRadii = fRaddi;
    // ------- compute charge number per micrometer cube -------//
    int NOSections = fRaddi.size();
    pRadialDistribution.resize(NOSections);
    for (int i = 0; i < pRadialDistribution.size(); i++)
    {
        pRadialDistribution[i] = 0;
    }

    int NoP = pChargeList.size();

    // float maxdim = -1000;
    // for (int i = 0; i < pChargeList.size(); i++)
    // {
    //     if (fType == pChargeList[i].Type)
    //         cout << pChargeList[i].Position.GetZ() << endl;
    // }

    float Zmin = fAxisStart.GetZ() / DUnitSystem::um;
    float Zmax = fAxisEnd.GetZ() / DUnitSystem::um;

    for (int i = 0; i < pChargeList.size(); i++)
    {
        if (fType != pChargeList[i].Type)
        {
            continue;
        }
        // transform charge along axis //
        DThreeVector position = pChargeList[i].Position;

        // check z section //
        if (position.GetZ() < Zmin || position.GetZ() >= Zmax)
        {
            continue;
        }

        // find radius //
        float r2 = position.GetX() * position.GetX() + position.GetY() * position.GetY();
        float radius = sqrt(r2);

        // find section //
        int index = -1;
        for (int ri = 0; ri < (NOSections - 1); ri++)
        {
            if (radius <= (fRaddi[ri] / DUnitSystem::um))
            {
                index = ri + 0;
                break;
            }
        }

        if (index >= 0)
        {
            pRadialDistribution[index] = pRadialDistribution[index] + pChargeList[i].Scale;
        }
    }

    // normalize to volume
    for (int ri = 0; ri < (NOSections - 1); ri++)
    {
        float rmin = fRaddi[ri] / DUnitSystem::um;
        float rmax = fRaddi[ri + 1] / DUnitSystem::um;
        float volume = M_PI * (rmax * rmax - rmin * rmin) * (Zmax - Zmin);
        pRadialDistribution[ri] = pRadialDistribution[ri] / volume;
    }
    return;
}
