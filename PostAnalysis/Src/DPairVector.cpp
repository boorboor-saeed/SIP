#include "DPairVector.h"
#include "DFileTools.h"

DPairVector::DPairVector()
{
    pZombie = true;
    pEquispaced = false;
    pTitle = "";
}

DPairVector::DPairVector(vector<float> fXVec, vector<float> fYVec, string fTitle)
{
    pZombie = true;
    pEquispaced = false;
    pX = fXVec;
    pY = fYVec;
    pTitle = fTitle;

    bool fl = CheckLength();
    if (fl == true)
    {
        pZombie = false;
    }
    else
    {
        return;
    }
    bool fe = CheckEquiSpace();
    if (fe == true)
    {
        pEquispaced = true;
    }
}

DPairVector::~DPairVector()
{
}

const vector<float> &DPairVector::GetXVec()
{
    return pX;
}

const vector<float> &DPairVector::GetYVec()
{
    return pY;
}

int DPairVector::GetLength()
{
    return pLength;
}
bool DPairVector::IsZombie()
{
    return pZombie;
}
bool DPairVector::IsEquispaced()
{
    return pEquispaced;
}

string DPairVector::GetTitle()
{
    return pTitle;
}

void DPairVector::SetTitle(string fTitle)
{
    pTitle = fTitle;
}

bool DPairVector::CheckLength()
{
    if (pX.size() < 2 || pY.size() < 2 || pY.size() != pX.size())
    {
        return false;
    }
    pLength = pX.size();
    return true;
}

bool DPairVector::CheckEquiSpace()
{
    const float tolerance = 1e-10;

    float dt0 = pX[1] - pX[0];
    for (int i = 1; i < pLength; i++)
    {
        float dt = pX[i] - pX[i - 1];
        float diff = fabs(dt - dt0);

        if (diff > tolerance)
        {
            return false;
        }
    }
    return true;
}

DPairVector DPairVector::ReadFromCSVFile(string fAddress, int fColumnIndex, string fTitle)
{
    DPairVector pairVector;
    CSVFileReader file(fAddress);
    if (file.IsZombie() == true)
    {
        return pairVector;
    }

    if (fColumnIndex < 0 || fColumnIndex >= file.GetNColumns())
    {
        return pairVector;
    }

    vector<float> X = file.GetColumn(0);
    vector<float> Y = file.GetColumn(fColumnIndex);
    pairVector = DPairVector(X, Y, fTitle);
    return pairVector;
}