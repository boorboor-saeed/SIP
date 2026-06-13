#include "DSignal.h"
#include "DFileTools.h"

DSignal::DSignal() : DPairVector()
{
    pValid = false;
}
DSignal::DSignal(vector<float> fTimeVec, vector<float> fValueVec, string fTitle) : DPairVector(fTimeVec, fValueVec, fTitle)
{
    bool flag = CheckMonotonicTimeIncrease();
    if (flag == false || IsZombie() == true)
    {
        pValid = false;
    }
}

DSignal::~DSignal()
{
}

bool DSignal::IsValid()
{
    return pValid;
}

DSignal DSignal::ReadSignalFromCSVFile(string fAddress, int fColumnIndex, string fTitle)
{
    DSignal signal;
    CSVFileReader file(fAddress);
    if (file.IsZombie() == true)
    {
        return signal;
    }

    if (fColumnIndex < 0 || fColumnIndex >= file.GetNColumns())
    {
        return signal;
    }

    vector<float> time = file.GetColumn(0);
    vector<float> value = file.GetColumn(fColumnIndex);
    signal = DSignal(time, value, fTitle);
    return signal;
}

const vector<float> &DSignal::GetTimeVec()
{
    return GetXVec();
}

const vector<float> &DSignal::GetValueVec()
{
    return GetYVec();
}

bool DSignal::CheckMonotonicTimeIncrease()
{
    const float tolerance = 1e-10;

    for (int i = 0; i < GetLength(); i++)
    {
        float dt = GetTimeVec()[i] - GetTimeVec()[i - 1];
        if (dt > tolerance)
        {
            return false;
        }
    }
    return true;
}