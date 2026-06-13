#ifndef DSignalTools_h
#define DSignalTools_h

#include <iostream>
#include <cmath>
#include <vector>
#include "DSignal.h"
#include "DFileTools.h"

using namespace std;

class DSignalTools
{
public:
    DSignalTools() { ; }
    ~DSignalTools() { ; }

    // static DSignal ReadSignalFromCSVFile(string fAddress, int fColumnIndex, string fTitle);

    // analysis
    static float ComputeRiseTime(DSignal fChargeSignal, float fWindowBottom, float fWindowUp);

    // processing
    static DSignal DownSampleSignal(DSignal fSigIn, float fDt);
    static DSignal UpSampleSignal(DSignal fSigIn, float fDt);
    static float LinLinInterpolate(DSignal &fSigIn, float fTime);

    static DSignal IdealIntegrate(DSignal &fSigIn);
    static DSignal IdealDifferentiate(DSignal &fSigIn);
    static DSignal Normalize(DSignal &fSigIn);
    static DSignal Extend(DSignal &fSigIn, float fDuration, bool fExtrapolateToZero = false);

    static float FindMax(DSignal &fSigIn);

    static float FindTimeAt(DSignal &fSigIn, float fValue);
    static DSignal ShiftTime(DSignal &fSigIn, float fShift);
    static DSignal Scale(DSignal &fSigIn, float fScale);
    static DSignal MovingAverage(DSignal &fSigIn, float fAveTime);
    static DSignal ApplySlewRate(DSignal &fSigIn, float fRiseFallTime);

    static DSignal BuildStep(float fAmplitude, float fPulse, float fPeriod, float fDelay);

private:
};
#endif